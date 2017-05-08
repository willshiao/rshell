#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "header/Command.h"

using namespace std;

StatusCode Command::eval() {
  cout << "Eval started" << endl;
  vector<string> argv = { "-rf", "/mnt/c/Users/willshiao/Documents/GitHub/cs100-rshell/tmp" };
  cout << "Trying runCommand" << endl;
  runCommand("rm", argv);
  // TODO: implement Command eval() logic
  return SUCCESS;
}

StatusCode Command::runCommand(string path, const vector<string>& args) {
  cout << "Running Command::runCommand" << endl;
  char ** argv = new char* [args.size() + 2];

  argv[0] = const_cast<char*>(path.c_str());
  // strcpy(argv[0], path.c_str()); // 
  cout << "First element: " << argv[0] << endl;
  //  argv[0] = path.c_str();
  for(unsigned i = 0; i < args.size(); ++i) {
    // strcpy(argv[i + 1], args.at(i).c_str());
    argv[i + 1] = const_cast<char*>(args.at(i).c_str());
  }
  argv[args.size() + 1] = nullptr;


  cout << "Running command at " << path << " with first arg: " << argv[0] << endl;
  pid_t pid = fork();

  if(pid == 0) {  // Child process
    if(execvp(path.c_str(), argv) < 0) {
      cout << "Exec failed!" << endl;
      exit(1);
    }
    delete[] argv;
    exit(0);
  } else if(pid > 0) {  // Parent process
    waitpid(pid, nullptr, 0);
  } else {  // fork failed
    delete[] argv;
    return FORK_ERROR;
  }
  delete[] argv;
  return SUCCESS;
}
