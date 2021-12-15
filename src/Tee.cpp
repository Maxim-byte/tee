#include "Tee.hpp"

#include <ostream>
#include <algorithm>
#include <iterator>

#include "line.hpp"

#include <fcntl.h>
#include <unistd.h>

template <>
void Tee<details::api::std>::open(const std::string & path, details::mode mode) {
    mode == details::mode::begin_point ? file_ = std::make_unique<std::fstream>(path, std::ios_base::trunc | std::ios_base::out) :
            file_ = std::make_unique<std::fstream>(path, std::ios_base::app | std::ios_base::out);
    if(!file_->is_open()) {
        throw std::runtime_error("File cannot be open!");
    }
}

template <>
void Tee<details::api::std>::close() {
    file_->close();
}

template <>
void Tee<details::api::std>::execute(std::istream & input, std::ostream & output) {
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



template <>
void Tee<details::api::lin>::open(const std::string & path, details::mode mode) {
    mode == details::mode::begin_point ? file_des_ = ::open(path.c_str(), O_CREAT | O_WRONLY | O_TRUNC) :
            file_des_ = ::open(path.c_str(), O_WRONLY | O_APPEND);
    if(file_des_ == -1) {
        throw std::runtime_error("File cannot be open!");
    }
}

template <>
void Tee<details::api::lin>::close() {
    fsync(file_des_);
    if(::close(file_des_) == -1) {
        throw std::runtime_error("File cannot be close!");
    }
}

template <>
void Tee<details::api::lin>::execute(std::istream & input, std::ostream & output) {
    std::for_each(std::istream_iterator<line_t>(input), std::istream_iterator<line_t>(), [&](const line_t & input_string) {
        if(input.fail()) {
            throw std::system_error(std::make_error_code(std::errc::io_error));
        }
        if(input_string.string.length() != write(file_des_, input_string.string.c_str(), input_string.string.length())) {
            throw std::system_error(std::make_error_code(std::errc::io_error));
        }
        write(file_des_, "\n", 1);
        output << input_string;
    });
    output.flush();
}
