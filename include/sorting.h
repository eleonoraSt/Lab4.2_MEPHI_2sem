#ifndef SORTING_H
#define SORTING_H

#include "FileReadOnlyStream.h"
#include "FileWriteOnlyStream.h"
#include "SequenceReadOnlyStream.h"
#include "SequenceWriteOnlyStream.h"
#include "BinaryHeap.h"

#include <iostream>  // отладка

template <class T> void sortFileStream(std::string inputFilename, std::string outputFilename, \
                                       std::function<T(const std::string&)> deser, \
                                       std::function<std::string(const T&)> ser) {
    std::cout << "called the func\n";
    FileReadOnlyStream<T>* inputFile = new FileReadOnlyStream<T>(inputFilename, deser);
    inputFile->Open();
    std::cout << "input file opened\n";
    BinaryHeap<T>* heap = new BinaryHeap<T>();
    while (!inputFile->IsEndOfStream()) {
        //heap->Append(inputFile->Read());
        try {
            T buf = inputFile->Read();
            std::cout << buf << "\n";
            heap->Append(buf);
        } catch (ErrorCode error) {}
    }
    inputFile->Close();
    std::cout << "input file closed\n";
    delete inputFile;
    heap->pyramidSort();
    FileWriteOnlyStream<T>* outputFile = new FileWriteOnlyStream<T>(outputFilename, ser);
    outputFile->Open();
    std::cout << "output file opened\n";
    for (size_t index = 0; index < heap->GetSize(); index++) {
        outputFile->Write(heap->Get(index));
    }
    outputFile->Close();
    std::cout << "output file closed\n";
    delete outputFile;
    delete heap;
}

template <class T> std::string sortSeqStream(SequenceReadOnlyStream<T>* inputStream) {
    BinaryHeap<T>* heap = new BinaryHeap<T>();
    while (!inputStream->IsEndOfStream()) {
        heap->Append(inputStream->Read());
    }
    heap->pyramidSort();
    SequenceWriteOnlyStream<T>* outputStream = new SequenceWriteOnlyStream<T>();
    std::string output = "";
    T buf;
    for (size_t index = 0; index < heap->GetSize(); index++) {
        buf = heap->Get(index);
        outputStream->Write(buf);
        output += std::to_string(buf) + " ";
    }
    delete outputStream;
    delete heap;
    return output;
}

#endif // SORTING_H
