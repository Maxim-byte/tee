#pragma once

#include <string>
#include <system_error>

#include "tee.hpp"

#include <boost/program_options.hpp>

struct settings {
    std::string path;
    details::mode mode;

    std::error_code parse(int argc, const char** argv);

private:
    boost::program_options::options_description m_desc {"Allowed options"};
    boost::program_options::variables_map m_vm;
};