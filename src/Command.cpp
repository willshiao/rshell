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

#define BUFFER_SIZE 100

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

  if(!this->outputFile.empty()) {
    #ifdef DEBUG
      cout << "Creating output pipe" << endl;
    #endif
    if(pipe(this->outputPipe) == -1) {
      cout << "Error creating output pipe" << endl;
    }
  }

  pid_t pid = fork();
  int commandStatus;

  if(pid == 0) {  // Child process
    if(!this->inputFile.empty()) {  // Read input file
      #ifdef DEBUG
        cout << "Creating input pipe" << endl;
      #endif
      if(pipe(this->inputPipe) == -1) {
        cout << "Error creating input pipe" << endl;
      }
      string fileContents = fileToString(this->inputFile);

      if(dup2(this->inputPipe[0], STDIN_FILENO) == -1) {
        cout << "Error creating input pipe in child" << endl;
      }
      write(this->inputPipe[1], fileContents.c_str(), fileContents.size());
      close(this->inputPipe[1]);
    }

    if(!this->outputFile.empty()) {
      close(this->outputPipe[0]);
      if(dup2(this->outputPipe[1], STDOUT_FILENO) == -1) {
        cout << "Error creating output pipe in child" << endl;
      }
      close(this->outputPipe[1]);
    }

    if(execvp(argv[0], argv) < 0) {
      cout << "No command \"" << argv[0] << "\" found." << endl;
      exit(1);
    }
    exit(0);
  } else if(pid > 0) {  // Parent process
    if(!this->outputFile.empty()) {
      close(this->outputPipe[1]);

      char buf[BUFFER_SIZE];
      ofstream ofs;

      if(this->appendOutput) {
        ofs.open(this->outputFile.c_str(), ios::app);
      } else {
        ofs.open(this->outputFile.c_str());
      }

      #ifdef DEBUG
        cout << "Writing to " << this->outputFile << endl;
      #endif

      ssize_t bytesRead;
      while((bytesRead = read(this->outputPipe[0], &buf, BUFFER_SIZE)) > 0) {
        if(bytesRead < BUFFER_SIZE) buf[bytesRead] = '\0';
        ofs << buf;
      }
      close(this->outputPipe[0]);
      cout << endl;
    }

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
