#include "jmp.h"

Jmp::Jmp(const string & _destinationLabel, BasicBlock* bb) : IRInstr("cmp_eq",bb)
{
    this->destinationLabel = _destinationLabel;
}

void Jmp::gen_asm(ostream & o) // x86 asm for now
{       
        o << "\tjmp "
          << this->destinationLabel
          << std::endl;
}

Jmp::~Jmp()
{

}

Jmp::Jmp()
{

}