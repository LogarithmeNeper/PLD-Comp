#include "write_label.h"

// Constructor of the class
Write_label::Write_label(const string &_destinationLabel, BasicBlock *bb) : IRInstr("cmp_eq", bb)
{
  this->destinationLabel = _destinationLabel;
}

// Assembly generator for a label
void Write_label::gen_asm(ostream &o) // x86 asm for now
{
  o << this->destinationLabel
    << ":"
    << std::endl; // Writing the label
}

// Destructor of the class
Write_label::~Write_label()
{
}

// No-params constructor
Write_label::Write_label()
{
}