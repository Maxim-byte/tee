#include <iostream>

#include "Tee.hpp"
#include "settings.hpp"

int main(int argc, const char** argv) {
    auto settings = parse(argc, argv);
    if(settings.errorCode) {
        return settings.errorCode.value();
    }
    Tee<details::api::lin> tee;
    try {
        tee.open(settings.path, settings.mode);
        tee.execute(std::cin, std::cout);
    } catch (const std::runtime_error & e) {
        tee.close();
        std::cerr << e.what() << '\n';
        return -1;
    }
    tee.close();
    return 0;
}
