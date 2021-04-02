#include "IR.h"

using namespace std;

CFG::CFG(Program* program) 
{
    this->program = program;

}

void CFG::add_bb(BasicBlock* bb)
{
    this->bbs.push_back(bb);
}

void CFG::gen_asm(ostream & o)
{
    for(int i = 0; i < this->bbs.size(); i++){
        bbs[i]->gen_asm(o);
    }
}

void CFG::gen_asm_prologue(ostream & o)
{
    o 
        << ".globl main\n"
        << " main: \n"
        << "\tpushq %rbp\n"
        << "\tmovq %rsp, %rbp\n";

}

void CFG::gen_asm_epilogue(ostream & o, int offsetReturn)
{
    o 
            << "\tmovl	-"
            << offsetReturn
            << "(%rbp), %eax\n"
            << "\tpopq %rbp\n"
            << "\tret\n";

}

void CFG::add_to_symbol_table(string & name, int & index)
{
    this->symbolTable.insert({name, index});
}

int CFG::get_var_index(string & name)
{
    return this->symbolTable[name];
}

BasicBlock* CFG::get_bb_by_index(int index)
{
    return this->bbs.at(index);

}
