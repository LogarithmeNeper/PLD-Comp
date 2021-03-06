#pragma once

// Personal include
#include "IR.h"
// System include
#include <iostream>

// Class used to implement a multiplication instruction
class Mul : public IRInstr
{
    // Public methods and attributes
public:
    Mul();
    Mul(const int &_offsetLeft, const int &_offsetRight, const int &_offsetDest, BasicBlock *bb);
    void gen_asm(ostream &o = cout);
    ~Mul();
    int offsetLeft;  // the offset of the left var
    int offsetRight; // the offset of the right var
    int offsetDest;  // the offset of the destination var

    // Protected methods and attributes
protected:
};