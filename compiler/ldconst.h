#pragma once

// Personal includes
#include "IR.h"
#include "basic_block.h"

// System includes
#include <iostream>

// Class for loading a constant in a temporary variable as an instruction
class ldconst : public IRInstr
{
    // Public methods and attributes
public:
    ldconst();
    ldconst(const int &_constValue, const int &_offset, const string &variableName, BasicBlock *bb);
    void gen_asm(ostream &o = cout);
    ~ldconst();
    string variableName;
    int constValue;
    int offset; // The offset of the temporary var in the register

    // Protected methods and attributes
protected:
};
