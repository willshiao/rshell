#include "header/Command.h"
#include "header/InputRedirector.h"

using namespace std;

StatusCode InputRedirector::eval() {
  Command *leftCommand = static_cast<Command*>(this->left);
  Command *rightCommand = static_cast<Command*>(this->right);

  #ifdef DEBUG
    cout << "Piping input from " << rightCommand->getArgs().front() << endl;
  #endif

  leftCommand->setInputFile(rightCommand->getArgs().front());
  return leftCommand->eval();
}
