#include "IR.h"

using namespace std;

BasicBlock::BasicBlock(CFG* cfg, string entry_label) 
{
    this->cfg = cfg;
    this->label = entry_label;
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