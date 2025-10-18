//
// Created by David Richter on 10/18/25.
//

#pragma once

#include <iostream>
#include <lo/lo.h>
#include <lo/lo_cpp.h>

class OscHandler
{
public:
    OscHandler() : serverThread(7000)
    {
    }

    void setCallbacks(
        const std::function<void()>& input,
        const std::function<void()>& cleanup)
    {
        // Wrapper for set_callbacks()
        serverThread.set_callbacks(input, cleanup);
    }

    void addMethod(
        const std::string& name,
        const std::string& type,
        const std::function<void(lo_arg** argv, int)>& func)
    {
        // Wrapper for add_method()
        serverThread.add_method(name, type, func);
    }

    void startThread()
    {
        // Wrapper for start()
        serverThread.start();
    }

private:
    lo::ServerThread serverThread;
};
