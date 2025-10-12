//
// Created by David Richter on 10/12/25.
//

#pragma once

#include <string>
#include <map>

class AppConfig
{
private:
    AppConfig()
        : configData({})
    {
        configData["screenWidth"] = 1280;
        configData["screenHeight"] = 720;
        configData["fps"] = 120;
    }

    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig) = delete;
    AppConfig(AppConfig&&) = delete;
    AppConfig& operator=(AppConfig&&) = delete;

    std::map<std::string, int> configData;

public:
    static AppConfig& getInstance()
    {
        static AppConfig instance;
        return instance;
    }

    std::map<std::string, int>& getConfig()
    {
        return configData;
    }
};
