#include "add.h"

Add::Add(const int & _offsetLeft, const int & _offsetRight, const int & _offsetDest) : IRInstr("add")
{
    this->offsetLeft = _offsetLeft;
    this->offsetRight = _offsetRight;
    this->offsetDest = _offsetDest;

}

void Add::gen_asm(ostream & o) // x86 asm for now
{
    std::cout 
      << "\tmovl -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl;
    std::cout
      << "\taddl -"
      << this->offsetRight 
      << "(%rbp), %eax"
      << std::endl;
    std::cout
        << "\tmovl %eax, -" 
        << this->offsetDest
        << "(%rbp)" 
        << std::endl;

}

Add::~Add()
{

}

Add::Add()
{

}