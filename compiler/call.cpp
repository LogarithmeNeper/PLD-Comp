#include "call.h"

Call::Call(const int & _argumentOffset, std::string _functionName, BasicBlock* bb) : IRInstr("add",bb)
{
    this->argumentOffset = _argumentOffset;
    this->functionName = _functionName;

}

void Call::gen_asm(ostream & o) // x86 asm for now
{
    o 
      << "\tmovl -"
      << this->argumentOffset
      << "(%rbp), %edi"
      << std::endl;
    o
      << "\tcall "
      << this->functionName
      << std::endl;
    o
      << "\tmovl "
      << "$0, %eax"
      << std::endl;

}

Call::~Call()
{

}

Call::Call()
{

}