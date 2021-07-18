//
//  manager.cpp
//
//  Created by 18870 on 2021/7/18.
//

#include "manager.hpp"
#include "lang.hpp"

using lang::l;

namespace manager {

Value SYSTEM;
Value DATA;
Value CONFIG;

Manager::Manager(const string name) {
	load_config();
	cfg = SYSTEM[name];
	manager_name = name;
	read();
}

void Manager::add(){
	Value new_data;
	string dataname;
	string datatype;
	string dispname;
	logger::hr(l("manager.add"));
	read();
	for (int i = 0; i < cfg["Datas"].size(); ++i) {
		dataname = cfg["Datas"][i]["key"].asString();
		datatype = cfg["Datas"][i]["type"].asString();
		cout << l(dataname) << ": ";
		mod(new_data, datatype, dataname);
	}

	data.append(new_data);
	save();
}

void Manager::del(){
	logger::hr(l("manager.del"));
	read();
	int page = 1;
	int action = -1;
	while (action) {
		disp(data, cfg["Display keys"], page);
		cout << "[0] " << l("quit") << endl;
		page_navigate(data, page);
		cout << ">>> ";
		cin >> action;
		cin.get();
		cout << endl;
		switch (action) {
		case -1: page += 1; break;
		case -2: page -= 1; break;
		case 0: break;
		default:
			if (action < -2 || action > data.size()) break;
			page = action / CONFIG["Display per page"].asInt() + 1;
			data.removeIndex(action - 1, NULL);
			save();
		}
	}
}

void Manager::modify(){
	logger::hr(l("manager.modify"));
	read();
	int page = 1;
	int action = -1;
	while (action) {
		disp(data, cfg["Display keys"], page);
		cout << "[0] " << l("quit") << endl;
		page_navigate(data, page);
		cout << ">>> ";
		cin >> action;
		cin.get();
		cout << endl;
		switch (action) {
		case -1: page += 1; break;
		case -2: page -= 1; break;
		case 0: break;
		default:
			if (action < -2 || action > data.size()) break;
			page = action / CONFIG["Display per page"].asInt() + 1;
			int action2 = -1;
			string dataname, datatype;
			while (action2) {
				cout << l("manager.modify.hint") << endl;
				for (int i = 0; i < cfg["Datas"].size(); ++i) {
					cout << "[" << i + 1 << "] ";
					dataname = cfg["Datas"][i]["key"].asString();
					cout << l(dataname) << ": " << data[action - 1][dataname] << endl;
				}
				cout << "[0] " << l("quit") << endl;
				cout << ">>> ";
				cin >> action2;
				cin.get();
				cout << endl;
				switch (action2) {
				case 0: break;
				default:
					if (action2 < 0 || action2 > data[action - 1].size()) break;
					cout << l("manager.modify.newvalue") << ": ";
					Value mod_data = data[action - 1];
					datatype = cfg["Datas"][action2 - 1]["type"].asString();
					dataname = cfg["Datas"][action2 - 1]["key"].asString();
					mod(mod_data, datatype, dataname);
					data[action - 1] = mod_data;
				}
			}
			save();
		}
	}
}

void Manager::search(){
	logger::hr(l("manager.search"));
	read();
	int method = -1;
	while (method) {
		cout << l("manager.search.select_method") << ": " << endl;
		for (int i = 0;i < cfg["Searchable keys"].size();++i) {
			string method_;
			cout << "[" << i + 1 << "] ";
			method_ = cfg["Searchable keys"][i].asString();
			cout << l(method_) << endl;
		}
		cout << "[0] " << l("quit") << endl;
		cout << ">>> ";
		cin >> method;
		cin.get();
		cout << endl;
		switch (method) {
		case 0: break;
		default:
			if (method < 0 || method > cfg["Searchable keys"].size()) break;
			string keyname = cfg["Searchable keys"][method-1].asString();
			string type = get_keytype(cfg["Datas"], keyname);
			int counter = 0;
			cout << l("manager.search.enter_key") << ": ";
			// type sucks
			if (type == "string") {
				string dest;
				cin >> dest;
				for (int i = 0;i < data.size();++i) {
					string key = data[i][keyname].asString();
					if (key == dest) {
						counter += 1;
						disp_(data, cfg["Display keys"], i);
					}
				}
			}
			else if (type == "int") {
				int dest;
				cin >> dest;
				cin.get();
				for (int i = 0;i < data.size();++i) {
					int key = data[i][keyname].asInt();
					if (key == dest) {
						counter += 1;
						disp_(data, cfg["Display keys"], i);
					}
				}
			}
			else if (type == "double") {
				double dest;
				cin >> dest;
				cin.get();
				for (int i = 0;i < data.size();++i) {
					double key = data[i][keyname].asDouble();
					if (key == dest) {
						counter += 1;
						disp_(data, cfg["Display keys"], i);
					}
				}
			}

			if (!counter) {
				cout << l("manager.search.notfound") << endl;
				break;
			}
			else {
				cout << l("manager.search.total1") << counter << l("manager.search.total2") << endl;
			}
			int choose = -1;
			while (choose) {
				cout << "[n] " << l("manager.search.showdetail") << endl;
				cout << "[0] " << l("quit") << endl;
				cout << ">>> ";
				cin >> choose;
				cin.get();
				cout << endl;
				switch (choose) {
				case 0: break;
				default:
					if (choose < 0 || choose > data.size()) break;
					for (int i = 0; i < cfg["Datas"].size(); ++i) {
						cout << "- ";
						string dataname = cfg["Datas"][i]["key"].asString();
						cout << l(dataname) << ": " << data[choose - 1][dataname] << endl;
					}
				}
			}
		}
	}
}

void Manager::display(){
	read();
	int page = 1;
	int action = 1;
	while (action) {
		disp(data, cfg["Display keys"], page);
		cout << "[0] " << l("quit") << endl;
		page_navigate(data, page);
		cout << ">>> ";
		cin >> action;
		cout << endl;
		switch (action){
		case -1: page += 1; break;
		case -2: page -= 1; break;
		case 0: break;
		default:
			if (action < -2 || action > data.size()) break;
			page = action / CONFIG["Display per page"].asInt() + 1;
			for (int i = 0; i < cfg["Datas"].size(); ++i) {
				cout << "- ";
				string dataname = cfg["Datas"][i]["key"].asString();
				cout << l(dataname) << ": " << data[action - 1][dataname] << endl;
			}
		}
	}
	
}

void Manager::panel(){

}



void Manager::read() {
	file::read("./data/data.json", DATA);
	data = DATA[manager_name];
}

void Manager::save(){
	file::read("./data/data.json", DATA);
	DATA[manager_name] = data;
	file::save("./data/data.json", DATA);
}



void mod(Value & data, string & type, string & name){
	if (type == "string") {
		string str;
		cin >> str;
		data[name] = str;
	}
	else if (type == "int") {
		int _i;
		cin >> _i;
		cin.get();
		data[name] = _i;
	}
	else if (type == "double") {
		double d;
		cin >> d;
		cin.get();
		data[name] = d;
	}
}

void disp(Value & data, Value & keys, int page, bool showIndex){
	int size = data.size();
	int npage = CONFIG["Display per page"].asInt();
	int m_page = (size - 1) / npage + 1;
	int start = (page - 1) * npage;
	int end = page * npage;
	if (page >= m_page) {
		page = m_page;
		start = (page - 1) * npage;
		end = size;
	}

	cout << "======== Page [" << page << " / " << m_page << "] ========" << endl;
	for (int i = start; i < end; ++i) {
		disp_(data, keys, i, showIndex);
	}
	
	
}

void disp_(Value& data, Value& keys, int i, bool showIndex){
	if (showIndex) {
		cout << "[" << i + 1 << "] ";
	}
	for (int j = 0;j < keys.size();++j) {
		string keyname = keys[j].asString();
		// Whatever, asString is not bad.
		cout << l(keyname) << ": " << data[i][keyname].asString() << " ";
	}
	cout << endl;
}

void page_navigate(Value & data, int page) {
	if (page == 1) {
		cout << "[-1] " << l("nextpage") << endl;
	}
	else if (page == (data.size() - 1) / CONFIG["Display per page"].asInt() + 1) {
		cout << "[-2] " << l("prevpage") << endl;
	}
	else {
		cout << "[-1] " << l("nextpage") << " [-2] " << l("prevpage") << endl;
	}
}

string get_keytype(Value& data, string& keyname) {
	for (int i = 0;i < data.size();++i) {
		if (data[i]["key"].asString() == keyname) {
			return data[i]["type"].asString();
		}
	}
	logger::error("Key " + keyname + " not found.");
	return string();
}

// TODO: move to data.cpp to initialize
void load_config(bool load){
	static bool CONFIG_LOADED = false;
	if (!CONFIG_LOADED || load) {
		file::read("./data/system.json", SYSTEM);
		file::read("./data/config.json", CONFIG);
		file::read("./data/lang.json", lang::LANG);
		CONFIG_LOADED = true;
	}
}

}