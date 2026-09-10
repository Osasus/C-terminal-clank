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

📝 Technical Note: clonk Improvements

Currently, the clonk text editor uses fixed-size stack arrays (char buffer[1024]) to handle file reading and line editing. While this works perfectly for small text files, it has a strict size limit.

Future Improvement: The memory handling should be refactored to use dynamic memory allocation. By utilizing fseek/ftell to find the exact file size and malloc/realloc to allocate the buffer (or by reading line-by-line using getline()), the editor will be able to safely handle files of any size without risking buffer truncation.
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