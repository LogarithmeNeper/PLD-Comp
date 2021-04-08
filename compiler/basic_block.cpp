#include "basic_block.h"

using namespace std;

BasicBlock::BasicBlock(CFG* cfg) 
{
    this->cfg = cfg;
}

void BasicBlock::gen_asm(ostream & o)
{
    for(int i = 0; i < this->instrs.size(); i++)
    {
        this->instrs[i]->gen_asm(o);
    }

}

void BasicBlock::add_IRInstr(IRInstr* instr)
{

    this->instrs.push_back(instr);


}

BasicBlock::~BasicBlock()
{
}