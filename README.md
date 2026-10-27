⚙️ Clank Shell

Clank is a custom, lightweight Unix-like shell and command-line interface written entirely in C. It implements standard shell utilities from scratch (like ls, cd, and cat) as well as some unique custom commands.

Note: This was a collaborative group project. While we built the core shell and many commands together, I specifically developed the echo, touch, and clonk commands.
🛠️ Features & Commands

Clank features a wide variety of built-in commands located in the commands/ directory:

    Navigation & Files: cd, ls, pwd, mkdir, cp, mv, rm

    Text & Output: cat, head, echo

    System & Shell: clear, history, help, man, exit

    External Execution: run (A powerful wrapper that allows you to execute external system binaries from within Clank, meaning you can easily launch tools like vim, nano, or bash!)

    Development & Meta: cog (A built-in development utility that can automatically pull Git updates, clean, recompile, and hot-restart the shell from within itself).

    Custom/Fun: clonk (text editor), clank, captcha, xplode

👨‍💻 My Contributions

I was primarily responsible for implementing the following built-in commands:

    echo (echo.c)
    Prints text/arguments back to the terminal. Handles argument iteration and spacing cleanly.

    touch (touch.c)
    Creates a new, empty file with the specified name. It utilizes access() to ensure it doesn't accidentally overwrite or modify an already existing file.

    clonk (clonk.c)
    A simple, built-in, line-based text editor. It reads a file, prints its contents alongside line numbers, and prompts the user to select a specific line to overwrite or edit.



🔍 Systems & Security Retrospective

Looking back at this project with my current background in cybersecurity and software development, several architectural and memory management decisions serve as valuable technical takeaways:

🛡️ Memory Safety & Data Structures in `clonk`

* File Size Constraints & Buffer Limits: The editor currently reads and edits files using fixed stack buffers (`char buffer[1024]`), inherently restricting it to small text files. A production refactor should dynamically allocate buffer sizes on the heap using `fseek()`/`ftell()` or read lines dynamically with `getline()`.

* Stack Bounds & Buffer Overflows (CWE-121): To append missing lines past EOF, the initial implementation relied on an iterative/recursive helper passing a small stack array (`add_line[] = "\n"`). This approach is prone to stack-smashing risks if user input exceeds available stack alignment. Eliminating the recursion in favor of an iterative append loop—or managing lines dynamically—removes this vulnerability entirely.

* Architectural Refactoring: Rather than performing in-place string manipulation on a single flat buffer, the editor should be refactored to use a dynamic array of line pointers (`char** lines`) allocated on the heap with `malloc()`/`realloc()`, or a dedicated data structure like a Gap Buffer. This isolates lines, enables safe line insertions, and prevents cross-buffer memory corruption.


⚙️ POSIX Terminal Control (Raw vs. Cooked Mode)

* I/O Mode Switching: To capture arrow keys and raw keypresses byte-by-byte for screen navigation, the terminal is placed into Raw Mode.

* Safe Line Editing: When clonk prompts the user to edit a specific line, the editor temporarily restores Cooked Mode. This hands input buffering back to the kernel's TTY driver so that echoing, Backspace handling, and standard line-editing work seamlessly with `fgets()`, before switching back to Raw mode.


💬 Command Evolution in `echo`

* Environment Variable Expansion: Environment variable support was introduced to Clank Shell after `echo` was initially written. The command can be further enhanced to handle variable expansion (`$VAR`). Architecturally, this variable substitution is best handled upstream in the shell's core lexer/parser before arguments (`argv`) are dispatched, ensuring uniform variable expansion across all commands.



🚀 Getting Started
Prerequisites

    GCC (GNU Compiler Collection)

    Make

    Git (optional, required if using the cog update command)

Building and Running

This project features a highly automated Makefile that handles code generation and linking. All compiled objects and generated files are neatly output to a build/ directory.

    Clone the repository and navigate into the root folder.

    Compile the code:
    code Bash

    make

    (You can also use make debug to build with debug symbols, or make clean to wipe the build directory).

    Run the compiled shell:
    code Bash

    ./build/clank

(Type help or man <command> once inside the shell to see how to use the available tools!)
🧠 Architecture Note: The Smart Makefile

One of the best features of this project is its Makefile. It automatically discovers any .c files placed in the commands/ directory. During the build process, it dynamically generates a commands.h and commands_gen.c file containing a central command registry.

This means adding a new command is completely frictionless: you simply drop a new mycommand.c into the commands/ folder containing a clank_mycommand() and man_mycommand() function, and the Makefile does the rest of the linking automatically!
📁 Project Structure
code Text

clank-main/
├── commands/         # Source code for all individual shell commands
│   ├── clonk.c       # (My contribution)
│   ├── echo.c        # (My contribution)
│   ├── touch.c       # (My contribution)
│   ├── cog.c         # Meta-tool for recompiling/updating Clank
│   ├── run.c         # Exec wrapper for external binaries (vim, bash, etc.)
│   └── ... 
├── utils/            # Helper functions and utilities (input handling, etc.)
├── Makefile          # Build instructions and automatic registry generator
├── main.c            # The main shell loop and entry point
└── README.md