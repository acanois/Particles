#include <iostream>

#include "Scene.h"


int main()
{
    const auto scene = std::make_unique<Scene>();
    scene->run();

    return 0;
}
