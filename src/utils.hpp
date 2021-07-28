//
//  utils.hpp
//  main
//
//  Created by 18870 on 2021/7/19.
//

#ifndef utils_hpp
#define utils_hpp

#include <iostream>
#include <string>

using namespace std;
namespace utils {
    bool in(const string&, const string&);
    bool in(const char*, const string&);
    bool in(const string&, const char*);
    bool in(const char*, const char*);
}
namespace logger {
    void hr(const char* c);
    void hr(const string& str);
    void warn(const char* c);
    void warn(const string& str);
    void error(const char* c);
    void error(const string& str);
    void info(const char* c);
    void info(const string& str);
}
#endif /* utils_hpp */
