#include "ldconst.h"

ldconst::ldconst(const int & _constValue, const int & _offset) : IRInstr("ldconst")
{
    this->constValue = _constValue;
    this->offset = _offset;

}

void ldconst::gen_asm(ostream & o)
{
    o << "\tmovl $" << this->constValue << ", -" << this->offset << "(%rbp)" << std::endl;

}

ldconst::~ldconst()
{

}

ldconst::ldconst()
{

}