#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "header/Command.h"

using namespace std;

StatusCode Command::eval() {
  StatusCode s = runCommand(this->args);
  if(s != SUCCESS) cout << "Failed to run command" << endl;
  return s;
}

StatusCode Command::runCommand(const vector<string>& args) {
  // cout << "Running Command::runCommand" << endl;
  char ** argv = new char* [args.size() + 1];

  for(unsigned i = 0; i < args.size(); ++i) {
    argv[i] = const_cast<char*>(args.at(i).c_str());
  }
  argv[args.size()] = nullptr;

  pid_t pid = fork();
  int commandStatus;

  if(pid == 0) {  // Child process
    if(execvp(argv[0], argv) < 0) {
      cout << "Exec failed!" << endl;
      exit(1);
    }
    exit(0);
  } else if(pid > 0) {  // Parent process
    waitpid(pid, &commandStatus, 0);
    // delete[] argv;
    if(WIFEXITED(commandStatus) != 0) return SUCCESS;
    return UNKNOWN_ERROR;
  } else {  // fork failed
    // delete[] argv;
    return FORK_ERROR;
  }
}
