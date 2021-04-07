// Code adapté de celui fourni ici : https://moodle.insa-lyon.fr/pluginfile.php/98639/mod_resource/content/3/IR.h
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include <map>
#include <list>

//#include "basic_block.h"
//#include "program.h"
class BasicBlock;
class Program;

using namespace std;

/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
	 The entry block is the one with the same label as the AST function name.
	   (it could be the first of bbs, or it could be defined by an attribute value)
	 The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG {
 public:
	CFG(Program* program);
	~CFG();
	Program* program; /**< The AST this CFG comes from */
	
	void add_bb(BasicBlock* bb); 

	// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	void gen_asm(ostream& o);
	// string IR_reg_to_asm(string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
	void gen_asm_prologue(ostream& o);
	void gen_asm_epilogue(ostream& o, int offsetReturn);

	// symbol table methods
	void add_to_symbol_table(string & name, int & index);
	//string create_new_tempvar(/*Type t*/);
	int get_var_index(string & name);
	string get_var_type(string & name);
	map<string,string>* getTypeTable();

	// basic block management

	BasicBlock* get_bb_by_index(int index);
	// string new_BB_name();
	BasicBlock* current_bb;

    map<string,int>* getSymbolTable();

 protected:
	//map <string, Type> SymbolType; /**< part of the symbol table  */
	map <string, int>* symbolTable; /**< part of the symbol table  */
	map <string, string>* typeTable;
	int nextFreeSymbolIndex; /**< to allocate new symbols in the symbol table */
	int nextBBnumber; /**< just for naming */
	
	vector <BasicBlock*> bbs; /**< all the basic blocks of this CFG*/
};