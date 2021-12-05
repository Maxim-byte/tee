#pragma once

#include <string>
#include <iosfwd>

struct line_t {
    friend std::ostream& operator<<(std::ostream & out, const line_t & line);

    friend std::istream & operator>>(std::istream & in, line_t & line);

    std::string string;
};

std::ostream& operator<<(std::ostream & out, const line_t & line) {
    return out << line.string;
}

std::istream & operator>>(std::istream & in, line_t & line) {
    return std::getline(in, line.string);
}