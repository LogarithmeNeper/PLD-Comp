#pragma once

// Personal includes
#include "IR.h"
#include "basic_block.h"
// System include
#include <iostream>

// Class used to write to a label as an instruction
class Write_label : public IRInstr
{
    // Public methods and attributes
public:
    Write_label();
    Write_label(const string &_destinationLabel, BasicBlock *bb);
    void gen_asm(ostream &o = cout);
    ~Write_label();
    string destinationLabel; // the label of the part of code inside the if statement

    // Protected methods and attributes
protected:
};