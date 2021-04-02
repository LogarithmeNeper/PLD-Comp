#include "sub.h"

Sub::Sub(const int & _offsetLeft, const int & _offsetRight, const int & _offsetDest, BasicBlock* bb) : IRInstr("sub",bb)
{
    this->offsetLeft = _offsetLeft;
    this->offsetRight = _offsetRight;
    this->offsetDest = _offsetDest;

}

void Sub::gen_asm(ostream & o) // x86 asm for now
{
    o 
      << "\tmovl -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl;
    o
      << "\tsubl -"
      << this->offsetRight 
      << "(%rbp), %eax"
      << std::endl;
    o
        << "\tmovl %eax, -" 
        << this->offsetDest
        << "(%rbp)" 
        << std::endl;

}

Sub::~Sub()
{

}

Sub::Sub()
{

}