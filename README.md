Pipex Project
Description:
The Pipex project simulates a simplified version of a Unix pipeline, where multiple commands can be chained together, with the output of one command becoming the input for the next. The task is to implement a program that mimics the behavior of pipes in Unix, where a sequence of commands is executed, and the data flows from one command to another through pipes.

The goal is to implement a program that reads input from files or standard input, processes the data through a series of commands, and writes the output to standard output or a file. This requires knowledge of inter-process communication, handling file descriptors, and managing multiple processes.

Project Requirements:
Input: The program accepts several arguments, including:
Two files: one for input and one for output.
A series of commands to execute on the input file.
Pipe Mechanism: The program needs to handle the piping of data from one command to the next, similar to how the shell would handle pipes (|).
Commands: The commands should be executed sequentially, with the output of one command feeding into the next.
Error Handling: The program should handle potential errors, such as invalid file paths or missing commands.
Key Restrictions & Challenges:
File Descriptors:
The project requires handling multiple file descriptors, particularly when using fork() to create processes. Each process needs to have the correct file descriptors set up so that they read from the correct input and write to the correct output. This involves using functions like dup2() to redirect input/output.

Forking Processes:
You’ll need to create new processes using fork(), allowing each command to run in a separate process. Each child process should be executed with the correct program (using execve()), while the parent process waits for all children to complete.

Pipes for Communication:
The most critical part of this project is the use of pipes to pass data between processes. This requires creating a pipe for each pair of consecutive commands. You’ll use pipe() to create the pipe and dup2() to redirect input/output through the pipe, ensuring the data flows correctly.

Command Execution:
The project asks for the implementation of a simplified version of the shell’s exec family of functions. You will use execve() to replace the child process with the specified command. Handling the path resolution for commands (searching the PATH environment variable) is also required to mimic the shell behavior.

Error Handling:
The program needs robust error handling, ensuring that any issues (such as missing files, invalid commands, or failed pipe creations) are reported correctly and gracefully without crashing the program. This involves checking the return values of system calls and using perror() to provide error messages.

Multiple Commands:
Unlike basic piping between two commands, this project involves handling multiple commands in a pipeline, which adds complexity in managing file descriptors and pipes for each intermediate step.




How to run:
In order to use it you have to run "make" and then ex run ./pipex infile "cat -e" "grep a" outfile.
The infile has to exist, but the outfile will be made by program if not existing.

How it works:
The program opens the infile which ex gets the filedesriptor "3". In first child process it duplicates fd 3 into STDIN, and then uses execve with the path of the command "cat" and options "cat" and "-e".
Before using execve i made a pipe and duplicated the write end of the pipe into STDOUT (which closes the STDOUT)
The second child read from the read end of the pipe and uses execve on the second argument (new path and options) and output into outfile. Before that, i duplicated fd of outfile into STOUT.
To test run do as shown in line 2.
