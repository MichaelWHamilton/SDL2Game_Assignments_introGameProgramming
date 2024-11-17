#pragma once
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include "Engine.h"

class GameObjectLoader {
public:
    GameObjectLoader(const std::string& objectFilePath);
private:
    std::string m_name;
    
};