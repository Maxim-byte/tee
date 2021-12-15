#pragma once

#include <system_error>
#include <memory>
#include <fstream>

namespace details {
    enum class mode {
        begin_point,
        end_point
    };
    enum class api {
        lin,
        std
    };
}

template <typename details::api>
class Tee {
public:
    Tee() = default;

    ~Tee() = default;

    Tee(const Tee & tee) = delete;

    Tee & operator=(const Tee & tee) = delete;

    void open(const std::string & path, details::mode mode);

    void close();

    void execute(std::istream & input, std::ostream & output);

private:
    std::unique_ptr<std::fstream> file_;
    int file_des_;
};
