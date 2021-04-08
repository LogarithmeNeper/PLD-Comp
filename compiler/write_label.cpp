#include "write_label.h"

Write_label::Write_label(const string & _destinationLabel, BasicBlock* bb) : IRInstr("cmp_eq",bb)
{
    this->destinationLabel = _destinationLabel;
}

void Write_label::gen_asm(ostream & o) // x86 asm for now
{       
        o << this->destinationLabel
          << ":"
          << std::endl;
}

Write_label::~Write_label()
{

}

Write_label::Write_label()
{

}