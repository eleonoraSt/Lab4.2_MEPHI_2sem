#ifndef SERIALIZING_H
#define SERIALIZING_H

#include <string>

int str2intDeserializer(const std::string &str);

std::string int2strSerializer(const int &val);

double str2doubleDeserializer(const std::string &str);

std::string double2strSerializer(const double &val);

#endif // SERIALIZING_H
