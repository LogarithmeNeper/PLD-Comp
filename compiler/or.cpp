#include "or.h"

// Constructor of the class
Or::Or(const int &_offsetLeft, const int &_offsetRight, const int &_offsetDest, BasicBlock *bb) : IRInstr("add", bb)
{
  this->offsetLeft = _offsetLeft;
  this->offsetRight = _offsetRight;
  this->offsetDest = _offsetDest;
}

// OR assembly generator in x86 ASM
void Or::gen_asm(ostream &o)
{
  o
      << "\tmovl -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl; // Moving left variable in eax
  o
      << "\torl -"
      << this->offsetRight
      << "(%rbp), %eax"
      << std::endl; // ORL right with eax
  o
      << "\tmovl %eax, -"
      << this->offsetDest
      << "(%rbp)"
      << std::endl; // Moving result
}

// Destructor of the class
Or::~Or()
{
}

// No-params constructor
Or::Or()
{
}