# LinPwn

![LinPwn](https://github.com/3XPL017/LinEnum/blob/master/images/LinPwn.png)
<br>
## About
LinPwn is a interactive tool created to assist you in post exploitation enumeration and privilege escalation.<br>
## Connection
Set your IP and port you want it to connect to in the Connection class.<br>
Place the LinPwn binary on the target machine.<br>
Run `nc -lvp PORT` on your machine and then run LinPwn on the target machine to get a connection.
## Usage
1. shell - This command Executes /bin/sh<br>
Example usage: `(LinPwn: Shell) > id`<br> 
Type exit to return to LinPwn.<br>
2. readfile - This command will print the contents of a file.<br>
Example usage: `(LinPwn: ReadFile)> /etc/passwd`<br>
Type exit to return to LinPwn.<br>
3. enumerate - this command runs LinEnum.sh
Example usage:  `(LinPwn) > enumerate` 
4. download - This command downloads a file on the target machine
Example usage: `(LinPwn: Download) > https://exampleurl.com/file_to_download`
## Compiling
I included a file called build.sh this is optional run `bash build.sh` to view the build options if you wish to use them. 
 
