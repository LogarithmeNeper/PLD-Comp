// Code adapté de celui fourni ici : https://moodle.insa-lyon.fr/pluginfile.php/98639/mod_resource/content/3/IR.h
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include <map>
#include <list>

// #include "basic_block.h"
#include "cfg.h"
class BasicBlock;

using namespace std;

// Declarations from the parser -- replace with your own
//#include "type.h"
//#include "symbole.h"


//! The class for one 3-address instruction
class IRInstr {
 
   public:
	/** The instructions themselves -- feel free to subclass instead */
	typedef enum {
		ldconst, // load a constant into a var
		copy, // copy the value of a var in an other var
		add, // addition
		sub, // subtraction
		mul, // multiplication
		rmem, // read the value of a memory space (used only for tabs)
		wmem, // write a value in a memory space (used only for tabs)
		call, // call to a function
		cmp_eq, // ==
		cmp_lt, // <
		cmp_le, // <=
		write_label // instruction to write a label for if instr
	} Operation;
	BasicBlock* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */

	IRInstr(std::string description="", BasicBlock* bb = nullptr):description(description), bb(bb){}
	string getDescription(){return this->description;}
	~IRInstr(){}
	
	/** Actual code generation */
	virtual void gen_asm(ostream & o = cout)=0; /**< x86 assembly code generation for this IR instruction */
	
 private:
	
	Operation op;
	//Type t;
	vector<string> params; /**< For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
	// if you subclass IRInstr, each IRInstr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design. 
	std::string description;
};
