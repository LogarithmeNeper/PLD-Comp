#include "copy.h"

Copy::Copy(const int & _offsetSource, const int & _offsetDest, const string & destName, BasicBlock* bb) : IRInstr("copy",bb)
{
    this->offsetSource = _offsetSource;
    this->offsetDest = _offsetDest;
    this->destName = destName;
    this->bb = bb;

}

// The asm generation can be optimized for a char : we use movl to allow char to be initialized with int value
// We would need the type of the Source to be able to use movb.
void Copy::gen_asm(ostream & o) // x86 asm for now
{
    string destType = this->bb->cfg->get_var_type(this->destName);
    if(destType == "int"){
        o << "\tmovl -"
              << this->offsetSource
              << "(%rbp), %eax"
              << std::endl;
        o << "\tmovl %eax, -"
              << this->offsetDest
              << "(%rbp)"
              << std::endl;

    } else if(destType == "char") {
        o << "\tmovl -"
              << this->offsetSource
              << "(%rbp), %eax"
              << std::endl;
        o << "\tmovb %al, -"
              << this->offsetDest
              << "(%rbp)"
              << std::endl;
    } else if(destType == "int64") {
        o << "\tmovq -"
              << this->offsetSource
              << "(%rbp), %rax"
              << std::endl;
        o << "\tmovq %rax, -"
              << this->offsetDest
              << "(%rbp)"
              << std::endl;
    }
    
}

Copy::~Copy()
{

}

Copy::Copy()
{

}