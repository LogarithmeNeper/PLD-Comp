// Add Class

#pragma once

// System includes
#include <iostream>

// Personal includes
#include "IR.h"

// Used to make an addition instruction
// Inherits from Instruction
class Add : public IRInstr
{
    // Public methods and attributes
public:
    Add();
    Add(const int &_offsetLeft, const int &_offsetRight, const int &_offsetDest, BasicBlock *bb);
    void gen_asm(ostream &o = cout);
    ~Add();
    int offsetLeft;  // the offset of the left var
    int offsetRight; // the offset of the right var
    int offsetDest;  // the offset of the destination var

    // Protected methods and attributes
protected:
};
