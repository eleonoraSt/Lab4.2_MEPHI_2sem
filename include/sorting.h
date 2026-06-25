#ifndef SORTING_H
#define SORTING_H

#include "FileReadOnlyStream.h"
#include "FileWriteOnlyStream.h"
#include "BinaryHeap.h"

#include <iostream>  // для отладки

template <class T> void sortFileStream(std::string inputFilename, std::string outputFilename, \
                                       std::function<T(const std::string&)> deser, \
                                       std::function<std::string(const T&)> ser) {
    std::cout << "i did start it\n";
    FileReadOnlyStream<T>* inputFile = new FileReadOnlyStream<T>(inputFilename, deser);
    inputFile->Open();
    std::cout << "reading file opened\n";
    BinaryHeap<T>* heap = new BinaryHeap<T>();
    while (!inputFile->IsEndOfStream()) {
        heap->Append(inputFile->Read());
    }
    inputFile->Close();
    delete inputFile;
    heap->pyramidSort();
    FileWriteOnlyStream<T>* outputFile = new FileWriteOnlyStream<T>(outputFilename, ser);
    outputFile->Open();
    std::cout << "writing file opened\n";
    for (size_t index = 0; index < heap->GetSize(); index++) {
        outputFile->Write(heap->Get(index));
    }
    outputFile->Close();
    delete outputFile;
    delete heap;
}

#endif // SORTING_H
