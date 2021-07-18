#include <iostream>
#include "json/json.h"
#include "file.hpp"

using namespace std;

int main(){
    Json::Value root;
    file::read("./data/data.json", root);
    cout << root[0]["score"]["Chinese"].asInt() << endl;
    file::save("./data/data.json", root);
}
