You are expected to create a simple program in C/C + + that implements an
application using RPC as the layer of communication between the client and the server. The
project consists of three separate parts; local procedure, remote procedure, and logging. The
local procedure part includes the creation of several processes and executing a binary file. The
remote procedure part includes the creation of remote processes and executing a binary file.
The logging part, which is a bonus, includes remotely logging of the inputs and outputs.
The project will be evaluated automatically in the Linux environment (Ubuntu Version
20.04.1) with either gcc/g++ or cc compiler (Version 9.3.0). Please follow all the requirements
specified below. Your submissions will be compiled and tested via automatic scripts. Therefore,
it is crucial that you follow the protocol (i.e. the rules and the specifications) defined in the
project document. Failure in the compilation and/or execution is your responsibility. You
should use the file names, parameters, etc. as mentioned in the project specifications.

The project focuses on an unknown binary file, namely blackbox. The blackbox is an executable
file that you should use without knowing the source code. So, you won’t be able to know exactly
what is happening in the blackbox. What you should know is that it takes some input from
the console (i.e., by reading stdin, not command line parameters) and it displays some output
based on the given input values. The main idea of the project is to automate the process using
this blackbox. However, the project is to be designed in a flexible manner. So, do not develop
your code depending on a specific binary file. There are 3 steps of the project that are built on
top of each other:
• In Part A, you will run the blackbox with the given inputs, get the output from the blackbox
and redirect it as requested.
• In Part B, you will upgrade the wrapper designed in Part A to be a Remote Procedural Call
(RPC) server that executes the blackbox for any client that requests.
• In part C, you will add one more process to the project which will log the client activity in
a different machine via a given Port. You are expected to have three independent submissions; Part A, Part B, and Part C with
the properties specified below. Note that, the input and output standards of the blackbox are
going to be defined and an example blackbox program is going to be provided to you but don’t
forget that your project should work on not only the given binary file but any blackbox. We
might replace blackbox with some other binary while grading.

part a:
• Your main program should create a child process that executes the given blackbox.
• The parent process should read the input from stdin (e.g., using scanf() function) and
pass it to blackbox as input. Note that blackbox takes two integer values from stdin as
input, and either produces one integer to stdout or an error text to stderr as output.
Redirecting input and output files at the command line by using redirection operators
(”<” and ”>”) will not be accepted; you must capture the input and output of blackbox
• Your main program should capture the output of the blackbox and print it to the
specified file in the following format:
<input1> <input2> <output1>

part b:
• Your client program should call an RPC function in the Server, passing three parameters:
path, number1, and number2.
• Your server program should be ready for clients to run the RPC function given above.
This function should create a child process that executes the given blackbox and return
the response to the Client.
• Your client program then should print the response to the specified file in the following
format:
<input1> <input2> <output1>

Input
For Part A;
1. The part a.out program takes two command line arguments:
blackbox: Path of the executable file
part a output.txt: Path of the output file
• For Part B;
1. The part b server.out program takes no argument and runs in the background.
2. The part b client.out program takes three command line arguments:
blackbox: Path of the executable file
part b output.txt: Path of the output file
SERVER IP ADDRESS: IP address of the server

Output
The blackbox returns an integer if the process executes successfully, and an error message if the
process fails for some reason. You should capture the output and write SUCCESS: or FAIL:
to the output file accordingly.