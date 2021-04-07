#include "cmp_eq.h"

Cmp_eq::Cmp_eq(const int & _offsetLeft, const int & _offsetRight, const string & destinationLabel, BasicBlock* bb) : IRInstr("cmp_eq",bb)
{
    this->offsetLeft = _offsetLeft;
    this->offsetRight = _offsetRight;
}

// The asm generation can be optimized for a char : we use movl to allow char to be initialized with int value
// We would need the type of the Source to be able to use movb.
void Cmp_eq::gen_asm(ostream & o) // x86 asm for now
{
        o << "\tcmpl -"
              << this->offsetLeft
              << "(%rbp), "
              << this->offsetRight
              << "(%rbp)"
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