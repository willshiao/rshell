#include <string>
#include <vector>
#include "header/Shell.h"

using namespace std;

int main(int argc, char** argv) {
  // Convert argv to string vector
  vector<string> args(argc);
  for(int i = 0; i < argc; ++i) {
    args.at(i) = argv[i];
  }

  Shell s(args);
  s.run();

  return 1;  // Non-zero exit code if exit command not used
}
