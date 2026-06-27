#include <random>
#include <climits>
#include <cfloat>
#include <iostream>

#include "testSort.h"
#include "..\include\FileWriteOnlyStream.h"
#include "..\include\serializing.h"
#include "..\include\sorting.h"

#define INT_I_FILENAME "testIntInput.txt"
#define INT_O_FILENAME "testIntOutput.txt"
#define DOUBLE_I_FILENAME "testDoubleInput.txt"
#define DOUBLE_O_FILENAME "testDoubleOutput.txt"

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

template <class T> void isFileSorted(short* testNumAddress, std::string filename, \
                  std::function<T(const std::string&)> deser, T minLimit) {
    FileReadOnlyStream<T>* inputStream = new FileReadOnlyStream(filename, deser);
    try {
        inputStream->Open();
        T prev = minLimit, buf;
        bool sorted = true;
        while (!inputStream->IsEndOfStream() && sorted) {
            buf = inputStream->Read();
            sorted = prev <= buf;
            prev = buf;
        }
        if (sorted) {
            std::cout << "Test " << *testNumAddress << " passed\n";
        } else {
            std::cout << "Test " << *testNumAddress << " not passed: " << prev << " > " << prev << \
                " at position " << inputStream->GetPosition() << " in " << filename << "\n";
        }
    } catch (ErrorCode error) {
        if (error == STREAM_NOT_OPEN) {
            std::cout << "Test " << *testNumAddress << \
                " not passed: can't open file in FileReadOnlyStream\n";
        } else if (error == READING_ERROR) {
            std::cout << "Test " << *testNumAddress << \
                " not passed: reading error in FileReadOnlyStream\n";
        }
    }
    inputStream->Close();
    delete inputStream;
    *testNumAddress += 1;
}

/*
template <class T> void testSeqSort(short* testNumAddress) {
    Sequence<T>* seq = new ListSequence<T>();
    T buf;
    size_t length = 0;
    while (std::cin >> buf) {
        seq->Append(buf);
        length++;
    }
    SequenceReadOnlyStream<T>* inputStream = new SequenceReadOnlyStream<T>(seq);
    BinaryHeap<T>* heap = new BinaryHeap<T>();
    for (size_t index = 0; index < length; index++) {
        heap->Append(seq->Get(index));
    }
    heap->pyramidSort();
    for (size_t index = 0; index < length; index++) {

    }
}
*/

template <class T> void testSort(short* testNumAddress, T minLimit) {
    BinaryHeap<T>* heap = new BinaryHeap<T>();
    T buf;
    T prev = minLimit;
    bool sorted = true;
    while (std::cin >> buf) {
        heap->Append(buf);
    }
    heap->pyramidSort();
    size_t index;
    for (index = 0; index < heap->GetSize() && sorted; index++) {
        buf = heap->Get(index);
        sorted = prev <= buf;
        prev = buf;
    }
    if (sorted) {
        std::cout << "Test " << *testNumAddress << " passed\n";
    } else {
        std::cout << "Test " << *testNumAddress << " failed: " << prev << " > " << buf << " at index " \
                  << index << " in sequence sorting\n";
    }
    for (index = 0; index < heap->GetSize(); index++) {
        std::cout << heap->Get(index) << " ";
    }
    std::cout << "\n";
    delete heap;
    *testNumAddress += 1;
}

void runAllTestSort() {
    size_t length = 1000000;
    try {
        generateRandomFileInt(length, INT_I_FILENAME);
        sortFileStream<int>(INT_I_FILENAME, INT_O_FILENAME, str2intDeserializer, int2strSerializer);
        std::cout << "\"" << INT_I_FILENAME << "\" sorted\n";
    } catch (ErrorCode error) {
        if (error == STREAM_NOT_OPEN) {
            std::cout << "Can't open files in integer sorting\n";
        } else if (error == READING_ERROR) {
            std::cout << "Reading error in " << INT_I_FILENAME << "\n";
        } else if (error == WRITING_ERROR) {
            std::cout << "Writing error in " << INT_O_FILENAME << "\n";
        }
    }

    try {
        generateRandomFileDouble(length, DOUBLE_I_FILENAME);
        sortFileStream<double>(DOUBLE_I_FILENAME, DOUBLE_O_FILENAME, str2doubleDeserializer, \
                               double2strSerializer);
        std::cout << "\"" << DOUBLE_I_FILENAME << "\" sorted\n";
    } catch (ErrorCode error) {
        if (error == STREAM_NOT_OPEN) {
            std::cout << "Can't open files in double sorting\n";
        } else if (error == READING_ERROR) {
            std::cout << "Reading error in " << DOUBLE_I_FILENAME << "\n";
        } else if (error == WRITING_ERROR) {
            std::cout << "Writing error in " << DOUBLE_O_FILENAME << "\n";
        }
    }

    short testNum = 1;
    short* testNumAddress = &testNum;

    isFileSorted<int>(testNumAddress, INT_O_FILENAME, str2intDeserializer, INT_MIN);
    isFileSorted<double>(testNumAddress, DOUBLE_O_FILENAME, str2doubleDeserializer, DBL_MIN);

    testSort<int>(testNumAddress, INT_MIN);
    testSort<double>(testNumAddress, DBL_MIN);
}
