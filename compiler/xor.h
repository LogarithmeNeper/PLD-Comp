#pragma once

#include "IR.h"
#include <iostream>

class Xor : public IRInstr{ // Used to make an addition
    public:
        Xor();
        Xor(const int & _offsetLeft, const int & _offsetRight, const int & _offsetDest, BasicBlock* bb);
        void gen_asm(ostream & o = cout);
        ~Xor();
        int offsetLeft; // the offset of the left var
        int offsetRight; // the offset of the right var
        int offsetDest; // the offset of the destination var

    protected:
        

};