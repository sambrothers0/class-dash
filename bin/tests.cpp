#include <physics/Vector2.hpp>

#include <iostream>

int main() {
    // This file just tests functionality

    // Vector2
    Vector2 vec(3.0, 4.0);

    std::cout << vec.magnitude() << std::endl;
    std::cout << vec << std::endl;
    std::cout << vec.normal() << std::endl;

    return 0;
}