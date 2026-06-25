#include <iostream>

#include "../include/ListSequence.h"
#include "../include/ArraySequence.h"

template <class T> void testGetFirst(short* testNum, Sequence<T>* seq, T expected) {
    try {
        T result = seq->GetFirst();
        if (result == expected) {
            std::cout << "Test " << *testNum << " passed\n";
        } else {
            std::cout << "Test " << *testNum << " failed: expected " << expected << ", got " \
                      << result << " in GetFirst\n";
        }
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " failed: error in GetFirst\n";
    }
    *testNum += 1;
}

template <class T> void testGetFirstIndexError(short* testNum, Sequence<T>* seq) {
    try {
        seq->GetFirst();
        std::cout << "Test " << *testNum << " failed: error not raised in GetFirst\n";
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " passed\n";
    }
    *testNum += 1;
}

template <class T> void testGetLast(short* testNum, Sequence<T>* seq, T expected) {
    try {
        T result = seq->GetLast();
        if (result == expected) {
            std::cout << "Test " << *testNum << " passed\n";
        } else {
            std::cout << "Test " << *testNum << " failed: expected " << expected << ", got " << result << \
                " in GetLast\n";
        }
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " failed: error in GetLast\n";
    }
    *testNum += 1;
}

template <class T> void testGetLastIndexError(short* testNum, Sequence<T>* seq) {
    try {
        seq->GetLast();
        std::cout << "Test " << *testNum << " failed: error not raised in GetLast\n";
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " passed\n";
    }
    *testNum += 1;
}

template <class T> void testGet(short *testNum, Sequence<T>* seq, T expected, int index) {
    try {
        T result = seq->Get(index);
        if (result == expected) {
            std::cout << "Test " << *testNum << " passed\n";
        } else {
            std::cout << "Test " << *testNum << " failed: expected " << expected << " at index " << \
                index << ", got " << result << " in Get\n";
        }
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " failed: error with size " << seq->GetLength() << \
            ", index " << index << " in Get\n";
    }
    *testNum += 1;
}

template <class T> void testGetIndexError(short* testNum, Sequence<T>* seq, int index) {
    try {
        seq->Get(index);
        std::cout << "Test " << *testNum << " failed: size " << seq->GetLength() << ", index " << \
            index << ", error not raised in Get\n";
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " passed\n";
    }
    *testNum += 1;
}

template <class T> void testGetSubseq(short* testNum, Sequence<T>* seq, Sequence<T>* expected, int start, \
                   int end) {
    try {
        Sequence<T>* subseq = seq->GetSubsequence(start, end);
        int size = subseq->GetLength(), expectedSize = expected->GetLength();
        int index = 0;
        bool equal = size == expectedSize;
        while (index < size && equal) {
            equal = expected->Get(index) == subseq->Get(index);
            index++;
        }
        if (equal) {
            std::cout << "Test " << *testNum << " passed\n";
        } else {
            std::cout << "Test " << *testNum << " failed: expected \n";
            for (int index = 0; index < expectedSize; index++) {
                std::cout << expected->Get(index) << " ";
            }
            std::cout << "\ngot\n";
            for (int index = 0; index < size; index++) {
                std::cout << subseq->Get(index) << " ";
            }
            std::cout << " in GetSubsequence\n";
        }
        delete subseq;
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " failed: error with size " << seq->GetLength() << \
            ", subseq from " << start << " to " << end << " in GetSubsequence\n";
    }
    *testNum += 1;
}

template <class T> void testGetSubseqIndexError(short* testNum, Sequence<T>* seq, int start, int end) {
    try  {
        Sequence<T>* subseq = seq->GetSubsequence(start, end);
        std::cout << "Test " << *testNum << " failed: size " << seq->GetLength() << ", subseq from " << \
            start << " to " << end << ", error not raised in GetSubsequence\n";
        delete subseq;
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " passed\n";
    }
    *testNum += 1;
}

template <class T> void testGetLength(short* testNum, Sequence<T>* seq, int expected) {
    int size = seq->GetLength();
    if (size == expected) {
        std::cout << "Test " << *testNum << " passed\n";
    } else {
        std::cout << "Test " << *testNum << " failed: expected " << expected << ", got " << size << \
            " in GetLength\n";
    }
    *testNum += 1;
}

template <class T> void testAppend(short* testNum, Sequence<T>* seq, T toAdd) {
    seq->Append(toAdd);
    T last = seq->GetLast();
    if (last == toAdd) {
        std::cout << "Test " << *testNum << " passed\n";
    } else {
        std::cout << "Test " << *testNum << " failed: expected last " << toAdd << ", got " << last << \
            " after Append\n";
    }
    *testNum += 1;
}

template <class T> void testPrepend(short* testNum, Sequence<T>* seq, T toAdd) {
    seq->Prepend(toAdd);
    T first = seq->GetFirst();
    if (first == toAdd) {
        std::cout << "Test " << *testNum << " passed\n";
    } else {
        std::cout << "Test " << *testNum << " failed: expected last " << toAdd << ", got " << first << \
            " after Prepend\n";
    }
    *testNum += 1;
}

template <class T> void testInsertAt(short* testNum, Sequence<T>* seq, T toAdd, int index) {
    try {
        seq->InsertAt(toAdd, index);
        T inPlace = seq->Get(index);
        if (inPlace == toAdd) {
            std::cout << "Test " << *testNum << " passed\n";
        } else {
            std::cout << "Test " << *testNum << " failed: expected " << toAdd << "at index " << index \
                      << ", got " << inPlace << " after InsertAt\n";
        }
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " failed: error in InsertAt\n";
    }
    *testNum += 1;
}

template <class T> void testInsertAtIndexError(short* testNum, Sequence<T>* seq, T toAdd, int index) {
    try {
        seq->InsertAt(toAdd, index);
        std::cout << "Test " << *testNum << " failed: inserting " << toAdd << " at index " << index << \
            ", error not raised in InsertAt\n";
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNum << " passed\n";
    }
    *testNum += 1;
}

template <class T> void testConcat(short* testNum, Sequence<T>* seq, Sequence<T>* toConnect) {
    int oldSize1 = seq->GetLength(), oldSize2 = toConnect->GetLength();
    seq->Concat(toConnect);
    bool valid = seq->GetLength() == oldSize1 + oldSize2;
    if (!valid) {
        std::cout << "Test " << *testNum << " failed: concatenated size expected " << \
                                                                                          oldSize1 + oldSize2 << ", got " << seq->GetLength() << "\n";
        return;
    }
    int index = 0;
    for (; index < oldSize2 && valid; index++) {
        valid = seq->Get(oldSize1 + index) == toConnect->Get(index);
    }
    if (valid) {
        std::cout << "Test " << *testNum << " passed\n";
    } else {
        std::cout << "Test " << *testNum << " failed: element number " << index << " expected " << \
                                                                                                   toConnect->Get(index) << ", got " << seq->Get(index + oldSize1);
    }
    *testNum += 1;
}

void runAllTestSequence() {
    short testNum = 1;
    short* testNumAddress = &testNum;
    int baseArray[] = {1, 2, 3};
    int baseArraySize = 3;

    ListSequence<int>* intList = new ListSequence<int>(baseArray, baseArraySize);
    ArraySequence<int>* intArray = new ArraySequence<int>(baseArray, baseArraySize);
    ListSequence<int>* emptyList = new ListSequence<int>();
    ArraySequence<int>* emptyArray = new ArraySequence<int>();

    testGetFirst<int>(testNumAddress, intList, 1);
    testGetFirst<int>(testNumAddress, intArray, 1);
    testGetFirstIndexError<int>(testNumAddress, emptyList);
    testGetFirstIndexError<int>(testNumAddress, emptyArray);

    testGetLast<int>(testNumAddress, intList, 3);
    testGetLast<int>(testNumAddress, intArray, 3);
    testGetLastIndexError<int>(testNumAddress, emptyList);
    testGetLastIndexError<int>(testNumAddress, emptyArray);

    testGet<int>(testNumAddress, intList, 2, 1);
    testGet<int>(testNumAddress, intArray, 2, 1);

    testGetIndexError(testNumAddress, emptyList, 3);
    testGetIndexError(testNumAddress, emptyArray, 3);

    int subseqArray[] = {2, 3};
    ArraySequence<int>* expectedSubseq = new ArraySequence<int>(subseqArray, 2);  // type of seq doesn't matter

    testGetSubseq(testNumAddress, intList, expectedSubseq, 1, 2);
    testGetSubseq(testNumAddress, intArray, expectedSubseq, 1, 2);

    delete expectedSubseq;

    testGetSubseqIndexError(testNumAddress, intList, -1, 2);
    testGetSubseqIndexError(testNumAddress, intList, 2, 1);
    testGetSubseqIndexError(testNumAddress, intArray, -1, 2);
    testGetSubseqIndexError(testNumAddress, intArray, 2, 1);

    testGetLength(testNumAddress, intList, 3);
    testGetLength(testNumAddress, intArray, 3);
    testGetLength(testNumAddress, emptyList, 0);
    testGetLength(testNumAddress, emptyArray, 0);

    testAppend(testNumAddress, intList, 5);
    testAppend(testNumAddress, intArray, 5);

    testPrepend(testNumAddress, intList, 0);
    testPrepend(testNumAddress, intArray, 0);

    testInsertAt(testNumAddress, intList, 4, 4);
    testInsertAt(testNumAddress, intArray, 4, 4);

    testInsertAtIndexError(testNumAddress, emptyList, 1, 1);
    testInsertAtIndexError(testNumAddress, emptyArray, 1, 1);

    delete intList;
    delete intArray;
    delete emptyList;
    delete emptyArray;
}