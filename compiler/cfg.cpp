#include "cfg.h"
#include "basic_block.h"

using namespace std;

CFG::CFG(Program* program, string name, int nbArguments) 
{
    this->program = program;
    this->symbolTable = new map<string,int>();
    this->maxOffset = 0;
    this->name = name;
    this->nbArguments = nbArguments;

}

CFG::~CFG() {
    delete symbolTable;
    for(int i=0; i < bbs.size(); i++){
        delete bbs[i];
    }
}

void CFG::add_bb(BasicBlock* bb)
{
    this->bbs.push_back(bb);
    this->current_bb = bb;
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
        << ".globl "<< this->name << "\n"
        << " " << this->name <<": " << "\n"
        << "\tpushq %rbp\n"
        << "\tmovq %rsp, %rbp\n";

    switch(this->nbArguments)
    {
        case 0:
        break;

        case 1:
        this->maxOffset += 4;
        o << "\tmovl	%edi, -" << this->maxOffset << "(%rbp) \n";
        break;

        case 2:
        this->maxOffset += 4;
        o << "\tmovl %edi -" << this->maxOffset << "(%rbp) \n";
        this->maxOffset += 4;
        o << "\tmovel %esi -" << this->maxOffset << "(%rbp) \n";
        break;

        default:
        cerr << "Error, functions containing more than 2 parameters are fobidden ! Wrong fonction : " << this->name << "\n";
        break;

    }

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
    this->symbolTable->insert({name, index});
}

int CFG::get_var_index(string & name)
{
    return (*(this->symbolTable))[name];
}

BasicBlock* CFG::get_bb_by_index(int index)
{
    return this->bbs.at(index);

}

map<string,int>* CFG::getSymbolTable()
{
    return this->symbolTable;
}
