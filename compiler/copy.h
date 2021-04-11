#pragma once

// Personal includes
#include "IR.h"
#include "basic_block.h"

// System include
#include <iostream>

// Class used to implement the instruction of copy
class Copy : public IRInstr{
    // Public methods and attributes
    public:
        Copy();
        Copy(const int & _offsetSource, const int & _offsetDest, const string & destName, BasicBlock* bb);
        void gen_asm(ostream & o = cout);
        ~Copy();
        int offsetSource; // The offset of the source var
        int offsetDest; // The offset of the destination var
        string destName; // The name of the destination variable

    // Protected methods and attributes
    protected:
        

};
