#ifndef FILEWRITEONLYSTREAM_H
#define FILEWRITEONLYSTREAM_H

#include <fstream>
#include <string>
#include <functional>

#include "WriteOnlyStream.h"
#include "errors.h"

template <class T> class FileWriteOnlyStream: public WriteOnlyStream<T> {
private:
    std::ofstream file;
    std::string filename;
    std::function<std::string(const T&)> serializer;
    size_t pos;
    bool opened;
public:
    FileWriteOnlyStream(const std::string &name, std::function<std::string(const T&)> ser) {
        filename = name;
        serializer = ser;
        pos = 0;
        opened = false;
    }

    ~FileWriteOnlyStream() {
        Close();
    }

    size_t GetPosition() const {
        return pos;
    }

    size_t Write(T item) {
        if (!opened) throw STREAM_NOT_OPEN;
        std::string token = serializer(item);
        file << token;
        if (file.fail()) throw WRITING_ERROR;
        pos++;
        return pos;
    }

    void Open() {
        if (opened) throw STREAM_NOT_CLOSED;
        file.open(filename);
        if (!file.is_open()) throw STREAM_NOT_OPEN;
        opened = true;
        pos = 0;
    }

    void Close() {
        if (file.is_open()) file.close();
        opened = false;
    }
};

#endif // FILEWRITEONLYSTREAM_H
