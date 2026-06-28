#include <iostream>

#include "..\include\FileReadOnlyStream.h"
#include "..\include\FileWriteOnlyStream.h"
#include "..\include\SequenceReadOnlyStream.h"
#include "..\include\SequenceWriteOnlyStream.h"
#include "..\include\serializing.h"

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

template <class T> void testReadError(short* testNumAddress, ReadOnlyStream<T>* stream) {
    try {
        stream->Read();
        std::cout << "Test " << *testNumAddress << " failed: error not raised in Read\n";
    } catch (ErrorCode error) {
        std::cout << "Test " << *testNumAddress << " passed\n";
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

template <class T> void testGetPosReading(short* testNumAddress, ReadOnlyStream<T>* stream, \
                      size_t expected) {
    size_t pos = stream->GetPosition();
    if (pos == expected) {
        std::cout << "Test " << *testNumAddress << " passed\n";
    } else {
        std::cout << "Test " << *testNumAddress << " failed: expected " << expected << ", got " << pos \
                  << "in GetPosition in ReadOnlyStream\n";
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

template <class T> void testGetPosWriting(short* testNumAddress, WriteOnlyStream<T>* stream, \
                       size_t expected) {
    size_t pos = stream->GetPosition();
    if (pos == expected) {
        std::cout << "Test " << *testNumAddress << " passed\n";
    } else {
        std::cout << "Test " << *testNumAddress << " failed: expected " << expected << ", got " << pos \
                  << "in GetPosition in WriteOnlyStream\n";
    }
    *testNumAddress += 1;
}

void runAllTestStream() {
    short testNum = 1;
    short* testNumAddress = &testNum;

    FileWriteOnlyStream<int>* intOutput = new FileWriteOnlyStream<int>("testInt.txt", int2strSerializer);
    FileWriteOnlyStream<double>* doubleOutput = new FileWriteOnlyStream<double>("testDouble.txt", \
                                                                              double2strSerializer);
    intOutput->Open();
    doubleOutput->Close();
    intOutput->Write(1);
    doubleOutput->Write(0.5);

    testGetPosWriting(testNumAddress, intOutput, 1);
    testGetPosWriting(testNumAddress, doubleOutput, 1);

    intOutput->Close();
    doubleOutput->Close();
    delete intOutput;
    delete doubleOutput;

    FileReadOnlyStream<int>* intInput = new FileReadOnlyStream<int>("testInt.txt", str2intDeserializer);
    FileReadOnlyStream<double>* doubleInput = new FileReadOnlyStream<double>("testDouble.txt", \
                                                                          str2doubleDeserializer);

    testEOF(testNumAddress, intInput, false);
    testEOF(testNumAddress, doubleInput, false);
    testRead(testNumAddress, intInput, 1);
    testRead(testNumAddress, doubleInput, 0.5);
    testGetPosReading(testNumAddress, intInput, 1);
    testGetPosReading(testNumAddress, doubleInput, 1);
    testReadError(testNumAddress, intInput);
    testReadError(testNumAddress, doubleInput);
    testEOF(testNumAddress, intInput, true);
    testEOF(testNumAddress, doubleInput, true);

    testCanSeek(testNumAddress, intInput, false);
    testCanSeek(testNumAddress, doubleInput, false);
    testSeekError(testNumAddress, intInput, 0);
    testSeekError(testNumAddress, doubleInput, 0);
    testCanGoBack(testNumAddress, intInput, false);
    testCanGoBack(testNumAddress, doubleInput, false);

    intInput->Close();
    doubleInput->Close();
    delete intInput;
    delete doubleInput;
}
