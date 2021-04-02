#include "mul.h"

Mul::Mul(const int & _offsetLeft, const int & _offsetRight, const int & _offsetDest, BasicBlock* bb) : IRInstr("sub",bb)
{
    this->offsetLeft = _offsetLeft;
    this->offsetRight = _offsetRight;
    this->offsetDest = _offsetDest;

}

void Mul::gen_asm(ostream & o) // x86 asm for now
{
    o 
      << "\tmovl -"
      << this->offsetRight
      << "(%rbp), %eax"
      << std::endl;
    o
      << "\timull -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl;
    o
        << "\tmovl %eax, -" 
        << this->offsetDest
        << "(%rbp)" 
        << std::endl;

}

Mul::~Mul()
{

}

Mul::Mul()
{

}