#include <iostream>
#include <string>
#include <stdlib.h>
#include "manager.hpp"
#include "lang.hpp"
#include "config.hpp"

using namespace std;
using manager::Manager;
using manager::BookManager;
using lang::l;

void setting_panel() {
    using config::CONFIG;
    logger::hr(l("setting"));
    int select = -1;
    while (select) {
        cout << l("setting.msg");
        cout << "[0] " << l("quit") << endl;
        cout << ">>> ";
        cin >> select;
        cout << endl;
        cin.get();
        switch (select){
        case 1: {
            int val;
            cout << l("setting.lang") << ">>> ";
            cin >> val;
            string lang[] = { "zh_cn", "en" };
            CONFIG["language"] = lang[val-1];
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

int main(){
    config::load_config();
    string m[] = {
        "Student Info",
        "Address Book",
        "Staff",
        "Device",
        "Flight",
        "Book",
    };
    Manager* manager;

    int select = -1;
    while (select) {
        system("cls");
        cout << l("main.select");
        cout << "[9] " << l("setting") << endl;
        cout << "[0] " << l("quit") << endl;
        cout << ">>> ";
        cin >> select;
        cin.get();
        cout << endl;
        switch (select) {
        case 0: break;
        case 9:
            setting_panel();
            break;
        default:
            if (select < 0 || select >6) break;
            if (select == 6) {
                manager = new BookManager(m[select - 1]);
            }
            else {
                manager = new Manager(m[select - 1]);
            }
            system("cls");
            manager->panel();
            delete manager;
        }
    }
}


