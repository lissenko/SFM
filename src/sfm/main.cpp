#include <chrono>
#include <filesystem>
#include <thread>

#include "sfm/Client.hpp"

int main()
{
        // fix: broken window with st
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if (Renderer::init()) {
                Client().start();
        }
        return 0;
}
