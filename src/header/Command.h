#ifndef RSHELL_COMMAND_H
#define RSHELL_COMMAND_H

#include <vector>
#include <string>
#include <iostream>
#include "Base.h"

using namespace std;

class Command : public Base {
 protected:
  vector<string> args;
  string inputFile, outputFile;  // Optional input/output files for streams
  bool appendOutput;

 public:
  int pipefd[2];  // File descriptor for pipe, [0] is read and [1] is write

  StatusCode runCommand(vector<string>& args);
  Command() {}
  explicit Command(vector<string> a)
      : args(a), inputFile(""), outputFile(""), appendOutput(false) {
    #ifdef DEBUG
      cout << "New command created with args: ";
      for(auto str : a) {
        cout << str << " ";
      }
      cout << endl;
    #endif
  }

  virtual StatusCode eval();
  virtual bool isEmpty();

  vector<string> getArgs() { return args; }
  void setOutputFile(string newOut) { outputFile = newOut; }
  void setInputFile(string newIn) { inputFile = newIn; }
  void setAppend(bool newState) { appendOutput = newState; }

 private:
  bool hasPipe() { return !(inputFile.empty() && outputFile.empty());  }
};


class NullCommand : public Command {
 public:
  NullCommand() {}
  explicit NullCommand(vector<string> a) : Command(a) {}
  virtual StatusCode eval() { return SUCCESS; }
  virtual bool isEmpty() { return true; }
};


class TestCommand : public Command {
 public:
  StatusCode runCommand(vector<string>& args);
  explicit TestCommand(vector<string> a) : Command(a) { }
};

#endif
