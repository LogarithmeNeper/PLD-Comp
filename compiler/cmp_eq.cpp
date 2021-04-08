#include "cmp_eq.h"

Cmp_eq::Cmp_eq(const int & _offsetLeft, const int & _offsetRight, const string & _destinationLabel, BasicBlock* bb) : IRInstr("cmp_eq",bb)
{
    this->offsetLeft = _offsetLeft;
    this->offsetRight = _offsetRight;
    this->destinationLabel = _destinationLabel;
}

void Cmp_eq::gen_asm(ostream & o) // x86 asm for now
{
        o << "\tmovl -"
          << this->offsetRight
          << "(%rbp), %eax"
          << std::endl;

        o << "\tcmpl -"
            << this->offsetLeft
            << "(%rbp), %eax"
            << std::endl;
        
        o << "\tjne "
          << this->destinationLabel
          << std::endl;
}

Cmp_eq::~Cmp_eq()
{

}

Cmp_eq::Cmp_eq()
{

}