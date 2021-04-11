#include "sub.h"

// Constructor of the class
Sub::Sub(const int &_offsetLeft, const int &_offsetRight, const int &_offsetDest, BasicBlock *bb) : IRInstr("sub", bb)
{
  this->offsetLeft = _offsetLeft;
  this->offsetRight = _offsetRight;
  this->offsetDest = _offsetDest;
}

// Assembly generator for the substraction
void Sub::gen_asm(ostream &o) // x86 asm for now
{
  o
      << "\tmovl -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl; // Moving the left value in eax
  o
      << "\tsubl -"
      << this->offsetRight
      << "(%rbp), %eax"
      << std::endl; // SUBL the right value
  o
      << "\tmovl %eax, -"
      << this->offsetDest
      << "(%rbp)"
      << std::endl; // moving to the right variable
}

// Destructor of the class
Sub::~Sub()
{
}

// No-params constructor
Sub::Sub()
{
}