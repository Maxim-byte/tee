#include <iostream>

#include "tee.hpp"
#include "settings.hpp"

int main(int argc, const char** argv) {
    settings setting;
    auto ec = setting.parse(argc, argv);
    if(ec) {
        return ec.value();
    }
    tee tee;
    try {
        tee.open(setting.path, setting.mode);
        tee.execute(std::cin, std::cout);
    } catch (const std::runtime_error & e) {
        tee.close();
        std::cerr << e.what() << '\n';
        return -1;
    }
    tee.close();
    return 0;
}
