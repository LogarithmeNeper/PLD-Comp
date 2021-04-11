#include "basic_block.h"

using namespace std;

// Constructor
BasicBlock::BasicBlock(CFG *cfg, string entry_label)
{
    this->cfg = cfg;
    this->label = entry_label;
}

// Assembly generator for each instruction (see related methods)
void BasicBlock::gen_asm(ostream &o)
{
    for (int i = 0; i < this->instrs.size(); i++)
    {
        this->instrs[i]->gen_asm(o);
    }
}

// Adding an instruction to the list of instructions
void BasicBlock::add_IRInstr(IRInstr *instr)
{
    this->instrs.push_back(instr);
}

// Destructor
BasicBlock::~BasicBlock()
{
}