// Code adapté de celui fourni ici : https://moodle.insa-lyon.fr/pluginfile.php/98639/mod_resource/content/3/IR.h
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include <map>
#include <list>

#include "cfg.h"

using namespace std;

class Program{
	public:
		Program();
		void gen_asm(ostream& o, int offsetReturn);
		void add_cfg(CFG* cfg);
		
		vector<CFG*> cfgs;

		CFG* get_cfg_by_index(int index);

	protected:
		
};