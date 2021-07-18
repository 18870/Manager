#include <iostream>
#include "manager.hpp"

using namespace std;
using manager::Manager;

void init() {

}

int main(){
    init();
    Manager student("Student Info");
    //Manager book("Book");
    Manager adbook("Address Book");
    Manager staff("Staff");
    Manager device("Device");
    Manager flight("Flight");
    Manager* manager;


    manager = &student;
    manager->search();
    
}


