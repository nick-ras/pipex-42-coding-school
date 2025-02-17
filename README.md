# Pipex Project

## Description:
The **Pipex** project simulates a simplified version of a Unix pipeline, where multiple commands can be chained together, with the output of one command becoming the input for the next. The task is to implement a program that mimics the behavior of pipes in Unix, where a sequence of commands is executed, and the data flows from one command to another through pipes.

The goal is to implement a program that reads input from files or standard input, processes the data through a series of commands, and writes the output to standard output or a file. This requires knowledge of inter-process communication, handling file descriptors, and managing multiple processes.

## Project Requirements:

- **Input**:  
  The program accepts several arguments, including:
  - Two files: one for input and one for output.
  - A series of commands to execute on the input file.

- **Pipe Mechanism**:  
  The program needs to handle the piping of data from one command to the next, similar to how the shell would handle pipes (`|`).

- **Commands**:  
  The commands should be executed sequentially, with the output of one command feeding into the next.

- **Error Handling**:  
  The program should handle potential errors, such as invalid file paths or missing commands.

## Key Restrictions & Challenges:

- **File Descriptors**:  
  The project requires handling multiple file descriptors, particularly when using `fork()` to create processes. Each process needs to have the correct file descriptors set up so that they read from the correct input and write to the correct output. This involves using functions like `dup2()` to redirect input/output.

- **Forking Processes**:  
  You’ll need to create new processes using `fork()`, allowing each command to run in a separate process. Each child process should be executed with the correct program (using `execve()`), while the parent process waits for all children to complete.

- **Pipes for Communication**:  
  The most critical part of this project is the use of pipes to pass data between processes. This requires creating a pipe for each pair of consecutive commands. You’ll use `pipe()` to create the pipe and `dup2()` to redirect input/output through the pipe, ensuring the data flows correctly.

- **Command Execution**:  
  The project asks for the implementation of a simplified version of the shell’s `exec` family of functions. You will use `execve()` to replace the child process with the specified command. Handling the path resolution for commands (searching the PATH environment variable) is also required to mimic the shell behavior.

- **Error Handling**:  
  The program needs robust error handling, ensuring that any issues (such as missing files, invalid commands, or failed pipe creations) are reported correctly and gracefully without crashing the program. This involves checking the return values of system calls and using `perror()` to provide error messages.

- **Multiple Commands**:  
  Unlike basic piping between two commands, this project involves handling multiple commands in a pipeline, which adds complexity in managing file descriptors and pipes for each intermediate step.

## How to Run:

To compile and run the program, use the following commands:

1. **Compile the program**:  
```bash
make
```
2. **Run the Program**
Use the following command to run the program:

./pipex infile "command1" "command2" ... "commandN" outfile

**Arguments:**
infile: The input file that contains the data you want to process.
command1, command2, ..., commandN: The commands to run in a pipeline.
outfile: The output file where the final result will be written.
Example:
To use cat -e on the input file and then pass the result to grep a, and write the final output to outfile, run:

```bash
./pipex infile "cat -e" "grep a" outfile
```
The program will read from infile, run cat -e, then pass the output to grep a, and write the final result to outfile. If the outfile doesn't exist, it will be created.

