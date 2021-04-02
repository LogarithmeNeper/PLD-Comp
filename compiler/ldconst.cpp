#include "ldconst.h"

ldconst::ldconst(const int & _constValue, const int & _offset, BasicBlock* bb) : IRInstr("ldconst",bb)
{
    this->constValue = _constValue;
    this->offset = _offset;

}

void ldconst::gen_asm(ostream & o) // x86 asm for now
{
    o
        << "\tmovl $" 
        << this->constValue 
        << ", -" 
        << this->offset 
        << "(%rbp)" 
        << std::endl;

}

ldconst::~ldconst()
{

}

ldconst::ldconst()
{

}