//
//  manager.hpp
//
//  Created by 18870 on 2021/7/18.
//

#ifndef manager_hpp
#define manager_hpp

#include <iostream>
#include <string>
#include "json/json.h"
#include "file.hpp"


using std::cin;
using std::cout;
using std::endl;
using std::string;
using Json::Value;


namespace manager {
extern Value SYSTEM_CONFIG;
extern Value DATA;
extern Value CONFIG;

void mod(Value &, string & type, string & name);
void disp(Value & data, Value & keys, int page = 1, bool showIndex=true);
void disp_(Value & data, Value & keys, int index, bool showIndex=true);
void page_navigate(Value & data, int page);
string get_keytype(Value & data, string & keyname);
void load_config(bool load=false);

class Manager {
	void read();
	void save();
	string manager_name;
	Value cfg;
	Value data;
public:
	Manager(const string);
	virtual void add();
	virtual void del();
	virtual void modify();
	virtual void search();
	virtual void display();
	virtual void panel();

};

}

#endif /* manager_hpp */
