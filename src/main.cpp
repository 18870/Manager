//
//  main.cpp
//
//  Created by 18870 on 2021/7/18.
//

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
            manager::setting_panel();
            break;
        default:
            if (select < 0 || select >6) break;
            if (select == 6) {
                manager = new BookManager(m[select - 1]);
            }
            else {
                manager = new Manager(m[select - 1]);
            }
            manager->panel();
            delete manager;
        }
    }
}