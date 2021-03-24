#ifndef LDCONST_H
#define LDCONST_H

#include "IR.h"
#include <iostream>

class ldconst : public IRInstr{ // Used to load a constant into a temporary var
    public:
        ldconst();
        ldconst(const int & _constValue, const int & _offset);
        void gen_asm(ostream & o);
        ~ldconst();

    protected:
        int constValue;
        int offset; // The offset of the temporary var in the register

};


#endif