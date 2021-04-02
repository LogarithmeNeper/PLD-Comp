#pragma once

#include "IR.h"
#include <iostream>

class Add : public IRInstr{ // Used to make an addition
    public:
        Add();
        Add(const int & _offsetLeft, const int & _offsetRight, const int & _offsetDest, BasicBlock* bb);
        void gen_asm(ostream & o = cout);
        ~Add();
        int offsetLeft; // the offset of the left var
        int offsetRight; // the offset of the right var
        int offsetDest; // the offset of the destination var

    protected:
        

};