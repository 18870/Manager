//
//  config.hpp
//  main
//
//  Created by 18870 on 2021/7/19.
//

#ifndef config_hpp
#define config_hpp

#include "json/json.h"
#include "file.hpp"
using Json::Value;

namespace config {
    extern Value DATA;
    extern Value CONFIG;
    extern Value SYSTEM;
    extern Value LANG;

    void load_config();
    void save_config();
}


#endif /* config_hpp */
