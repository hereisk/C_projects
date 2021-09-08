# zsh

Zsh is a command interpreters. It runs in a loop

-> 
|  Read: Read the command from standard input.
|  Parse: Separate the command string into a program and arguments.
|  Execute: Run the parsed command.
|-- (repeat)

Only basic command lines are to be executed; no pipes, redirections or any other advanced features.

There are two types of commands: zsh built-ins and binary.

The built-in commands include:

    1) "cd" is a command used to change the current working directory. In case the directory doesn't exist or the user doesn't have permissions to access the directory the command is not executed and a prompt is displayed.
        the cd command supports the following options:
        - "cd .." moves the user up one directory;
        - "cd -" switches to the previously visited directory;
        - "cd dir" (withouth a "/") puts the user in a subdirectory;
        - "cd /[path]" puts the user into the directory of the [path].
    
    2) "pwd" is a command to display the current working directory.

    3) "echo" is a command that outputs the strings that is being passed as arguments.
        To output a value of a global variable from the name of the variable should be preceded by $ character.
        If the variable is not found an empty line is printed out.

    4) "env" is a command to print a list of environment variables. No options are supported.

    5) "setenv" is a command that adds the variable name to the environment with the value value,
        if name does not already exist.  If name does exist in the environment, then its value is changed to value.

    6) "unsetenv" is a command that deletes the variable name from the environment.

    7) "which" is a command that takes one argument at a time and prints to stdout the full path of the executables
        that would have been executed when this argument had been entered at the shell prompt.
        It does this by searching for an executable or script in the directories listed in the environment variable PATH.
        No Options are supported

Binary commands are executed using the function execve().
The executables should be those found in the path, as indicated in the PATH variable.

To run a binary executable that is located in the current working directory the name of the executable should be preceded by "./".

When a binary command is being executed the programm follows the scheme below:

                     parent process
                     ---------------------------------------> wait() -----> resumes
                     |                                          ^
                     |                                          |
            fork() --                                           |
                     |                                          |
                     |                                          |
                     -----------> execve() -----------------> exit()
                     child process
                     

If a child process exited with a signal the signal number is displaed in the stdout but the error is not explained.


The project is completed by Konstantin Melkov.
