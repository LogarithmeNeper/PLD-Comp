#pragma once

#include "IR.h"
#include <iostream>
#include <string>

class Call : public IRInstr{ // Used to make a function call
    public:
        Call();
        Call(const int & _argumentOffset, std::string _functionName, const int & _offset,BasicBlock* bb);
        void gen_asm(ostream & o = cout);
        ~Call();
        int argumentOffset; // The offset of the variable passed to the function as an argument
        std::string functionName; // The name of the function to call
        int offset;

    protected:
        

};
