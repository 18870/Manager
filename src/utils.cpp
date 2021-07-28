//
//  utils.cpp
//  main
//
//  Created by 18870 on 2021/7/19.
//

#include "utils.hpp"

namespace utils {
    bool in(const string& origin, const string& dest) {
        if (dest.find(origin) != dest.npos) return true;
        return false;
    }
    bool in(const char* origin, const string& dest) {
        if (dest.find(origin) != dest.npos) return true;
        return false;
    }
    bool in(const string& origin, const char* dest) {
        if (string(dest).find(origin) != string().npos) return true;
        return false;
    }
    bool in(const char* origin, const char* dest) {
        if (string(dest).find(origin) != string().npos) return true;
        return false;
    }
}

namespace logger {
    void hr(const char* c) {
        cout << "<<<<<<<< " << c << " >>>>>>>>" << endl;
    }
    void hr(const string& str) {
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
