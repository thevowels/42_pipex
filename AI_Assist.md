# C Standard and POSIX I/O / Process Helpers — Quick Reference

This file gives concise explanations, prototypes, return values, error notes, and tiny examples for common C/POSIX functions you listed.

---

open, close, read, write
- Purpose: low-level POSIX file I/O.
- Prototypes:
  - `int open(const char *pathname, int flags, mode_t mode);`
  - `int close(int fd);`
  - `ssize_t read(int fd, void *buf, size_t count);`
  - `ssize_t write(int fd, const void *buf, size_t count);`
- Return values: `open` returns a non-negative file descriptor or -1 on error; `close` returns 0 or -1; `read`/`write` return number of bytes or -1 on error (0 from `read` means EOF).
- Errors: check `errno` after -1; common errors include `EACCES`, `ENOENT`, `EBADF`, `EINTR`.
- Notes: `open` flags include `O_RDONLY`, `O_WRONLY`, `O_RDWR`, `O_CREAT`, `O_TRUNC`, `O_APPEND`. Use `mode` when creating files (e.g., `0644`).

malloc, free
- Purpose: allocate and free heap memory in C.
- Prototypes:
  - `void *malloc(size_t size);`
  - `void free(void *ptr);`
- Return values: `malloc` returns a pointer to allocated memory or `NULL` on failure. `free` returns nothing; passing `NULL` is safe.
- Errors: if `malloc` returns `NULL`, do not dereference the pointer; handle allocation failures gracefully.

perror, strerror
- Purpose: convert `errno` into human-readable messages and print errors.
- Prototypes:
  - `void perror(const char *s);` — prints `s: <error message>` to `stderr` using current `errno`.
  - `char *strerror(int errnum);` — returns pointer to string describing `errnum`.
- Notes: `perror` is convenient for quick diagnostics; `strerror` can be used to format messages.

access
- Purpose: check user's permissions for a pathname.
- Prototype: `int access(const char *pathname, int mode);` where `mode` is `R_OK`, `W_OK`, `X_OK`, `F_OK`.
- Return: 0 on success (permission OK), -1 on error and `errno` set.
- Warning: `access` checks real UID/GID and can introduce TOCTOU races; use carefully.

dup, dup2
- Purpose: duplicate file descriptors.
- Prototypes:
  - `int dup(int oldfd);`
  - `int dup2(int oldfd, int newfd);`
- Return: new file descriptor on success, -1 on error.
- Notes: `dup2` closes `newfd` first if open and makes it refer to the same open file description as `oldfd`. Useful for redirecting `stdin`/`stdout` before `exec`.

execve
- Purpose: execute a new program in the current process image.
- Prototype: `int execve(const char *pathname, char *const argv[], char *const envp[]);`
- Behavior: on success `execve` does not return (current process replaced); on error returns -1 and sets `errno`.
- Notes: pass `argv[0]` as program name and terminate `argv`/`envp` with NULL. Common wrapper functions: `execl`, `execv`, `execvp`.

exit
- Purpose: terminate the calling process normally.
- Prototype: `void exit(int status);`
- Behavior: flushes stdio buffers, calls `atexit` handlers, then returns `status` to the parent.

fork
- Purpose: create a new process (child) by duplicating the calling process.
- Prototype: `pid_t fork(void);`
- Return: in parent returns child's PID (>0); in child returns 0; on error returns -1 and sets `errno`.
- Notes: after `fork`, both processes continue executing; careful with resources like open file descriptors and memory.

pipe
- Purpose: create a unidirectional data channel (pipe) between processes.
- Prototype: `int pipe(int pipefd[2]);` — `pipefd[0]` is read end, `pipefd[1]` is write end.
- Return: 0 on success, -1 on error.
- Notes: pipes are blocking by default; close unused ends in parent/child.

unlink
- Purpose: remove a name from the filesystem (delete a file link).
- Prototype: `int unlink(const char *pathname);`
- Return: 0 on success, -1 on error.
- Notes: if last link is removed and no processes have the file open, storage is freed. If open FDs exist, file remains until closed.

wait, waitpid
- Purpose: wait for child process state changes.
- Prototypes:
  - `pid_t wait(int *wstatus);`
  - `pid_t waitpid(pid_t pid, int *wstatus, int options);`
- Return: PID of changed child, or -1 on error.
- Notes: `wait` waits for any child; `waitpid` can wait for a specific child or use options like `WNOHANG`. Inspect `wstatus` with macros `WIFEXITED`, `WEXITSTATUS`, `WIFSIGNALED`, `WTERMSIG`.

---

Minimal examples

- Redirect stdout to a file using `dup2` and `execve` (sketch):

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    int fd = open("out.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if (fd < 0) return 1;
    if (dup2(fd, STDOUT_FILENO) < 0) return 1;
    close(fd);
    char *argv[] = {"/bin/echo", "hello", NULL};
    execve("/bin/echo", argv, NULL);
    return 1; // execve only returns on error
}
```

- Create a pipe, fork, and have child write to parent:

```c
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int fds[2];
    if (pipe(fds) != 0) { perror("pipe"); exit(1); }
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) { // child
        close(fds[0]);
        const char *msg = "hi\n";
        write(fds[1], msg, 3);
        close(fds[1]);
        exit(0);
    } else { // parent
        close(fds[1]);
        char buf[10];
        ssize_t n = read(fds[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, n);
        close(fds[0]);
        waitpid(pid, NULL, 0);
    }
    return 0;
}
```

---

Tips
- Always check return values and examine `errno` on failures.
- Use `perror` or `strerror(errno)` for readable diagnostics.
- Be mindful of resource leaks: close file descriptors and `free` memory.
- Beware TOCTOU races when using `access` or multiple syscalls on shared paths.

If you want, I can expand any entry with more examples or edge cases.

---

Parsing (command / input parsing)
- Purpose: turn raw text (command lines, input strings, files) into structured data you can act on (e.g., `argv[]` for `execve`).
- Common tasks:
  - Tokenizing: split by whitespace while respecting quotes and escapes.
  - Handling environment lookup: search `PATH` for executables (or use full paths).
  - Converting strings to numbers: use `strtol`, `strtoul`, or `%d` with `sscanf` safely.
  - Memory management: allocate arrays of `char *` for tokens and `free` them later.
- Approaches:
  - Simple: `strtok` or your project's `ft_split` for whitespace-only splits (fast but limited — it ignores quotes and escapes).
  - Robust: write a small stateful parser that tracks whether you're inside single/double quotes and handles backslashes; this avoids splitting inside quoted strings.
  - Libraries: use existing parsers if available for complex grammars.
- Pitfalls and tips:
  - Preserve quoted substrings (e.g., `echo "a b"` => two tokens: `echo` and `a b`).
  - Handle empty tokens and multiple spaces correctly.
  - Be careful with stack buffers; `malloc` tokens sized to strlen+1.
  - Validate conversions (`strtol` sets `errno` on overflow, check end-pointer).

Minimal parsing sketch (split by spaces, handle double quotes):

```c
// Very small example: not production-ready, demonstrates approach
#include <stdlib.h>
#include <string.h>

char **simple_parse(const char *s) {
    // returns NULL-terminated array of malloc'd strings; caller frees
    char **out = malloc(sizeof(char*) * 64);
    size_t oi = 0;
    size_t i = 0, n = strlen(s);
    while (i < n) {
        while (i < n && s[i] == ' ') i++;
        if (i >= n) break;
        int inq = 0;
        size_t start = i;
        char buf[1024]; size_t bi = 0;
        while (i < n && (inq || s[i] != ' ')) {
            if (s[i] == '"') { inq = !inq; i++; continue; }
            buf[bi++] = s[i++];
        }
        buf[bi] = '\0';
        out[oi++] = strdup(buf);
    }
    out[oi] = NULL;
    return out;
}
```

If you want, I can expand this into a production-safe parser (supporting single/double quotes, escapes, malloc sizing, and edge-case tests).

---

Tokenizing
- Purpose: break an input string into tokens (words) while handling quotes and escapes.
- Behavior: tokens are contiguous substrings that represent command/argument units. Tokenizers should:
  - Skip leading whitespace.
  - Treat text inside single quotes `'...'` as a single token (no escape processing inside single quotes).
  - Treat text inside double quotes `"..."` as a single token (allow backslash escapes for `"` and `\\`).
  - Allow backslash `\` to escape the following character outside single quotes.
  - Return a NULL-terminated `char **` array where each entry is `malloc`'d and caller frees.
- Common helpers: `strtok_r` or `strsep` for simple splits; custom stateful parser for correct shell-like behavior.

Compact tokenizer example (handles spaces, single/double quotes, and backslash escapes):

```c
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Returns NULL-terminated array; caller must free each string and the array.
char **tokenize(const char *s) {
  size_t cap = 8, cnt = 0;
  char **res = malloc(sizeof(char*) * cap);
  const char *p = s;
  while (*p) {
    while (isspace((unsigned char)*p)) p++;
    if (!*p) break;
    if (cnt + 1 >= cap) { cap *= 2; res = realloc(res, sizeof(char*) * cap); }
    char *buf = malloc(strlen(p) + 1);
    size_t bi = 0;
    int in_single = 0, in_double = 0;
    while (*p && (in_single || in_double || !isspace((unsigned char)*p))) {
x      if (*p == '\'' && !in_double) { in_single = !in_single; p++; continue; }
      if (*p == '"' && !in_single) { in_double = !in_double; p++; continue; }
      if (*p == '\\' && !in_single && p[1]) { p++; buf[bi++] = *p++; continue; }
      buf[bi++] = *p++;
    }
    buf[bi] = '\0';
    res[cnt++] = buf;
  }
  res[cnt] = NULL;
  return res;
}
```

Notes:
- This example is compact for clarity; production code should validate allocations, handle very long tokens without temporary over-allocations, and provide clear error paths.
- If you need shell-compatible parsing (expansions, globbing), consider using a library or a more complete parser.
