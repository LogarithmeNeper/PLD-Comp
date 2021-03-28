#include "Copy.h"

Copy::Copy(const int & _offsetSource, const int & _offsetDest) : IRInstr("copy")
{
    this->offsetSource = _offsetSource;
    this->offsetDest = _offsetDest;

}

void Copy::gen_asm(ostream & o) // x86 asm for now
{
    std::cout << "\tmovl -"
              << this->offsetSource
              << "(%rbp), %eax"
              << std::endl;
    std::cout << "\tmovl %eax, -"
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