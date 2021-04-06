#pragma once

#include "IR.h"
#include "basic_block.h"
#include <iostream>

class ldconst : public IRInstr{ // Used to load a constant into a temporary var
    public:
        ldconst();
        ldconst(const int & _constValue, const int & _offset, const string & variableName, BasicBlock* bb);
        void gen_asm(ostream & o = cout);
        ~ldconst();
        BasicBlock* bb;
        string variableName;
        int constValue;
        int offset; // The offset of the temporary var in the register

    protected:
        

};
