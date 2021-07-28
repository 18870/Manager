//
//  manager.cpp
//
//  Created by 18870 on 2021/7/18.
//

#include "manager.hpp"

namespace manager {
    void mod(Value& data, string& type, string& name) {
        if (type == "string") {
            cout << l(name) << ": ";
            char c[80] = "";
            cin.getline(c, 81);
            if (string(c) != "") {
                data[name] = c;
            }
        } else if (type == "int") {
            cout << l(name) << ": ";
            int _i;
            cin >> _i;
            cin.get();
            data[name] = _i;
        } else if (type == "double") {
            cout << l(name) << ": ";
            double d;
            cin >> d;
            cin.get();
            data[name] = d;
        } else if (type == "bool") {
            cout << l(name) << " [0] " << l("false") << " [1] " << l("true") << ": ";
            bool b;
            cin >> b;
            cin.get();
            data[name] = b;
        }
    }
    void disp(Value& data, Value& keys, int page, bool showIndex) {
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
    void disp_(Value& data, Value& keys, int i, bool showIndex) {
        if (showIndex) {
            cout << "[" << i + 1 << "] ";
        }
        for (int j = 0; j < keys.size(); ++j) {
            string keyname = keys[j].asString();
            // Whatever, asString is not bad.
            if (!data[i][keyname].isNull()) {
                cout << l(keyname) << ": " << data[i][keyname].asString() << " ";
            }
        }
        cout << endl;
    }
    void page_navigate(Value& data, int page) {
        if ((data.size() - 1) / CONFIG["Display per page"].asInt() + 1 == 1) return;
        if (data.size() == 0) return;

        if (page == 1) {
            cout << "[-1] " << l("nextpage") << endl;
        } else if (page == (data.size() - 1) / CONFIG["Display per page"].asInt() + 1) {
            cout << "[-2] " << l("prevpage") << endl;
        } else {
            cout << "[-1] " << l("nextpage") << " [-2] " << l("prevpage") << endl;
        }
    }
    string get_keytype(Value& data, string& keyname) {
        for (int i = 0; i < data.size(); ++i) {
            if (data[i]["key"].asString() == keyname) {
                return data[i]["type"].asString();
            }
        }
        logger::error("Key " + keyname + " not found.");
        return string();
    }
    void setting_panel() {
        logger::hr(l("setting"));
        int select = -1;
        while (select) {
            cout << l("setting.msg");
            cout << "[0] " << l("quit") << endl;
            cout << ">>> ";
            cin >> select;
            cout << endl;
            cin.get();
            switch (select) {
                case 1: {
                        int val;
                        cout << l("setting.lang") << ">>> ";
                        cin >> val;
                        string lang[] = { "zh_cn", "en" };
                        CONFIG["language"] = lang[val - 1];
                        system("cls");
                        break;
                    }
                case 2: {
                        cout << l("manager.modify.newvalue") << ": ";
                        int i;
                        cin >> i;
                        cin.get();
                        CONFIG["Display per page"] = i;
                        break;
                    }
            }
            config::save_config();
        }
    }

    Manager::Manager(const string& name) {
        cfg = SYSTEM[name];
        manager_name = name;
        read();
    }
    Manager::~Manager() {}

    void Manager::add() {
        Value new_data;
        string dataname;
        string datatype;
        string dispname;
        logger::hr(l("manager.add"));
        read();
        for (int i = 0; i < cfg["Datas"].size(); ++i) {
            dataname = cfg["Datas"][i]["key"].asString();
            datatype = cfg["Datas"][i]["type"].asString();
            mod(new_data, datatype, dataname);
        }

        data.append(new_data);
        save();
    }
    void Manager::del() {
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
                case -1:
                    page += 1;
                    break;
                case -2:
                    page -= 1;
                    break;
                case 0:
                    break;
                default:
                    if (action < -2 || action > data.size()) break;
                    page = action / CONFIG["Display per page"].asInt() + 1;
                    data.removeIndex(action - 1, NULL);
                    save();
            }
        }
    }
    void Manager::modify() {
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
                case -1:
                    page += 1;
                    break;
                case -2:
                    page -= 1;
                    break;
                case 0:
                    break;
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
                            case 0:
                                break;
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
    void Manager::search() {
        logger::hr(l("manager.search"));
        read();
        int method = -1;
        while (method) {
            cout << l("manager.search.select_method") << ": " << endl;
            for (int i = 0; i < cfg["Searchable keys"].size(); ++i) {
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
                case 0:
                    break;
                default:
                    if (method < 0 || method > cfg["Searchable keys"].size()) break;
                    string keyname = cfg["Searchable keys"][method - 1].asString();
                    string type = get_keytype(cfg["Datas"], keyname);
                    int counter = 0;
                    // type sucks
                    if (type == "string") {
                        cout << l("manager.search.enter_key") << ": ";
                        string dest;
                        cin >> dest;
                        for (int i = 0; i < data.size(); ++i) {
                            string key = data[i][keyname].asString();
                            if (utils::in(dest, key)) {
                                counter += 1;
                                disp_(data, cfg["Display keys"], i);
                            }
                        }
                    } else if (type == "int") {
                        cout << l("manager.search.enter_key") << ": ";
                        int dest;
                        cin >> dest;
                        cin.get();
                        for (int i = 0; i < data.size(); ++i) {
                            int key = data[i][keyname].asInt();
                            if (key == dest) {
                                counter += 1;
                                disp_(data, cfg["Display keys"], i);
                            }
                        }
                    } else if (type == "double") {
                        cout << l("manager.search.enter_key") << ": ";
                        double dest;
                        cin >> dest;
                        cin.get();
                        for (int i = 0; i < data.size(); ++i) {
                            double key = data[i][keyname].asDouble();
                            if (key == dest) {
                                counter += 1;
                                disp_(data, cfg["Display keys"], i);
                            }
                        }
                    } else if (type == "bool") {
                        bool dest;
                        cout << " [0] " << l("false") << " [1] " << l("true") << ": ";
                        cin >> dest;
                        cin.get();
                        for (int i = 0; i < data.size(); ++i) {
                            bool key = data[i][keyname].asBool();
                            if (key == dest) {
                                counter += 1;
                                disp_(data, cfg["Display keys"], i);
                            }
                        }
                    }

                    if (!counter) {
                        cout << l("manager.search.notfound") << endl;
                        break;
                    } else {
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
                            case 0:
                                break;
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
    void Manager::display() {
        read();
        int page = 1;
        int action = 1;
        while (action) {
            if (page < 1) page = 1;
            if (page > (data.size() - 1) / CONFIG["Display per page"].asInt() + 1) page -= 1;

            disp(data, cfg["Display keys"], page);
            cout << "[0] " << l("quit") << endl;
            page_navigate(data, page);
            cout << ">>> ";
            cin >> action;
            cout << endl;
            switch (action) {
                case -1:
                    page += 1;
                    break;
                case -2:
                    page -= 1;
                    break;
                case 0:
                    break;
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
    void Manager::panel() {
        /// All program have those method :P
        //Value methods = cfg["Method"];
        //string ALL_METHOD[] = { "Add", "Del", "Modify", "Search", "Display" };
        //bool avaliable[] = { true, true, true, true, true };
        //size(ALL_METHOD);
        //for (int i = 0;i < size(ALL_METHOD);++i) {
        //	if (methods.isMember(ALL_METHOD[i])) {
        //		cout << l("manager.panel." + ALL_METHOD[i]) << endl;
        //		avaliable[i] = true;
        //	}
        //	else {
        //		avaliable[i] = false;
        //	}
        //}

        int select = -1;
        while (select) {
            system("cls");
            logger::hr(l(manager_name));
            cout << l("manager.panel");
            cout << "[0] " << l("quit") << endl;
            cout << ">>> ";
            cin >> select;
            cin.get();
            switch (select) {
                case 1:
                    add();
                    break;
                case 2:
                    del();
                    break;
                case 3:
                    modify();
                    break;
                case 4:
                    search();
                    break;
                case 5:
                    display();
                    break;
                case 0:
                    break;
            }
        }
    }

    void Manager::read() {
        file::read("./data/data.json", DATA);
        data = DATA[manager_name];
    }
    void Manager::save() {
        file::read("./data/data.json", DATA);
        DATA[manager_name] = data;
        file::save("./data/data.json", DATA);
    }

    BookManager::~BookManager() {}
    void BookManager::borrow() {
        logger::hr(l("bookmanager.borrow"));
        read();
        int choose = -1;
        while (choose) {
            cout << l("bookmanager.borrow.msg");
            cout << "[0] " << l("quit") << endl;
            cout << ">>> ";
            cin >> choose;
            cin.get();
            cout << endl;
            switch (choose) {
                case 0:
                    break;
                default:
                    if (data[choose - 1]["borrowed"].asBool() == false) {
                        for (int i = 0; i < cfg["Datas"].size(); ++i) {
                            cout << "- ";
                            string dataname = cfg["Datas"][i]["key"].asString();
                            cout << l(dataname) << ": " << data[choose - 1][dataname] << endl;
                        }
                        cout << l("bookmanager.borrow.confirm") << endl;
                        cout << " [0] " << l("false") << " [1] " << l("true") << ": ";
                        bool confirm = false;
                        cin >> confirm;
                        cin.get();
                        cout << endl;
                        if (confirm) {
                            data[choose - 1]["borrowed"] = true;
                            cout << l("bookmanager.borrow.time") << ": ";
                            char c[80] = "";
                            cin.getline(c, 81);
                            data[choose - 1]["borrow_date"] = c;
                            save();
                        } else {
                            break;
                        }
                    } else {
                        disp_(data, cfg["Display keys"], choose - 1);
                        cout << l("bookmanager.borrow.book_borrowed") << endl;
                        break;
                    }
            }
        }
    }
    void BookManager::return_book() {
        logger::hr(l("bookmanager.return"));
        read();
        int choose = -1;
        while (choose) {
            cout << l("bookmanager.return.msg");
            cout << "[0] " << l("quit") << endl;
            cout << ">>> ";
            cin >> choose;
            cin.get();
            cout << endl;
            switch (choose) {
                case 0:
                    break;
                default:
                    if (data[choose - 1]["borrowed"].asBool() == true) {
                        for (int i = 0; i < cfg["Datas"].size(); ++i) {
                            cout << "- ";
                            string dataname = cfg["Datas"][i]["key"].asString();
                            cout << l(dataname) << ": " << data[choose - 1][dataname] << endl;
                        }
                        cout << l("bookmanager.return.confirm") << endl;
                        cout << " [0] " << l("false") << " [1] " << l("true") << ": ";
                        bool confirm = false;
                        cin >> confirm;
                        cin.get();
                        cout << endl;
                        if (confirm) {
                            data[choose - 1]["borrowed"] = false;
                            data[choose - 1].removeMember("borrow_date");
                            save();
                        } else {
                            break;
                        }
                    } else {
                        disp_(data, cfg["Display keys"], choose - 1);
                        cout << l("bookmanager.return.book_unborrowed") << endl;
                        break;
                    }
            }
        }
    }
    void BookManager::panel() {
        int select = -1;
        while (select) {
            system("cls");
            logger::hr(l(manager_name));
            cout << l("bookmanager.panel");
            cout << "[0] " << l("quit") << endl;
            cout << ">>> ";
            cin >> select;
            cin.get();
            switch (select) {
                case 1:
                    add();
                    break;
                case 2:
                    del();
                    break;
                case 3:
                    modify();
                    break;
                case 4:
                    search();
                    break;
                case 5:
                    display();
                    break;
                case 6:
                    borrow();
                    break;
                case 7:
                    return_book();
                    break;
                case 0:
                    break;
            }
        }
    }
}
