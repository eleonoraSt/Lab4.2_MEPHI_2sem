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

#define EPSILON 1e-6

void generateRandomFileInt(size_t length, std::string filename) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(-1000, 1000);
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
    std::uniform_real_distribution<> distribution(-1000, 1000);
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
        T prev = minLimit, buf = minLimit;
        bool sorted = true;
        while (!inputStream->IsEndOfStream() && sorted) {
            try {
                prev = buf;
                buf = inputStream->Read();
                sorted = buf - prev >= -EPSILON;
            } catch (ErrorCode error) {}
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

template <class T> void testSort(short* testNumAddress, Sequence<T>* seq, T minLimit) {
    BinaryHeap<T>* heap = new BinaryHeap<T>();
    T buf = minLimit;
    T prev = minLimit;
    bool sorted = true;
    size_t length = seq->GetLength();
    for (size_t index = 0; index < length; index++) {
        heap->Append(seq->Get(index));
    }
    heap->pyramidSort();
    size_t index;
    for (index = 0; index < heap->GetSize() && sorted; index++) {
        prev = buf;
        buf = heap->Get(index);
        sorted = buf - prev >= -EPSILON;
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

template <class T> void testInputSort(short* testNumAddress, T minLimit) {
    BinaryHeap<T>* heap = new BinaryHeap<T>();
    T buf;
    T prev = minLimit;
    bool sorted = true;
    try {
        while (std::cin >> buf) {
            heap->Append(buf);
        }
    } catch (ErrorCode error) {
        return;
    }
    heap->pyramidSort();
    size_t index;
    for (index = 0; index < heap->GetSize() && sorted; index++) {
        prev = buf;
        buf = heap->Get(index);
        sorted = buf - prev >= -EPSILON;
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
    isFileSorted<double>(testNumAddress, DOUBLE_O_FILENAME, str2doubleDeserializer, -DBL_MAX);

    int intArray[] = {10, 8, -1, 3, -3, 5};
    double doubleArray[] = {0.5, -0.25, -3.75, 10, 0, 1.125};
    ArraySequence<int>* intSeq = new ArraySequence<int>(intArray, 6);
    ArraySequence<double>* doubleSeq = new ArraySequence<double>(doubleArray, 6);

    testSort<int>(testNumAddress, intSeq, INT_MIN);
    testSort<double>(testNumAddress, doubleSeq, -DBL_MAX);

    delete intSeq;
    delete doubleSeq;

    //testInputSort<int>(testNumAddress, INT_MIN);
    //testInputSort<double>(testNumAddress, -DBL_MAX);
}
