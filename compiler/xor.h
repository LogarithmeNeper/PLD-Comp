#pragma once

// Personal include
#include "IR.h"
// System include
#include <iostream>

// Class used to implement the logical XOR Instruction
class Xor : public IRInstr
{
    // Public methods and attributes
public:
    Xor();
    Xor(const int &_offsetLeft, const int &_offsetRight, const int &_offsetDest, BasicBlock *bb);
    void gen_asm(ostream &o = cout);
    ~Xor();
    int offsetLeft;  // the offset of the left var
    int offsetRight; // the offset of the right var
    int offsetDest;  // the offset of the destination var

    // Protected methods and attributes
protected:
};