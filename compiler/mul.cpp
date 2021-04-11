#include "mul.h"

// Constructor of the class
Mul::Mul(const int &_offsetLeft, const int &_offsetRight, const int &_offsetDest, BasicBlock *bb) : IRInstr("sub", bb)
{
  this->offsetLeft = _offsetLeft;
  this->offsetRight = _offsetRight;
  this->offsetDest = _offsetDest;
}

// Multiplication assembly generator
void Mul::gen_asm(ostream &o) // x86 asm for now
{
  o
      << "\tmovl -"
      << this->offsetRight
      << "(%rbp), %eax"
      << std::endl; // Moving the variable
  o
      << "\timull -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl; // IMULL for multiplying
  o
      << "\tmovl %eax, -"
      << this->offsetDest
      << "(%rbp)"
      << std::endl; // Moving the result
}

// Destructor of the class
Mul::~Mul()
{
}

// Constructor of the class
Mul::Mul()
{
}