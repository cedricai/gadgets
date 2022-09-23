//
// Created by Cedric Ai on 9/23/2022.
//

#ifndef GADGETS_EVALUATION_HPP
#define GADGETS_EVALUATION_HPP

#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono;

template<typename T>
void print_execute_time(const std::string &name, T func) {
    system_clock::time_point start = system_clock::now();
    func();
    system_clock::time_point end = system_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << name << " time: " << ms.count() << "ms." << std::endl;
}

#endif //GADGETS_EVALUATION_HPP
