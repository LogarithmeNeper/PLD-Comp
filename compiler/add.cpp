// Personal include

#include "add.h"

// Constructor of the class
Add::Add(const int &_offsetLeft, const int &_offsetRight, const int &_offsetDest, BasicBlock *bb) : IRInstr("add", bb)
{
  this->offsetLeft = _offsetLeft;
  this->offsetRight = _offsetRight;
  this->offsetDest = _offsetDest;
}

// Method for assembly generation
// x86 asm for now
void Add::gen_asm(ostream &o)
{
  o
      << "\tmovl -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl; // moving the variable
  o
      << "\taddl -"
      << this->offsetRight
      << "(%rbp), %eax"
      << std::endl; // adding the variable
  o
      << "\tmovl %eax, -"
      << this->offsetDest
      << "(%rbp)"
      << std::endl; // moving the result in the registry
}

// Destructor
Add::~Add()
{
}

// No-params constructor
Add::Add()
{
}