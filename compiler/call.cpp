#include "call.h"

// Constructor
Call::Call(const int & _argumentOffset, std::string _functionName, const int & _offset, BasicBlock* bb) : IRInstr("call",bb)
{
    this->argumentOffset = _argumentOffset;
    this->functionName = _functionName;
    this->offset = _offset;

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
      << "%eax, -"
      << this->offset
      << "(%rbp)"
      << std::endl;

}

// Destructor
Call::~Call()
{
}

// No-params constructor
Call::Call()
{
}