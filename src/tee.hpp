#pragma once

#include <system_error>
#include <memory>
#include <fstream>

namespace details {
    enum class mode {
        begin_point,
        end_point
    };
}

class tee {
public:
    tee() = default;

    ~tee() = default;

    tee(const tee & tee) = delete;

    tee & operator=(const tee & tee) = delete;

    void open(const std::string & path, details::mode mode);

    void close();

    void execute(std::istream & input, std::ostream & output);

private:
    std::unique_ptr<std::fstream> file_;
};