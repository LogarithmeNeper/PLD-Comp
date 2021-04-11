#include "xor.h"

// Constructor of the class
Xor::Xor(const int &_offsetLeft, const int &_offsetRight, const int &_offsetDest, BasicBlock *bb) : IRInstr("add", bb)
{
  this->offsetLeft = _offsetLeft;
  this->offsetRight = _offsetRight;
  this->offsetDest = _offsetDest;
}

// Assembly generator for the XOR instruction
void Xor::gen_asm(ostream &o) // x86 asm for no
{
  o
      << "\tmovl -"
      << this->offsetLeft
      << "(%rbp), %eax"
      << std::endl; // moving the left variable in the eax registry
  o
      << "\txorl -"
      << this->offsetRight
      << "(%rbp), %eax"
      << std::endl; // XORL the right variable with the current value in eax
  o
      << "\tmovl %eax, -"
      << this->offsetDest
      << "(%rbp)"
      << std::endl; // moving the result in the destination
}

// Destructor of the class
Xor::~Xor()
{
}

// No-params constructor
Xor::Xor()
{
}