#include "program.h"

using namespace std;

// Constructor of the class
Program::Program()
{
    this->cfgs = vector<CFG *>();
}

// Destructor of the class
Program::~Program()
{
    for (int i = 0; i < cfgs.size(); i++)
    {
        delete cfgs[i]; // Delete each cfg in the vector
    }
}

// Method to add a CFG to the vector of CFG
void Program::add_cfg(CFG *cfg)
{
    this->cfgs.push_back(cfg);
}

// Assembly generator
void Program::gen_asm(ostream &o, int offsetReturn)
{
    // For each CFG in the vector...
    for (int i = 0; i < this->cfgs.size(); i++)
    {
        this->cfgs[i]->gen_asm_prologue(o);               // ... generating the prologue ...
        this->cfgs[i]->gen_asm(o);                        // ... then the body ...
        this->cfgs[i]->gen_asm_epilogue(o, offsetReturn); // ..then the epilogue
    }
}

// Getter of the CFG by its index
CFG *Program::get_cfg_by_index(int index)
{
    return this->cfgs.at(index);
}