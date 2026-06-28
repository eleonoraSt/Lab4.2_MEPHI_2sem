#include <iostream>

#include "..\include\FileReadOnlyStream.h"
#include "..\include\FileWriteOnlyStream.h"
#include "..\include\SequenceReadOnlyStream.h"
#include "..\include\SequenceWriteOnlyStream.h"

template <class T> void testRead(short* testNumAddress, ReadOnlyStream<T>* stream, T expected) {
    try {
        T buf = stream->Read();
        if (buf == expected) {
            std::cout << "Test " << *testNumAddress << " passed\n";
        } else {
            std::cout << "Test " << *testNumAddress << " failed: expected " << expected << ", got " << \
                buf << " in Read\n";
        }
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNumAddress << " failed: error in Read\n";
    }
    *testNumAddress += 1;
}

template <class T> void testEOF(short* testNumAddress, ReadOnlyStream<T>* stream, bool expected) {
    bool res = stream->IsEndOfStream();
    if (res == expected) {
        std::cout << "Test " << *testNumAddress << " passed\n";
    } else {
        std::cout << "Test " << *testNumAddress << " failed: expected " << expected << ", got " << res \
                  << "in IsEndOfStream\n";
    }
    *testNumAddress += 1;
}

template <class T> void testGetPos(short* testNumAddress, ReadOnlyStream<T>* stream, \
                      size_t expected) {
    size_t pos = stream->GetPosition();
    if (pos == expected) {
        std::cout << "Test " << *testNumAddress << " passed\n";
    } else {
        std::cout << "Test " << *testNumAddress << " failed: expected " << expected << ", got " << pos \
                  << "in GetPosition\n";
    }
    *testNumAddress += 1;
}

template <class T> void testCanSeek(short* testNumAddress, ReadOnlyStream<T>* stream, bool expected) {
    bool res = stream->IsCanSeek();
    if (res == expected) {
        std::cout << "Test " << *testNumAddress << " passed\n";
    } else {
        std::cout << "Test " << *testNumAddress << " failed: expected " << expected << ", got " << res \
                  << "in IsCanSeek\n";
    }
    *testNumAddress += 1;
}

template <class T> void testSeek(short* testNumAddress, ReadOnlyStream<T>* stream, size_t pos) {
    try {
        stream->Seek(pos);
        if (stream->GetPosition() == pos) {
            std::cout << "Test " << *testNumAddress << " passed\n";
        } else {
            std::cout << "Test " << *testNumAddress << " failed: expected position " << pos << ", got " \
                      << stream->GetPosition() << " in Seek\n";
        }
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNumAddress << " failed: error in Seek\n";
    }
    *testNumAddress += 1;
}

template <class T> void testSeekError(short* testNumAddress, ReadOnlyStream<T>* stream, size_t pos) {
    try {
        stream->Seek(pos);
        std::cout << "Test " << *testNumAddress << " failed: error not raised in Seek\n";
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNumAddress << " passed\n";
    }
    *testNumAddress += 1;
}

template <class T> void testCanGoBack(short* testNumAddress, ReadOnlyStream<T>* stream, bool expected) {
    bool res = stream->IsCanGoBack();
    if (res == expected) {
        std::cout << "Test " << *testNumAddress << " passed\n";
    } else {
        std::cout << "Test " << *testNumAddress << " failed: expected " << expected << ", got " << res \
                  << "in IsCanGoBack\n";
    }
    *testNumAddress += 1;
}