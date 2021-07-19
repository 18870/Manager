//
//  config.cpp
//  main
//
//  Created by 18870 on 2021/7/19.
//

#include "config.hpp"

namespace config {

	Value DATA;
	Value CONFIG;
	Value SYSTEM;
	Value LANG;

	void load_config(){
		file::read("./data/system.json", SYSTEM);
		file::read("./data/config.json", CONFIG);
		file::read("./data/lang.json", LANG);
		file::read("./data/data.json", DATA);
	}
	void save_config(){
		file::save("./data/config.json", CONFIG);
	}
}