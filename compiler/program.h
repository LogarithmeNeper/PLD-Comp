// Code adapté de celui fourni ici : https://moodle.insa-lyon.fr/pluginfile.php/98639/mod_resource/content/3/IR.h
#pragma once

// System includes
#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include <map>
#include <list>

// Personal include
#include "cfg.h"

// Namespace
using namespace std;

// Class used to represent a program
class Program
{
	// Public methods and attributes
public:
	Program();
	~Program();
	void gen_asm(ostream &o, int offsetReturn);
	void add_cfg(CFG *cfg);
	vector<CFG *> cfgs;				  // list of CFG
	CFG *get_cfg_by_index(int index); // Getter

	// Protected methods and attributes
protected:
};