#pragma once

#include <string>
#include <system_error>

#include "Tee.hpp"

#include <boost/program_options.hpp>

struct settings;

settings parse(int argc, const char** argv);

struct settings {
    std::string path;
    details::mode mode;
    std::error_code errorCode;
};
