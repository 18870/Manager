//
//  lang.cpp
//  main
//
//  Created by 18870 on 2021/7/18.
//

#include "lang.hpp"
#include "manager.hpp"
#include "file.hpp"

namespace lang {
	using manager::CONFIG;
	Value LANG;

	void read(){
		file::read("./data/lang.json", LANG);
	}
	void save() {
		file::save("./data/lang.json", LANG);
	}

	string l(string& key) {
		if (LANG[CONFIG["language"].asString()][key].isNull()) {
			logger::warn("Key " + key + " not found.");
			// Saving a Chinese character cause coding problem
			// GBK sucks, PLEASE USE UTF-8

			//LANG[CONFIG["language"].asString()][key] = "";
			//save();
			return key;
		}
		// Disabled.
		//if (LANG[CONFIG["language"].asString()][key].asString() == "") {
		//	logger::warning("Key " + key + " is empty.");
		//	return key;
		//}
		return LANG[CONFIG["language"].asString()][key].asString();
	}
	string l(const char* key) {
		string k = key;
		return l(k);
	}
}

namespace logger {
	void hr(const char* c){
		cout << "<<<<<<<< " << c << " >>>>>>>>" << endl;
	}
	void hr(const string& str){
		cout << "<<<<<<<< " << str << " >>>>>>>>" << endl;
	}
	void warn(const char* c) {
		cout << "[Warning] " << c << endl;
	}
	void warn(const string& str) {
		cout << "[Warning] " << str << endl;
	}
	void error(const char* c) {
		cout << "[Error] " << c << endl;
	}
	void error(const string& str) {
		cout << "[Error] " << str << endl;
	}
	void info(const char* c) {
		cout << "[Info] " << c << endl;
	}
	void info(const string& str) {
		cout << "[Info] " << str << endl;
	}
}