#pragma once

#include "IR.h"
#include <iostream>

class Copy : public IRInstr{ // Used to load a constant into a temporary var
    public:
        Copy();
        Copy(const int & _offsetSource, const int & _offsetDest);
        void gen_asm(ostream & o = cout);
        ~Copy();
        int offsetSource; // The offset of the source var
        int offsetDest; // The offset of the destination var

    protected:
        

};
