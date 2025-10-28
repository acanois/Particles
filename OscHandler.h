//
// Created by David Richter on 10/27/25.
//

#pragma once

#include <lo/lo.h>
#include <lo/lo_cpp.h>

class OscHandler
{
public:
    explicit OscHandler(const int port)
        : serverThread(port)
    {
    }

    ~OscHandler()
    {
        serverThread.stop();
    }

    void startOscThread()
    {
        serverThread.start();
    }

    void stopOscThread()
    {
        serverThread.stop();
    }

    void setCallbacks(
        const std::function<void()>& input,
        const std::function<void()>& cleanup
    )
    {
        serverThread.set_callbacks(input, cleanup);
    }

    void addMethod(
        const std::string& tag,
        const std::string& tagType,
        const std::function<void(lo_arg** argv, int)>& func
    )
    {
        serverThread.add_method(tag, tagType, func);
    }

private:
    lo::ServerThread serverThread;
};
