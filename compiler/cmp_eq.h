#pragma once

#include "IR.h"
#include "basic_block.h"
#include <iostream>

class Cmp_eq : public IRInstr{ // Used to load a constant into a temporary var
    public:
        Cmp_eq();
        Cmp_eq(const int & _offsetLeft, const int & _offsetRight, const string & destinationLabel, BasicBlock* bb);
        void gen_asm(ostream & o = cout);
        ~Cmp_eq();
        int offsetLeft; // The offset of the left var
        int offsetRight; // The offset of the right var
        string destinationLabel; // the label of the part of code inside the if statement

    protected:
        

};