#include "program.h"

using namespace std;

Program::Program()
{
	this->cfgs = vector<CFG*>();
}

Program::~Program() {
for(int i=0; i < cfgs.size(); i++){
   delete cfgs[i];
    }
}
void Program::add_cfg(CFG* cfg)
{
    this->cfgs.push_back(cfg);
}

void Program::gen_asm(ostream & o, int offsetReturn)
{
    for(int i = 0; i < this->cfgs.size(); i++)
    {
        this->cfgs[i]->gen_asm_prologue(o);
        this->cfgs[i]->gen_asm(o);
        this->cfgs[i]->gen_asm_epilogue(o, offsetReturn);
    }

}

CFG* Program::get_cfg_by_index(int index)
{
    return this->cfgs.at(index);
}