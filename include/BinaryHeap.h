#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <cstdlib>  // size_t

#include "DynamicArray.h"

template <class T> class BinaryHeap {
private:
    DynamicArray<T>* heap;
    size_t unsorted;

    void siftDown(size_t index, bool goDeep) {
        size_t child1 = 2 * index + 1, child2 = 2 * index + 2;
        if (child1 >= unsorted) return;
        size_t maxChild;
        if (child2 < unsorted) {
            maxChild = heap->Get(child1) > heap->Get(child2) ? child1 : child2;
        } else {  // есть только один потомок
            maxChild = child1;
        }
        size_t newIndex = index;
        if (heap->Get(index) > heap->Get(maxChild)) {
            T buf = heap->Get(index);
            heap->Set(index, heap->Get(maxChild));
            heap->Set(maxChild, buf);
            newIndex = maxChild;
        }
        // goDeep - чтобы не тратить время на сравнения, если нужно просеять на 1 ступень (1 этап)
        if (newIndex != index && goDeep) siftDown(newIndex, goDeep);
    }
public:
    /*
    BinaryHeap(T* data, size_t size) {
        heap = new DynamicArray<T>(data, size);
        unsorted = size;
    }
*/
    BinaryHeap(DynamicArray<T>* array) {
        heap = array;
        unsorted = array->GetSize();
    }

    BinaryHeap() {
        heap = new DynamicArray<T>(0);
        unsorted = 0;
    }

    ~BinaryHeap() {
        delete heap;
    }

    void pyramidSort() {
        for (int index = unsorted - 1; index >= 0; index--) {
            siftDown(index, false);
        }
        T buf = heap->Get(0);
        heap->Set(0, heap->Get(unsorted - 1));
        heap->Set(unsorted - 1, buf);
        unsorted--;
        while (unsorted > 0) {
            siftDown(0, true);
            buf = heap->Get(0);
            heap->Set(0, heap->Get(unsorted - 1));
            heap->Set(unsorted - 1, buf);
            unsorted--;
        }
    }
};

#endif // BINARYHEAP_H
