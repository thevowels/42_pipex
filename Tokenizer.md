# Tokenizing — Full Algorithmic Specification

Purpose
- Provide a production-ready, language-agnostic algorithmic description for tokenizing command-line style input into discrete tokens. This document describes the desired behavior, state machine, memory considerations, edge cases, and tests. No implementation code is included; the focus is on algorithm and correctness.

Definitions
- Input: a finite sequence of characters (bytes) provided as a single string or a stream.
- Token: a contiguous logical unit derived from the input (e.g., command or argument). Tokens are returned as an ordered list.
- Separator: characters that delimit tokens (typically whitespace: space, tab, newline) unless inside quotes or escaped.
- Quote characters: single quote (') and double quote (").
- Escape character: backslash (\) used to protect special characters from their normal interpretation.

Goals and requirements
- Produce a NULL-terminated array/list of tokens in order of appearance.
- Preserve quoted substrings as single tokens and keep their contained characters (optionally with quote removal, see behavior below).
- Support escapes so characters that would otherwise end or split tokens are included literally.
- Be linear time O(n) in the length of the input and use O(n) memory in worst case.
- Be robust: detect and report malformed input (e.g., unclosed quotes) and avoid undefined behavior.
- Provide deterministic behavior for empty tokens (for example, the empty string produced by "" should be an empty token, not ignored).

High-level behavior choices (design decisions)
- Quote handling: remove quotes in output tokens (so input "a b" yields token a b) while preserving the enclosed content. This mirrors shell-like behavior and is the default in this spec.
- Escape handling inside quotes:
  - Single quotes (`'`): treat everything inside as literal; do not process escapes (i.e., backslash has no special meaning).
  - Double quotes (`"`): allow backslash to escape `"`, `\\`, and optionally `$`/`` ` `` if expansion is implemented; for pure tokenizing, escape only `"` and `\\`.
- Empty tokens: `''` or `""` produce an explicit empty token.
- Whitespace definition: use the language's `isspace` semantics over unsigned char values, or a clearly documented subset (space and tab are common minimal choices).

State machine (formal description)
Maintain one of the following states while scanning characters left-to-right:

- OUT: not currently building a token (in whitespace between tokens).
- IN: building an unquoted token.
- IN_SINGLE: inside single quotes.
- IN_DOUBLE: inside double quotes.
- ESCAPE: immediate escape state (used only while in IN or IN_DOUBLE when backslash seen).

State transitions and actions (per input character `c`):

- State OUT:
  - If `c` is EOF: finish; emit no new token.
  - If `c` is whitespace: remain OUT (skip it).
  - If `c` is single-quote (`'`): transition -> IN_SINGLE; start new token buffer (empty).
  - If `c` is double-quote (`"`): transition -> IN_DOUBLE; start new token buffer (empty).
  - If `c` is backslash (`\`): transition -> ESCAPE; start new token buffer and mark that one escaped char will be taken literally.
  - Otherwise: transition -> IN; start new token buffer and append `c` to buffer.

- State IN:
  - If `c` is EOF or whitespace: finalize current token (append to token list), transition -> OUT.
  - If `c` is single-quote (`'`): transition -> IN_SINGLE (do not append the quote to buffer).
  - If `c` is double-quote (`"`): transition -> IN_DOUBLE.
  - If `c` is backslash (`\`): transition -> ESCAPE (next char appended literally).
  - Otherwise: append `c` to current buffer; remain IN.

- State IN_SINGLE:
  - If `c` is EOF: error (unterminated single quote).
  - If `c` is single-quote (`'`): transition -> IN (or -> OUT if no more characters and next char is whitespace or EOF); do not append the quote.
  - Otherwise: append `c` literally to buffer; remain IN_SINGLE.

- State IN_DOUBLE:
  - If `c` is EOF: error (unterminated double quote).
  - If `c` is double-quote (`"`): transition -> IN; do not append the quote.
  - If `c` is backslash (`\`): transition -> ESCAPE (escape is interpreted inside double quotes, but only for specific characters depending on design; minimally allow `"` and `\\`).
  - Otherwise: append `c` to buffer; remain IN_DOUBLE.

- State ESCAPE:
  - If `c` is EOF: treat as literal backslash at end (behavior choice) or error; the spec recommends treating as literal backslash and producing a token containing a `\`.
  - Append `c` to buffer literally (even if `c` is quote or whitespace); transition back to IN or IN_DOUBLE depending on previous context.

Notes on transitions:
- When IN_SINGLE or IN_DOUBLE transitions back to IN, subsequent whitespace or EOF will close the token per the IN rules.
- If quotes open a token when in OUT, the resulting token should be emitted when the matching quote closes and the state reaches OUT or when whitespace/EOF ends it.
- For the purposes of simplicity, this spec treats tokens as sequences of characters after quote removal; i.e., quotes themselves are not included in output tokens.

Memory and output structure
- Token buffer management:
  - For each new token, allocate a dynamic buffer. A practical strategy is to start with a modest initial capacity (e.g., 32 bytes) and double the capacity whenever the buffer would overflow. Doubling ensures amortized O(1) append time.
  - Track buffer length and capacity. After finishing a token, shrink-to-fit if desired, then store the pointer in the tokens array.
- Token list management:
  - Maintain an array/vector of `char *` token pointers. Start with an initial capacity (e.g., 8) and double when more slots are needed.
  - The returned structure should be NULL-terminated for interoperability (e.g., to pass as `argv`).
- Memory ownership and freeing:
  - The caller receives ownership of the array and each token string. Document that the caller must free each token and the array container.

Error handling and edge cases
- Unterminated quotes: detect when EOF is reached while in IN_SINGLE or IN_DOUBLE and return a clear error code or set an error flag. Optionally return partially parsed tokens or none — prefer failing and leaving no tokens to avoid inconsistent state.
- Invalid escape sequences: by default, any character following `\` is taken literally. If policy differs (e.g., only specific escapes allowed), define the allowed set and report an error on invalid escapes.
- Extremely long tokens: defend against unbounded memory consumption by imposing a configurable per-token maximum length. If exceeded, return an error.
- Empty input: return an empty token list (NULL pointer array with first entry NULL).
- Only-quote tokens: `'` or `"` immediately followed by matching quote produce an empty string token (not ignored).

Complexity
- Time: single pass over input, O(n) where n is number of characters.
- Memory: worst-case O(n) for token data plus overhead for the token pointers array.

Security and robustness considerations
- Validate all allocations; on allocation failure, free previously allocated memory and return an error.
- Use unsigned character semantics when classifying whitespace or other character classes to avoid UB on signed char platforms.
- Enforce reasonable limits on number of tokens and token sizes to prevent denial-of-service via extremely large inputs.

Streaming and incremental parsing
- For very long inputs or interactive streams, design the tokenizer to operate incrementally:
  - Maintain state across buffers (OUT, IN, IN_SINGLE, IN_DOUBLE, ESCAPE) so partial token data from the end of a chunk is preserved for the next chunk.
  - Emit completed tokens as they become available; hold the current token buffer between calls.
  - When the stream ends, apply end-of-input rules (error on unclosed quotes, finalize token if in IN).

Examples (input => tokens)
- `echo hello world` => `["echo", "hello", "world"]`
- `echo "a b" c` => `["echo", "a b", "c"]`
- `cmd 'single quoted' "double quoted"` => `["cmd", "single quoted", "double quoted"]`
- `a\\ b` (where `\\` is a single backslash then space) => `["a b"]` if backslash escapes the space.
- `"" empty` => `["", "empty"]` (explicit empty token then token `empty`).
- `a\"b` inside double quote context (e.g., `"a\"b"`) => token `a"b` (quote inside preserved via escape).

Testing checklist
- Unit tests for:
  - Basic splitting on whitespace.
  - Single and double quoted tokens.
  - Escaped characters in and out of quotes.
  - Empty tokens from `""` and `''`.
  - Unterminated quotes produce errors.
  - Large input performance and memory safety.
- Property tests: random inputs vs. a reference implementation (e.g., a known shell parser) to find mismatches.

Integration notes
- When passing tokens to `execve`, ensure the array is NULL-terminated and that `argv[0]` is set appropriately.
- If performing additional shell-like processing (globbing, variable expansion, command substitution), do so in clearly separated phases after tokenization.

Optional extensions
- Support for locale-aware whitespace and multibyte characters.
- Support for quoted escapes of other sequences (`\n`, `\t`) if desired — document behavior.
- Add diagnostics that include character index and context for better error messages.

If you'd like, I can now:
- Produce a careful, safe C implementation following this spec with allocation checks and unit tests.
- Produce a streaming version and a test harness that fuzz-tests the tokenizer.
