//
//  file.cpp
//  main
//
//  Created by 18870 on 2021/7/18.
//

#include "file.hpp"
namespace file{

int read(const std::string & filename, Json::Value & json){
    Json::Reader reader;
    std::ifstream file;
    file.open(filename);
    assert(file.is_open());
    
    if (!reader.parse(file, json)){
        std::cout << "[Error] Reader parse failed.";
        file.close();
        return -1;
    }
    file.close();
    return 1;
}

int save(const std::string & filename, Json::Value & json){
//    Json::FastWriter writer;
    Json::StreamWriterBuilder wbuilder;
//    wbuilder["indentation"] = "\t";
    std::ofstream file;
    file.open(filename);
    assert(file.is_open());
    
//    std::string json_string = writer.write(json);
    std::string json_string = Json::writeString(wbuilder, json);
    
    file << json_string;
    
    file.close();
    return 1;
}

}

