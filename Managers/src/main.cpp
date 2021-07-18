#include <iostream>
#include "json/json.h"
#include "manager.hpp"

using namespace std;

int main(){
    //Json::Value root;
    //file::read("./data/data.json", root);
    //cout << root[0]["Chinese"].asInt() << endl;
    //file::save("./data/data.json", root);
    manager::Manager student("Student Info");
    student.display();
}
