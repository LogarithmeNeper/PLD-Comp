#include "copy.h"

// Constructor of the class
Copy::Copy(const int &_offsetSource, const int &_offsetDest, const string &destName, BasicBlock *bb) : IRInstr("copy", bb)
{
      this->offsetSource = _offsetSource;
      this->offsetDest = _offsetDest;
      this->destName = destName;
}

// The asm generation can be optimized for a char : we use movl to allow char to be initialized with int value
// We would need the type of the Source to be able to use movb.
void Copy::gen_asm(ostream &o) // x86 asm for now
{
      string destType = this->bb->cfg->get_var_type(this->destName);
      // Different assembly for different types
      if (destType == "int")
      {
            o << "\tmovl -" // movl for int
              << this->offsetSource
              << "(%rbp), %eax"
              << std::endl;
            o << "\tmovl %eax, -"
              << this->offsetDest
              << "(%rbp)"
              << std::endl;
      }
      else if (destType == "char")
      {
            o << "\tmovl -"
              << this->offsetSource
              << "(%rbp), %eax"
              << std::endl;
            o << "\tmovb %al, -" // movb for char
              << this->offsetDest
              << "(%rbp)"
              << std::endl;
      }
      else if (destType == "int64")
      {
            o << "\tmovq -" // movq for int64
              << this->offsetSource
              << "(%rbp), %rax"
              << std::endl;
            o << "\tmovq %rax, -"
              << this->offsetDest
              << "(%rbp)"
              << std::endl;
      }
}

// Destructor of the class
Copy::~Copy()
{
}

// No-params constructor
Copy::Copy()
{
}