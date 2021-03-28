#pragma once

#include "IR.h"
#include <iostream>

class Sub : public IRInstr{ // Used to make an addition
    public:
        Sub();
        Sub(const int & _offsetLeft, const int & _offsetRight, const int & _offsetDest);
        void gen_asm(ostream & o = cout);
        ~Sub();
        int offsetLeft; // the offset of the left var
        int offsetRight; // the offset of the right var
        int offsetDest; // the offset of the destination var

    protected:
        

};
