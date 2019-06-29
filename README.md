# LinPwn

![LinPwn](https://github.com/3XPL017/LinEnum/blob/master/images/LinPwn.png)
<br>
## About
LinPwn is a post exploitation tool designed to be an interactive backdoor.<br>
It was written in a way that it only works for you once it has been placed on the target machine so if you are doing a CTF or a pentest anyone else on the machine can not use it to get a shell of their own.<br>
Obfuscation is up to you - LinPwn was not written using any type of obfuscation to make it easy to read and build on top of it so anyone on the target machine will be able to see what it is doing and who it is connecting to. So if you want obfuscation you will have to obfuscate it yourself.<br>
The LinPwn process will not terminate on a successful connection. If it does terminate the connection was not successful.
## Connection
To get a connection you must set your IP and port you want it to connect to in the class Connection<br>
First you must place the LinPwn binary on the target machine<br>
Then you can simply run `nc -lvp PORT` on your machine and then run LinPwn on the target machine to get a connection.
## About The Code
The IP and port are hardcoded this is intended(Read about to find out why)<br>
I am using `system()` instead of `execve()`This is because`execve()` doesnt return instead the LinPwn process will terminate upon exiting the shell so the use of `system()`is forced.<br>
I try to follow the google C++ style guide and C++ best practices to the best of my ability
## Usage
1. shell - Type `shell` in LinPwn to run this command.<br>
Example usage:`Shell> id`<br> 
Type exit to return to LinPwn.<br>
2. readfile - Type `readfile` in LinPwn to run this command.<br>
Example usage: `ReadFile> /etc/passwd` <br>
This command will print the contents of a file.<br>
Type exit to return to LinPwn.<br>
## Compile
Compiling is completely up to you.<br>
This is because there are different ways you might want it to be compiled.

