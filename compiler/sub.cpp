#include "sub.h"

Sub::Sub(const int & _offsetLeft, const int & _offsetRight, const int & _offsetDest) : IRInstr("sub")
{
    this->offsetLeft = _offsetLeft;
    this->offsetRight = _offsetRight;
    this->offsetDest = _offsetDest;

}

void Sub::gen_asm(ostream & o) // x86 asm for now
{
    std::cout 
      << "\tmovl -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl;
    std::cout
      << "\tsubl -"
      << this->offsetRight 
      << "(%rbp), %eax"
      << std::endl;
    std::cout
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