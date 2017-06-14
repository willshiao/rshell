#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

#include "header/Command.h"

using namespace std;

string fileToString(const string& fileName) {
  ifstream fs{fileName};
  ostringstream str_stream;

  if(fs.fail()) {
    cout << "Error opening " << fileName << endl;
  }

  fs >> str_stream.rdbuf();
  if (fs.fail() && !fs.eof()) {
    cout << "Error reading " << fileName << endl;
  }

  return str_stream.str();
}

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
  } else if(this->args.at(0) == "test") {
    return (new TestCommand(this->args))->eval();
  }
  StatusCode s = this->runCommand(this->args);
  #ifdef DEBUG
    if(s != SUCCESS) cout << "Invalid command." << endl;
  #endif
  return s;
}

StatusCode Command::runCommand(vector<string>& args) {
  // cout << "Running Command::runCommand" << endl;
  char ** argv = new char* [args.size() + 1];

  for(unsigned i = 0; i < args.size(); ++i) {
    argv[i] = const_cast<char*>(args.at(i).c_str());
  }
  argv[args.size()] = nullptr;

  pid_t pid = fork();
  int commandStatus;

  if(hasPipe()) {
    cout << "Output redirection detected" << endl;
    if(pipe(this->pipefd) == -1) {  // File descriptor for pipe, [0] is read and [1] is write
      cout << "Error creating pipe." << endl;
      delete[] argv;
      return IO_ERROR;
    }
  }

  if(pid == 0) {  // Child process
    if(!this->inputFile.empty()) {  // Read input file
      #ifdef DEBUG
        cout << "Reading from " << this->inputFile << endl;
      #endif
      string fileContents = fileToString(this->inputFile);

      #ifdef DEBUG
        cout << "Got file contents: " << fileContents << endl << endl;
      #endif

      dup2(this->pipefd[0], STDIN_FILENO);
      write(this->pipefd[1], fileContents.c_str(), fileContents.size());
      close(this->pipefd[1]);
    }
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

StatusCode TestCommand::runCommand(vector<string>& args) {
  if(args.size() < 2) {
    cout << "Invalid test command." << endl;
    return COMMAND_ERROR;
  } else if(args.size() == 2) {
    args.insert(args.begin() + 1, "-e");
  }
  bool status = false;
  struct stat buf;

  if(args.at(1) == "-e") {
    status = (stat(args.at(2).c_str(), &buf) != -1);
  } else if(args.at(1) == "-d") {
    status = (stat(args.at(2).c_str(), &buf) != -1) && S_ISDIR(buf.st_mode);
  } else if(args.at(1) == "-f") {
    status = (stat(args.at(2).c_str(), &buf) != -1) && S_ISREG(buf.st_mode);
  } else {
    cout << "Invalid test command." << endl;
    return COMMAND_ERROR;
  }
  cout << (status ? "(True)" : "(False)") << endl;
  return (status ? SUCCESS : IO_ERROR);
}

StatusCode TestCommand::eval() {
  return this->runCommand(this->args);
}
