#include "tee.hpp"

#include <ostream>
#include <algorithm>
#include <iterator>

#include "line.hpp"

void tee::open(const std::string & path, details::mode mode) {
    mode == details::mode::begin_point ? file_ = std::make_unique<std::fstream>(path, std::ios_base::trunc | std::ios_base::out) :
            file_ = std::make_unique<std::fstream>(path, std::ios_base::app | std::ios_base::out);
    if(!file_->is_open()) {
        throw std::runtime_error("File cannot be open!");
    }
}

void tee::close() {
    file_->close();
}

void tee::execute(std::istream & input, std::ostream & output) {
    std::for_each(std::istream_iterator<line_t>(input), std::istream_iterator<line_t>(), [&](const line_t & input_string) {
        if(input.fail()) {
            throw std::system_error(std::make_error_code(std::errc::io_error));
        }
        output << input_string;
        *file_ << input_string;
    });
    output.flush();
    file_->flush();
}
