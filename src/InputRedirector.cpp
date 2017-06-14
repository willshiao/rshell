#include "header/Command.h"
#include "header/InputRedirector.h"

using namespace std;

StatusCode InputRedirector::eval() {
  Command *leftCommand = static_cast<Command*>(this->left);

  #ifdef DEBUG
    Command *rightCommand = static_cast<Command*>(this->right);
    cout << "Piping input from " << rightCommand->getArgs().front() << endl;
  #endif
  return leftCommand->eval();
}
