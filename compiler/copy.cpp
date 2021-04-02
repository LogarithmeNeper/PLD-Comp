#include "copy.h"

Copy::Copy(const int & _offsetSource, const int & _offsetDest, BasicBlock* bb) : IRInstr("copy",bb)
{
    this->offsetSource = _offsetSource;
    this->offsetDest = _offsetDest;

}

void Copy::gen_asm(ostream & o) // x86 asm for now
{
    o << "\tmovl -"
              << this->offsetSource
              << "(%rbp), %eax"
              << std::endl;
    o << "\tmovl %eax, -"
              << this->offsetDest
              << "(%rbp)"
              << std::endl;

}

Copy::~Copy()
{

}

Copy::Copy()
{

}