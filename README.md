# LinEnum
LinPwn rewritten in C++\n

[![LinPwn](https://github.com/3XPL017/LinEnum/blob/master/images/LinPwn.png)
\n
## About
LinPwn is a interactive backdoor 
\n
## Usage
1. shell - Executes /bin/sh after LinPwn outputs Executing /bin/sh you can start typing your commands. This behaves like a typical reverse shell there will be no prompt to fix this you have to run `python -c "import pty;pty.spawn('/bin/sh')"`like normal.
To return to LinPwn you must type exit and not ^C. ^C will terminate the LinPwn process and the connection will close. I havent figured out how to fix this yet... Also dont do ^Z `stty raw -echo` `fg` It will work like you expect it to until you type exit to return to LinPwn where your termianl will become unresponsive. The only way to fix this is to kill the process.
\n
## Compile

