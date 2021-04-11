#include "and.h"

// Constructor
And::And(const int &_offsetLeft, const int &_offsetRight, const int &_offsetDest, BasicBlock *bb) : IRInstr("add", bb)
{
  this->offsetLeft = _offsetLeft;
  this->offsetRight = _offsetRight;
  this->offsetDest = _offsetDest;
}

// Method for assembly generation
// x86 asm for now
void And::gen_asm(ostream &o) 
{
  o
      << "\tmovl -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl; // Moving the left variable in eax
  o
      << "\tandl -"
      << this->offsetRight
      << "(%rbp), %eax"
      << std::endl; // ANDL
  o
      << "\tmovl %eax, -"
      << this->offsetDest
      << "(%rbp)"
      << std::endl; // Moving the result in the right offset
}

// Destructor
And::~And()
{
}

// No-params constructor
And::And()
{
}