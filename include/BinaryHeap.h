#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <cstdlib>  // size_t

#include "DynamicArray.h"

template <class T> class BinaryHeap {
private:
    DynamicArray<T> heap;
public:
    BinaryHeap(T* data, size_t size) {
        heap = new DynamicArray<T>(data, size);
    }

    void PyramidSort() {

    }
};

#endif // BINARYHEAP_H
