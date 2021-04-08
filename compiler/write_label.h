#pragma once

#include "IR.h"
#include "basic_block.h"
#include <iostream>

class Write_label : public IRInstr{ // Used to load a constant into a temporary var
    public:
        Write_label();
        Write_label(const string & _destinationLabel, BasicBlock* bb);
        void gen_asm(ostream & o = cout);
        ~Write_label();
        string destinationLabel; // the label of the part of code inside the if statement

    protected:
        

};