#pragma once

// Personal includes
#include "IR.h"
#include "basic_block.h"

// System includes
#include <iostream>

// Class implementing a jump instruction
class Jmp : public IRInstr
{
// Public methods and attributes
public:
    Jmp();
    Jmp(const string &_destinationLabel, BasicBlock *bb);
    void gen_asm(ostream &o = cout);
    ~Jmp();
    string destinationLabel; // the label of the part of code inside the if statement
// Protected methods and attributes
protected:
};