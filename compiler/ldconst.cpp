#include "ldconst.h"

// Constructor of the class
ldconst::ldconst(const int &_constValue, const int &_offset, const string &variableName, BasicBlock *bb) : IRInstr("ldconst", bb)
{
    this->constValue = _constValue;
    this->offset = _offset;
    this->variableName = variableName;
}

// Assembly generator
void ldconst::gen_asm(ostream &o) // x86 asm for now
{
    // Getting the type variable
    string variableType = this->bb->cfg->get_var_type(this->variableName);
    // depending on the type...
    if (variableType == "int")
    {
        o
            << "\tmovl $" // movl for int
            << this->constValue
            << ", -"
            << this->offset
            << "(%rbp)"
            << std::endl;
    }
    else if (variableType == "char")
    {
        o
            << "\tmovb $" // movb for char
            << this->constValue
            << ", -"
            << this->offset
            << "(%rbp)"
            << std::endl;
    }
}

// Destructor of the class
ldconst::~ldconst()
{
}

// No params constructor
ldconst::ldconst()
{
}