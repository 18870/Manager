//
//  manager.hpp
//
//  Created by 18870 on 2021/7/18.
//

#ifndef manager_hpp
#define manager_hpp

#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include "json/json.h"
#include "file.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "lang.hpp"

using namespace std;
using std::string;
using Json::Value;
using lang::l;
using config::CONFIG;
using config::DATA;
using config::SYSTEM;

namespace manager {
    void mod(Value&, string& type, string& name);
    void disp(Value& data, Value& keys, int page = 1, bool showIndex = true);
    void disp_(Value& data, Value& keys, int index, bool showIndex = true);
    void page_navigate(Value& data, int page);
    string get_keytype(Value& data, string& keyname);
    void setting_panel();

    class Manager {
        protected:
            void read();
            void save();
            string manager_name;
            Value cfg;
            Value data;
        public:
            Manager(const string&);
            virtual ~Manager();
            virtual void add();
            virtual void del();
            virtual void modify();
            virtual void search();
            virtual void display();
            virtual void panel();
    };

    class BookManager : public Manager {
        public:
            BookManager(const string& name) :Manager(name) {};
            virtual ~BookManager();
            virtual void borrow();
            virtual void return_book();
            virtual void panel();
    };
}

#endif /* manager_hpp */
