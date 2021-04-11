// Personal include
#include "cmp_eq.h"

// Constructor of the class
Cmp_eq::Cmp_eq(const int &_offsetLeft, const int &_offsetRight, const string &_destinationLabel, const string &_comparativeSign, BasicBlock *bb) : IRInstr("cmp_eq", bb)
{
  this->offsetLeft = _offsetLeft;
  this->offsetRight = _offsetRight;
  this->destinationLabel = _destinationLabel;
  this->comparativeSign = _comparativeSign;
}

// Assembly generator for the comparison
// x86 asm for now
void Cmp_eq::gen_asm(ostream &o)
{
  o << "\tmovl -"
    << this->offsetLeft
    << "(%rbp), %eax"
    << std::endl; // moving the left variable in eax

  o << "\tcmpl -"
    << this->offsetRight
    << "(%rbp), %eax"
    << std::endl; // comparing the right variable with eax

  // accoring to the comparison
  if (comparativeSign == "==")
  {
    o << "\tjne "               // jump if not equal
      << this->destinationLabel // to the destination label
      << std::endl;
  }
  else if (comparativeSign == "<")
  {
    o << "\tjge "               // jump if greater or equal
      << this->destinationLabel // to the destination label
      << std::endl;
  }
  else if (comparativeSign == ">")
  {
    o << "\tjle "               // jump if less or equal
      << this->destinationLabel // to the destination label
      << std::endl;
  }
  else if (comparativeSign == "!=")
  {
    o << "\tje "                // jump if equal
      << this->destinationLabel // to the destination label
      << std::endl;
  }
}

// Destructor
Cmp_eq::~Cmp_eq()
{
}

// No-params constructor
Cmp_eq::Cmp_eq()
{
}