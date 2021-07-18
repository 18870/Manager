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


using namespace std;
using Json::Value;


namespace lang {
	extern Value LANG;
	void read();
	string l(string& key);
	string l(const char* key);
}

namespace logger {
	void hr(const char* c);
	void hr(const string& str);
	void warning(const char* c);
	void warning(const string& str);
	void error(const char* c);
	void error(const string& str);
	void info(const char* c);
	void info(const string& str);
}

#endif /* lang_hpp */