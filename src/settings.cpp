#include "settings.hpp"

#include <iostream>
#include <map>

std::error_code settings::parse(int argc, const char **argv) {
    m_desc.add_options()
            ("help", "Show help")
            ("exist_path,a", boost::program_options::value<std::string>(&path)->composing(),
             "Set file path for adding to the end")
            ("path", boost::program_options::value<std::string>(&path), "Set file path for tee");

    try {
        boost::program_options::positional_options_description positionalDescription;
        positionalDescription.add( "path", -1 );
        boost::program_options::store(boost::program_options::command_line_parser (argc, argv).options(m_desc).positional(positionalDescription).run(), m_vm);
        boost::program_options::notify(m_vm);

        if (m_vm.count("help")) {
            std::cout << m_desc << std::endl;
            return std::make_error_code(std::errc::no_message);
        }
        if (m_vm.count("a")) {
            mode = details::mode::end_point;
        } else if (m_vm.count("path")) {
            mode = details::mode::begin_point;
        }
    } catch (const boost::program_options::error &error) {
        std::cerr << "No such option: " << error.what();
        return std::make_error_code(std::errc::protocol_error);
    }
    return {};
}
