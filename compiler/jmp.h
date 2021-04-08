#pragma once

#include "IR.h"
#include "basic_block.h"
#include <iostream>

class Jmp : public IRInstr{ // Used to load a constant into a temporary var
    public:
        Jmp();
        Jmp(const string & _destinationLabel, BasicBlock* bb);
        void gen_asm(ostream & o = cout);
        ~Jmp();
        string destinationLabel; // the label of the part of code inside the if statement

    protected:
        

};