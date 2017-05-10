#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>

#include "header/Command.h"

using namespace std;

bool Command::isEmpty() {
  if(this->args.size() == 0) return true;
  // if(this->args.size() > 1) return false;
  return false;
}

StatusCode Command::eval() {
  if(this->args.size() < 1 || this->args.at(0) == "") {
    cout << "Missing command." << endl;
    return UNKNOWN_ERROR;
  }
  if(this->args.at(0) == "exit") {
    exit(0);
  }
  StatusCode s = runCommand(this->args);
  #ifdef DEBUG
    if(s != SUCCESS) cout << "Invalid command." << endl;
  #endif
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
      cout << "No command \"" << argv[0] << "\" found." << endl;
      exit(1);
    }
    exit(0);
  } else if(pid > 0) {  // Parent process
    waitpid(pid, &commandStatus, 0);
    delete[] argv;
    if(WEXITSTATUS(commandStatus) == 0) return SUCCESS;
    #ifdef DEBUG
      cout << "Unknown error!" << endl;
    #endif
    return UNKNOWN_ERROR;
  } else {  // fork failed
    delete[] argv;
    #ifdef DEBUG
      cout << "Fork error!" << endl;
    #endif
    return FORK_ERROR;
  }
}
