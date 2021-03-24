#include "ldconst.h"

ldconst::ldconst(const int & _constValue, const int & _offset)
{
    this->constValue = _constValue;
    this->offset = _offset;

}

void gen_asm(ostream & o)
{


}

ldconst::~ldconst(){}
ldconst::ldconst(){}