# LinPwn

![LinPwn](https://github.com/3XPL017/LinEnum/blob/master/images/LinPwn.png)
<br>
## About
LinPwn is a interactive tool created to assist you in post exploitation enumeration and privilege escalation.<br>
It was written in a way that it only works for you once it has been placed on the target machine so if you are doing a CTF or a pentest anyone else on the machine can not use it to get a shell of their own.<br>
Obfuscation is up to you - LinPwn was not written using any type of obfuscation to make it easy to read and build on top of it so anyone on the target machine will be able to see what it is doing and who it is connecting to. So if you want obfuscation you will have to obfuscate it yourself.<br>
The text that will be printed out on the target machine after executing LinPwn will try to make it appear like this is just a innocent program called LinChat.<br>
When you type `exit` to exit out of LinPwn Segmentation fault will be printed out on the Target machine... this is not a real segmentation fault I simply just printed out the words to make it appear as such.
## Connection
To get a connection you must set your IP and port you want it to connect to in the class Connection<br>
First you must place the LinPwn binary on the target machine<br>
Then you can simply run `nc -lvp PORT` on your machine and then run LinPwn on the target machine to get a connection.
## About The Code
The IP and port are hardcoded this is intended(Read about to find out why)<br>
I am using `system()` instead of `execve()`This is because`execve()` doesnt return instead the LinPwn process will terminate upon exiting the shell so the use of `system()`is forced.<br>
I try to follow the google C++ style guide and C++ best practices to the best of my ability
## Usage
1. shell - This command runs /bin/sh<br>
Example usage:`Shell> id`<br> 
Type exit to return to LinPwn.<br>
2. readfile - This command will print the contents of a file.<br>
Example usage: `ReadFile> /etc/passwd`<br>
Type exit to return to LinPwn.<br>
3. enumerate - this command runs LinEnum.sh
Example usage: `>>> enumerate` 
## Compiling
I included a file called build.sh this is optional run `bash build.sh` to view the build options if you wish to use them.
## Why it was created
This idea is the one I had in mind when i created netpwn but since I did that in python things did not work like i wanted them to 
so i decided to go a different direction with it. I wanted to write some C++ and while thinking of a project
idea i remembered my original idea with netpwn. I knew it would go much better this time since it was going to be written in C++ where I have much more control over certain things.<br>
I also wanted to create a tool that I could use but no one else could like during a CTF for example.<br>
https://www.hackthebox.eu/ Is a CTF platform where multiple people are attacking the same machine at the same time and I have noticed when ever I put a reverseshell or something on the machine people will try to use it by changing the IP and port number which makes C++ the perfect language to use to be able to avoid this.<br>
Then I thought I not only want to to be useful for CTfs but also real world pentests this is what inspired LinChat 
 
