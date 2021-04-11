#include "call.h"

// Constructor
Call::Call(const int &_argumentOffset, std::string _functionName, BasicBlock *bb) : IRInstr("add", bb)
{
  this->argumentOffset = _argumentOffset;
  this->functionName = _functionName;
}

// Assembly generator for calling
// x86 asm for now
void Call::gen_asm(ostream &o)
{
  o
      << "\tmovl -"
      << this->argumentOffset
      << "(%rbp), %edi"
      << std::endl; // moving the argument in the edi registry
  o
      << "\tcall "
      << this->functionName
      << std::endl; // calling the function
  o
      << "\tmovl "
      << "$0, %eax"
      << std::endl; // returning the value
}

// Destructor
Call::~Call()
{
}

// No-params constructor
Call::Call()
{
}