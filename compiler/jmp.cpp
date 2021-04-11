#include "jmp.h"

// Constructor of the class
Jmp::Jmp(const string &_destinationLabel, BasicBlock *bb) : IRInstr("cmp_eq", bb)
{
  this->destinationLabel = _destinationLabel;
}

// Assembly generation in x86 for the jump
void Jmp::gen_asm(ostream &o)
{
  o << "\tjmp "
    << this->destinationLabel
    << std::endl;
}

// Destructor of the class
Jmp::~Jmp()
{
}

// No-params constructor
Jmp::Jmp()
{
}