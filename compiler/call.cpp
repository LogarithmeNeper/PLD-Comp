#include "call.h"

Call::Call(const int & _argumentOffset, std::string _functionName, const int & _offset, BasicBlock* bb) : IRInstr("call",bb)
{
    this->argumentOffset = _argumentOffset;
    this->functionName = _functionName;
    this->offset = _offset;

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
      << "%eax, -"
      << this->offset
      << "(%rbp)"
      << std::endl;

}

Call::~Call()
{

}

Call::Call()
{

}