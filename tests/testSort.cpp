#include <random>
#include <climits>
#include <cfloat>

#include "..\include\FileReadOnlyStream.h"
#include "..\include\FileWriteOnlyStream.h"
#include "..\include\serializing.h"

void generateRandomFileInt(size_t length, std::string filename) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(INT_MIN, INT_MAX);
    FileWriteOnlyStream<int>* outputStream = new FileWriteOnlyStream<int>(filename, int2strSerializer);
    outputStream->Open();
    for (size_t index = 0; index < length; index++) {
        outputStream->Write(distribution(generator));
    }
    outputStream->Close();
    delete outputStream;
}

void generateRandomFileDouble(size_t length, std::string filename) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<> distribution(DBL_MIN, DBL_MAX);
    FileWriteOnlyStream<double>* outputStream = \
        new FileWriteOnlyStream<double>(filename, double2strSerializer);
    outputStream->Open();
    for (size_t index = 0; index < length; index++) {
        outputStream->Write(distribution(generator));
    }
    outputStream->Close();
    delete outputStream;
}
