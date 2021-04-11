#include "and.h"

And::And(const int & _offsetLeft, const int & _offsetRight, const int & _offsetDest, BasicBlock* bb) : IRInstr("add",bb)
{
    this->offsetLeft = _offsetLeft;
    this->offsetRight = _offsetRight;
    this->offsetDest = _offsetDest;

}

void And::gen_asm(ostream & o) // x86 asm for now
{
    o 
      << "\tmovl -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl;
    o
      << "\tandl -"
      << this->offsetRight 
      << "(%rbp), %eax"
      << std::endl;
    o
        << "\tmovl %eax, -" 
        << this->offsetDest
        << "(%rbp)" 
        << std::endl;

}

And::~And()
{

}

And::And()
{

}