![Alt text](/static/getnextline.drawio.png?raw=true "Diagram for get next line")

*This activity has been created as part of the 42 curriculum by mberraho.*

# get_next_line

## Description

The goal of this project is to implement the `get_next_line` function, a utility that reads a file descriptor line by line and returns one line per call, including the terminating newline character (`\n`) when present.

The core challenge is to manage partial reads and preserve unread data between function calls. This is achieved through a static buffer (`stash`) that stores leftover data after a line is extracted. The function must handle arbitrary line lengths, work with a configurable buffer size, and behave correctly at end-of-file.

This implementation follows the standard constraints of the 42 `get_next_line` project and is structured to be readable, modular, and debuggable.

## Instructions


### Uage 

Uncomment the main function in get_next_line.c file

### Compilation
```sh
cc -Wall -Wextra -Werror ./get_next_line.c ./get_next_line.h ./get_next_line_utils.c -g -D BUFFER_SIZE=1000
```

### Check memory leak
```sh
valgrind --tool=memcheck --leak-check=full --track-origins=yes ./a.out
```

## Algorithm and Design Choices

### High-level Strategy

This implementation follows a **stash-driven, newline-centric algorithm**, directly reflected in both the flowchart diagram and the source code.

A static buffer called `stash` is used to store unread data between calls to `get_next_line`. The function progresses only when it can either return a complete line (ending with `\n`) or determine that no more data is available.

---

### Core State

- **`static char *stash`**  
  Persistent memory that survives across function calls. It contains:
  - leftover data after a line has been returned, or
  - newly read data that has not yet formed a complete line.

This corresponds to the top-level state in the diagram and the loop-back path labeled `stash = left_over`.

---

### Control Flow Logic

1. **Function entry**
   - Execution begins with the current value of `stash`, which may be `NULL` or already contain data from a previous call.

2. **Stash null check**
   - If `stash == NULL`, the function must read from the file descriptor.
   - If `stash != NULL`, the function checks whether it already contains a newline.

   This is represented by the first decision node (`is null ?`) in the diagram.

3. **Newline detection**
   - If `stash` contains a `\n`, no further reading is required.
   - If `stash` does not contain a `\n`, the function continues reading and appending data.

   This matches the central decision point (`has \n ?`) in the diagram and the condition used in the read loop.

4. **Read and append phase**
   - A temporary buffer of size `BUFFER_SIZE` is allocated.
   - `read(fd, buffer, BUFFER_SIZE)` is called.
   - If `read` returns `0` or a negative value:
     - No more data can be read (EOF or error).
     - The read loop stops.
   - Otherwise:
     - The buffer is null-terminated.
     - The buffer is concatenated to `stash`.
     - Control returns to the newline check.

   This corresponds to the diagram path:

5. **Line extraction**
- When a newline is found in `stash`:
  - `stash` is split into two parts:
    - **line**: all characters up to and including the first `\n`
    - **left_over**: all characters after the first `\n`
  - `line` is returned to the caller.
  - `stash` is replaced with `left_over`.

This matches the diagram block “split stash in two parts” followed by “return line”.

6. **End-of-file without newline**
- If reading stops and no newline exists in `stash`:
  - If `stash` is not `NULL`, its entire content is returned as the final line.
  - `stash` is then freed and reset to `NULL`.
  - If `stash` is `NULL`, the function returns `NULL`.

This corresponds to the termination paths at the bottom of the diagram.

---

### Algorithm Characteristics

- **Lazy reading**  
Data is read only until a newline is encountered or EOF is reached.

- **Single-line guarantee**  
Each call to `get_next_line` returns exactly one line.

- **Persistent state**  
Unconsumed data is preserved across calls using a static buffer.

- **Deterministic control flow**  
All execution paths end in either:
- returning a line, or
- terminating cleanly at end-of-file.

---

### Justification of the Approach

- Lines may span multiple reads, making buffering mandatory.
- A static stash avoids data loss and repeated reads.
- Splitting only at the first newline prevents over-reading.
- The flowchart models this behavior as a loop with two exit conditions:
- a newline is found, or
- no more data can be read.

The implementation is a direct translation of this model, ensuring correctness, predictability, and compliance with the project constraints.

## Implementation Difficulty and Comparison with the Invariant Approach

### Why `get_next_line` Is Difficult to Implement

The difficulty of `get_next_line` does not come from complex algorithms, but from **state management under partial information**. The function must:

- Read from a file descriptor in fixed-size chunks
- Return exactly one logical line per call
- Handle lines longer than `BUFFER_SIZE`
- Preserve unread data between calls
- Correctly terminate at end-of-file
- Avoid memory leaks and undefined behavior

All of this must be achieved in a language without automatic memory management, while respecting strict ownership rules. The difficulty lies in coordinating **control flow, memory lifetime, and state persistence** simultaneously.

The core source of complexity is that the function’s result (a full line) is not aligned with the unit of input (`read()` chunks).

---

### Hidden State and Control Flow Entanglement

In the current implementation, control flow is driven by conditions such as:

- Is `stash` NULL?
- Does `stash` contain a newline?
- Did `read()` return data or EOF?

These conditions are checked repeatedly and indirectly influence:
- when to read,
- when to stop reading,
- when to split,
- when to return.

This leads to a branching-heavy implementation where correctness depends on covering all edge cases in the right order.

---

## Invariant Programming: Concept

**Invariant programming** is a design approach where a program maintains a condition (an invariant) that is always true at a specific point in execution.

Instead of asking:
> “What should I do now?”

You define:
> “What must always be true when I reach this point?”

Control flow is then structured to preserve that invariant.

Typical benefits:
- Reduced branching
- Fewer special cases
- Easier reasoning about correctness
- Clear separation between *state maintenance* and *result extraction*

### A Natural Invariant for `get_next_line`

A useful invariant for this problem could be:

> **At the start of each iteration, `stash` contains only unread data and never contains a complete line that has not yet been returned.**

Or, more concretely:

> **After the read loop finishes, `stash` contains either:**
> - exactly one full line followed by leftovers, or  
> - no newline at all and no more data can be read.

With this invariant, the algorithm becomes conceptually simpler:
- First, enforce the invariant (read until it holds).
- Then, extract the result knowing the invariant guarantees correctness.

---

### How an Invariant-Based Design Would Look

Invariant-based structure:

1. **Maintain the invariant**
   - While `stash` has no newline and input is not exhausted:
     - Read and append to `stash`.

2. **Exploit the invariant**
   - If `stash` contains a newline:
     - Split and return the line.
   - Otherwise:
     - Return the remaining data or `NULL`.

The key difference is that **decision-making is front-loaded into invariant maintenance**, rather than scattered throughout the function.

---

### Comparison with the Current Approach

| Aspect | Current Implementation | Invariant-Based Approach |
|-----|----------------------|--------------------------|
| Control flow | Branch-heavy | Loop + post-condition |
| Reasoning | Case-by-case | Property-based |
| Debugging | Edge-case driven | Invariant violation driven |
| Read loop | Intertwined with return logic | Clearly separated |
| Mental load | High | Lower |

The current implementation already partially follows this idea but does not make the invariant explicit. As a result, reasoning about correctness requires tracing multiple paths instead of verifying a single maintained property.

---

### Would Invariant Programming Make `get_next_line` Easier?

**Yes, conceptually.**  
Invariant programming does not reduce the amount of code, but it reduces **cognitive complexity**.

For `get_next_line`, an invariant-based mindset:
- Makes EOF handling clearer
- Prevents accidental over-reading
- Clarifies when memory must be freed
- Exposes bugs as invariant violations rather than runtime surprises

However, for beginners, invariant programming can feel abstract. The challenge is not the technique itself, but learning to think in terms of maintained properties rather than step-by-step actions.

---

## Conclusion

The difficulty of `get_next_line` lies in managing persistent state under partial reads. An invariant-based approach reframes the problem from “handling cases” to “maintaining guarantees”.

Your implementation already aligns with this model implicitly. Making the invariant explicit would not change the behavior, but it would significantly simplify reasoning, debugging, and long-term correctness.

One of the biggest difficulty I encountered with this project is the mental shift between conditional programming to invariant programming. It caused me pain. Additionaly, all the memory bugs, segfaults and other C monsters traumatized me a little but it was for the best !
 
Thanks to Wissem Boussah *wboussah* for reviewing my logic and discussing edge cases and Ronan Gouachet *rgouachet* for the last and most vicious memory leak.


## Resources

- A hard limit has been set to prevent that the count_bytes transfered by the function read()
man 2 read gives : 
> On  Linux,  read()  (and similar system calls) will transfer at most 0x7ffff000 (2,147,479,552) bytes, returning the number of bytes
> actually transferred. 


- Learned to read valgrind output
https://bytes.usc.edu/cs104/wiki/valgrind/#conditional-jump-or-move-depends-on-uninitialized-values

- Learned gdb :
https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf