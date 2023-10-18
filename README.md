# 0x16. C - Simple Shell

A basic Unix-like shell with limited functionality. This project aims to implement fundamental shell features, including command execution, and basic built-in commands like cd and exit. The shell should provide a simple command-line interface and demonstrate a foundational understanding of process management and input/output handling.r

## UNIX-LIKE SHELL

![UNIX SHELL](https://fiverr-res.cloudinary.com/images/t_main1,q_auto,f_auto,q_auto,f_auto/gigs/3582305/original/shellProgramming/write-linux-or-unix-shell-scripts-bash.jpg)

## Authors

- [@cruso003](https://github.com/cruso003/)
- [@ElizabethAgada](https://github.com/ElizabethAgada)

## Language Used

![UNIX SHELL](https://www.techbaz.org/Course/img/c-logo.png)

## Compiliation

All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options

```bash
   -Wall -Werror -Wextra -pedantic -std=gnu89
```

## Lessons Learned

Creating a shell is a complex project that involves various aspects of operating systems, system calls, string manipulation, and command execution. Here are some lessons that can be learned from this project:

1. **Understanding the Unix Shell**: Developing a shell requires a deep understanding of how the Unix shell works. It's important to be familiar with the basic concepts of processes, system calls, and how a shell interacts with the operating system.

2. **String Manipulation**: String manipulation is a fundamental part of parsing and interpreting commands. You need to be proficient in handling strings, splitting them into tokens, and performing substitutions or replacements.

3. **Process Management**: The shell must be able to create and manage processes. Understanding the `fork()`, `exec()`, and `wait()` system calls is essential.

4. **Error Handling**: Proper error handling is crucial. Handling and reporting errors in system calls, memory allocation, and other operations is important for the robustness of the shell.

5. **Environmental Variables**: Managing environment variables like `PATH`, `HOME`, `OLDPWD`, etc., is essential for creating a functional shell.

6. **Built-In Commands**: Implementing built-in commands like `cd`, `exit`, `echo`, and handling them correctly is a key part of a shell.

7. **Signal Handling**: Dealing with signals, such as Ctrl+D (`EOF`), is necessary for a shell to provide a good user experience.

8. **Dynamic Memory Allocation**: Proper use of dynamic memory allocation functions like `malloc` and freeing allocated memory with `free` is important to avoid memory leaks.

9. **Command Line Arguments**: Understanding how to process command-line arguments passed to the shell is crucial for usability.

10. **Testing**: Extensive testing is required to ensure that the shell works as expected. This includes testing various commands, pipes, and redirections.

11. **Documentation**: Good documentation of our code and the project as a whole is important, especially if others are expected to work on or understand the code.

12. **Version Control**: Using a version control system (e.g., Git) is a good practice. It allows us to track changes, collaborate, and revert to previous versions if needed.

13. **Iterative Development**: Building a shell is a complex project, and it's usually best done in an iterative manner. Start with basic functionality and gradually add more features.

14. **Research and References**: Be prepared to do a lot of research. We'll need to consult documentation, books, and online resources to understand various aspects of shell development.

15. **Security**: Keep in mind that security is a concern, especially if we plan to use the shell in a real environment. Avoid command injection vulnerabilities and protect sensitive data.

Overall, developing a shell is a challenging but rewarding project that deepens our understanding of how the operating system interacts with user commands. It's a great way to learn about low-level system programming and the intricacies of command-line interfaces.

## Basic information

Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
