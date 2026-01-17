*This Project has been created as part of the 42 curriculum by **aphyo-ht**.*

# PIPEX

## Description

PIPEX is a 42 school project that implements a simplified version of Unix shell piping functionality. This program recreates the behavior of the shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

The program demonstrates fundamental Unix concepts including:
- **Process creation and management** using `fork()` and `execve()`
- **Inter-process communication** through Unix pipes
- **File descriptor manipulation** for input/output redirection
- **PATH environment variable parsing** for command resolution
- **Error handling** with proper exit codes

PIPEX takes an input file, executes the first command with that file as input, pipes the output to a second command, and writes the final result to an output file. This mimics the shell's pipe operator (`|`) behavior in a controlled environment.

## Instructions

### Prerequisites
Before compilation, ensure your system has:
- Unix-like operating system (Linux, macOS)
- GCC compiler
- Make build tool
- Standard C library

### Compilation
1. Clone or download the project to your local machine
	```bash
	git clone https://github.com/thevowels/42_pipex.git
	```
2. Navigate to the project directory:
   ```bash
   cd pipex
   ```
3. Compile the project using Make:
   ```bash
   make
   ```
   This will:
   - Compile the custom `libft` library
   - Compile all mandatory source files
   - Create the `pipex` executable

### Execution
Run the program with the following syntax:
```bash
./pipex file1 cmd1 cmd2 file2
```

**Parameters:**
- `file1`: Input file to read from (must exist and be readable)
- `cmd1`: First command to execute (with arguments if needed, enclosed in quotes)
- `cmd2`: Second command to execute (with arguments if needed, enclosed in quotes)  
- `file2`: Output file to write to (will be created or overwritten)

### Practical Examples
```bash
# Count lines containing "hello" in input.txt
./pipex input.txt "grep hello" "wc -l" output.txt

# Sort and remove duplicates from data.txt
./pipex data.txt "sort" "uniq" result.txt

# Find files and count them
./pipex file_list.txt "cat" "grep '.txt'" text_files.txt

# Complex command with arguments
./pipex data.csv "cut -d',' -f1" "sort -r" sorted_names.txt
```

### Testing Your Implementation
1. Create a test input file:
   ```bash
   echo -e "apple\nbanana\napple\ncherry" > test.txt
   ```
2. Test the program:
   ```bash
   ./pipex test.txt "sort" "uniq" result.txt
   cat result.txt
   ```
3. Compare with shell equivalent:
   ```bash
   < test.txt sort | uniq > expected.txt
   diff result.txt expected.txt
   ```

### Make Commands
- `make` or `make all`: Compile the entire project
- `make clean`: Remove object files (.o files)
- `make fclean`: Remove object files and executable
- `make re`: Clean and recompile everything from scratch

### Error Handling
The program handles various error conditions:
- Invalid number of arguments
- File access permissions (read/write)
- Command not found in PATH
- Pipe creation failures
- Process creation failures
- Memory allocation errors

Exit codes follow Unix conventions, returning the exit status of the last executed command.

## Project Structure

```
pipex_now/
├── Makefile                 # Build configuration
├── README.md               # This file
├── libft/                  # Custom C library
│   ├── Makefile
│   ├── includes/
│   │   └── libft.h
│   └── src/                # Library source files
│       ├── ctype/          # Character type functions
│       ├── math/           # Mathematical utilities
│       ├── others/         # Memory operations
│       ├── print/          # Output functions
│       └── string/         # String manipulation
└── mandatory/              # Main project files
    ├── pipex.c            # Main program logic
    ├── pipex.h            # Header file
    ├── pipex_utils.c      # Utility functions
    └── path_utils.c       # PATH resolution functions
```

## Technical Implementation

### Core Components

1. **Process Creation**: Uses `fork()` to create two child processes
2. **Pipe Communication**: Creates a pipe using `pipe()` for inter-process communication
3. **File Descriptor Management**: Uses `dup2()` for input/output redirection
4. **Command Execution**: Uses `execve()` to execute commands
5. **PATH Resolution**: Searches through system PATH to find executables

### Error Handling

The program includes robust error handling for:
- Invalid number of arguments
- File access permissions
- Command not found
- Pipe creation failures
- Process creation failures
- Memory allocation errors

## Resources

### Essential Readings
- [Unix Pipes and Forks](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY) - Understanding pipe concepts (Youtube Playlist)
- [Process Management in Unix](https://www.geeksforgeeks.org/process-management-in-unix/) - Fork, exec, and wait functions
- [File Descriptors and Redirection](https://www.gnu.org/software/bash/manual/html_node/Redirections.html) - Input/output redirection in Unix

### System Calls Documentation
- [fork(2) manual page](https://man7.org/linux/man-pages/man2/fork.2.html) - Creating child processes
- [execve(2) manual page](https://man7.org/linux/man-pages/man2/execve.2.html) - Executing programs
- [pipe(2) manual page](https://man7.org/linux/man-pages/man2/pipe.2.html) - Creating pipes
- [dup2(2) manual page](https://man7.org/linux/man-pages/man2/dup2.2.html) - Duplicating file descriptors
