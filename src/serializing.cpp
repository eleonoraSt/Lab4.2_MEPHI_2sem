#include <stdexcept>

#include "..\include\serializing.h"

int str2intDeserializer(const std::string &str) {
    int val = 0;
    try {
        val = stoi(str);
    } catch (std::out_of_range error) {
        val = 0;
    }
    return val;
}

std::string int2strSerializer(const int &val) {
    return std::to_string(val);
}

double str2doubleDeserializer(const std::string &str) {
    double val = 0;
    try {
        val = stod(str);
    } catch (std::out_of_range error) {
        val = 0;
    }
    return val;
}

std::string double2strSerializer(const double &val) {
    return std::to_string(val);
}
