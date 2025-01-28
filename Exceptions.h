#ifndef SEAFIGHT_EXCEPTIONS_H
#define SEAFIGHT_EXCEPTIONS_H
#include <iostream>
#include <utility>

class NoAbilityError: public std::exception{
    public:
        std::string msg;
        explicit NoAbilityError(std::string error) : msg(std::move(error)) {}
        [[nodiscard]] const char * what() const noexcept override {
            return msg.c_str();
        }
};

class ShipError: public std::exception{
public:
    std::string msg;
    explicit ShipError(std::string error) : msg(std::move(error)) {}
    [[nodiscard]] const char * what() const noexcept override {
        return msg.c_str();
    }
};

class CoordinatesError: public std::exception{
public:
    std::string msg;
    explicit CoordinatesError(std::string error) : msg(std::move(error)) {}
    [[nodiscard]] const char * what() const noexcept override {
        return msg.c_str();
    }
};

class PositiveIntError: public std::exception{
public:
    std::string msg;
    explicit PositiveIntError(std::string error) : msg(std::move(error)) {}
    [[nodiscard]] const char * what() const noexcept override {
        return msg.c_str();
    }
};

class ManyShipsError: public std::exception{
public:
    std::string msg;
    explicit ManyShipsError(std::string error) : msg(std::move(error)) {}
    [[nodiscard]] const char * what() const noexcept override {
        return msg.c_str();
    }
};

class OrientationError: public std::exception{
public:
    std::string msg;
    explicit OrientationError(std::string error) : msg(std::move(error)) {}
    [[nodiscard]] const char * what() const noexcept override {
        return msg.c_str();
    }
};


#endif //SEAFIGHT_EXCEPTIONS_H
