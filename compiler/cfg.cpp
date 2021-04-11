// Personal includes
#include "cfg.h"
#include "basic_block.h"

// Namespace
using namespace std;

// Constructor given a program
CFG::CFG(Program *program)
{
    this->program = program;
    this->symbolTable = new map<string, int>();
    this->typeTable = new map<string, string>();
}

// Destructor
CFG::~CFG()
{
    delete symbolTable;
    for (int i = 0; i < bbs.size(); i++)
    { // foreach basic bloc, deleting
        delete bbs[i];
    }
}

// Adding a basic block to the list of basic blocks and inidicating the current one
void CFG::add_bb(BasicBlock *bb)
{
    this->bbs.push_back(bb);
    this->current_bb = bb;
}

// Assembly generator
void CFG::gen_asm(ostream &o)
{
    for (int i = 0; i < this->bbs.size(); i++)
    {
        bbs[i]->gen_asm(o); // for each basic block, generate assembly for the list of instrs
    }
}

// Prologue maker
void CFG::gen_asm_prologue(ostream &o)
{
    o
        << ".globl main\n"
        << " main: \n"
        << "\tpushq %rbp\n"
        << "\tmovq %rsp, %rbp\n"; // declaring main process
}

// Epilogue maker
void CFG::gen_asm_epilogue(ostream &o, int offsetReturn)
{
    o
        << "\tmovl	-"
        << offsetReturn
        << "(%rbp), %eax\n"
        << "\tpopq %rbp\n"
        << "\tret\n"; // returning the value
}

// Method to add a variable/index in the symbol table of the CFG
void CFG::add_to_symbol_table(string &name, int &index)
{
    this->symbolTable->insert({name, index});
}

// Getter of the index of a given variable
int CFG::get_var_index(string &name)
{
    return (*(this->symbolTable))[name];
}

// Getter of the type of a given variable
string CFG::get_var_type(string &name)
{
    return (*(this->typeTable))[name];
}

// Getter of a basic block of a given index
BasicBlock *CFG::get_bb_by_index(int index)
{
    return this->bbs.at(index);
}

// Getter of the symbol table
map<string, int> *CFG::getSymbolTable()
{
    return this->symbolTable;
}

// Getter of the type table
map<string, string> *CFG::getTypeTable()
{
    return this->typeTable;
}