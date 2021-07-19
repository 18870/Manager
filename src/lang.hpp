//
//  lang.hpp
//  main
//
//  Created by 18870 on 2021/7/18.
//

#ifndef lang_hpp
#define lang_hpp

#include <iostream>
#include "json/json.h"
#include "utils.hpp"
#include "file.hpp"
#include "config.hpp"

using namespace std;
using Json::Value;
using config::LANG;
using config::CONFIG;


namespace lang {
	void read();
	string l(string& key);
	string l(const char* key);
}

#endif /* lang_hpp */