//
//  file.hpp
//  main
//
//  Created by 18870 on 2021/7/18.
//

#ifndef file_hpp
#define file_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include "json/json.h"

namespace file{

int read(const std::string & filename, Json::Value & json);
int save(const std::string & filename, Json::Value & json);

}

#endif /* file_hpp */
