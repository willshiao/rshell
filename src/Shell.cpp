#include <iostream>
#include <vector>

#include "header/Shell.h"
#include "header/StatusCode.h"

using namespace std;

Shell::Shell(vector<string> args) {
  if(args.size() < 1) return;
  cout << "Shell intialized with arguments: ";
  for(unsigned i = 0; i < args.size(); ++i) {
    cout << args.at(i) << ' ';
  }
  cout << endl;
}

StatusCode Shell::run() {
  string line;
  while(true) {
    cout << "$ ";
    getline(cin, line);
    cout << "Got input: " << line << endl;
  }
  return SUCCESS;
}
