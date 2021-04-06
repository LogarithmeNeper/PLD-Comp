#include "ldconst.h"

ldconst::ldconst(const int & _constValue, const int & _offset,const string & variableName, BasicBlock* bb) : IRInstr("ldconst",bb)
{
    this->constValue = _constValue;
    this->offset = _offset;
    this->variableName = variableName;
    this->bb = bb;
}

void ldconst::gen_asm(ostream & o) // x86 asm for now
{
    string variableType = this->bb->cfg->get_var_type(this->variableName);
    if(variableType == "int") {
        o
        << "\tmovl $" 
        << this->constValue 
        << ", -" 
        << this->offset 
        << "(%rbp)" 
        << std::endl;
    } else if (variableType == "char") {
        o
        << "\tmovb $" 
        << this->constValue 
        << ", -" 
        << this->offset 
        << "(%rbp)" 
        << std::endl;
    }
    

}

ldconst::~ldconst()
{

}

ldconst::ldconst()
{

}