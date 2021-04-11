#pragma once

// Personal includes
#include "IR.h"
#include "basic_block.h"

// System includes
#include <iostream>

// Class used to load a constant into a temporary var
class Cmp_eq : public IRInstr
{
    // Public methods and attributes
public:
    Cmp_eq();
    Cmp_eq(const int &_offsetLeft, const int &_offsetRight, const string &_destinationLabel, const string &_comparativeSign, BasicBlock *bb);
    void gen_asm(ostream &o = cout);
    ~Cmp_eq();
    int offsetLeft;          // The offset of the left var
    int offsetRight;         // The offset of the right var
    string destinationLabel; // the label of the part of code inside the if statement
    string comparativeSign;

    // Protected methods and attributes
protected:
};