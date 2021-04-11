#pragma once

// Personal include
#include "IR.h"
// System include
#include <iostream>
#include <string>

// Class used to make a function call
 
class Call : public IRInstr{ 
   // Public methods and attributes
    public:
        Call();
        Call(const int & _argumentOffset, std::string _functionName, const int & _offset,BasicBlock* bb);
        void gen_asm(ostream & o = cout);
        ~Call();
        int argumentOffset; // The offset of the variable passed to the function as an argument
        std::string functionName; // The name of the function to call
        int offset;

    // Protected methods and attributes
protected:
};
