#include "settings.hpp"

#include <iostream>
#include <map>

settings parse(int argc, const char **argv) {
    settings settings;

    boost::program_options::options_description m_desc {"Allowed options"};
    boost::program_options::variables_map m_vm;

    m_desc.add_options()
            ("help", "Show help")
            ("exist_path,a", boost::program_options::value<std::string>(&settings.path)->composing(),
             "Set file path for adding to the end")
            ("path", boost::program_options::value<std::string>(&settings.path), "Set file path for Tee");

    try {
        boost::program_options::positional_options_description positionalDescription;
        positionalDescription.add( "path", -1 );
        boost::program_options::store(boost::program_options::command_line_parser (argc, argv).options(m_desc).positional(positionalDescription).run(), m_vm);
        boost::program_options::notify(m_vm);

        if (m_vm.count("help")) {
            std::cout << m_desc << std::endl;
            settings.errorCode = std::make_error_code(std::errc::io_error);
            return settings;
        }
        if (m_vm.count("a")) {
            settings.mode = details::mode::end_point;
        } else if (m_vm.count("path")) {
            settings.mode = details::mode::begin_point;
        }
    } catch (const boost::program_options::error &error) {
        std::cerr << "No such option: " << error.what();
        settings.errorCode = std::make_error_code(std::errc::io_error);
        return settings;
    }
    return settings;
}
