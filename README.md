**First Process**
**Deevankumar Gaddala**


#Compilation

gcc my_cmd.c - o my_cmd

#Execution

./my_cmd -e <pathname of an executable> -o "<String of command line options>" [-b | -f]

-e: Specify the pathname of the executable to run.
-o: Provide a string of command line options to pass to the executable.
-f: (Optional) Run the executable in the foreground (default mode).
-b: (Optional) Run the executable in the background.

#Options

-e: This option is mandatory and should be followed by the pathname of the executable you want to run.
-o: Use this option to provide a string of command line options to pass to the executable.
-b: Use this flag if you want to run the executable in the background.
-f: Use this flag if you want to run the executable in the foreground. This is the default mode if no -b or -f is specified.

#Examples

Running ./my_cmd named /usr/bin/ls with options "-l -a" in the foreground:
list out all the file as well as with hidden files(-a)

./my_cmd -e /usr/bin/ls -o "-l -a"

Running ./my_cmd named /bin/sleep with options 5 in the background:
makes the shell to sleep for 5 seconds

./my_cmd -e /bin/sleep -o 5


##How it Works

    The program parses command line arguments using get options to get the options -e, -o, -b, and -f.
    It checks for the mandatory -e option which specifies the pathname of the executable.
    The -o option allows you to provide a string of command line options to be passed to the executable.
    If the -b flag is used, the program runs the executable in the background.
    If the -f flag is used or no -b or -f flag is specified, the program runs the executable in the foreground (default).
    After parsing options, the program constructs the command line to execute using execve.
    If the execve call fails, an error message is displayed.
    If the executable runs in the background, the program displays the PID (Process ID) of the child process.
    If the executable runs in the foreground, the program waits for the child process to finish.
    After the child process exits, the program checks the exit status. If the exit code is non-zero, it prints the exit code. Otherwise, it indicates that the child process exited normally.

##Example Output

```$ ./my_cmd -e ./my_executable -o "-a -b -c"
Command Line: ./my_executable -a -b -c
Child Process exited normally with status 0
Child Process ID: 1234
Error Code of your C program: 0```

```$ ./my_cmd -e ./background_executable -o "-x -y -z" -b
Command Line: ./background_executable -x -y -z
Running in the background with PID: 5678
Error Code of your C program: 0```

###Error Handling

If the executable path is not provided with the -e option, an error message is displayed.
If fork() fails, a "Fork failed" error message is shown.
If execve() fails, an "Exec failed" error message is shown.
After execution, the program displays the error code of the C program.
