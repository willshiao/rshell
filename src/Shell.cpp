#include <iostream>
#include <vector>

#include "header/Shell.h"

using namespace std;

Shell::Shell(vector<string> args) {
  cout << "Shell running with arguments: ";
  for(unsigned i = 0; i < args.size(); ++i) {
    cout << args.at(i) << ' ';
  }
  cout << endl;
}
