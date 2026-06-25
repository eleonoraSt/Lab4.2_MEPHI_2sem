#ifndef FILEREADONLYSTREAM_H
#define FILEREADONLYSTREAM_H

#include <fstream>
#include <string>
#include <functional>

#include "ReadOnlyStream.h"
#include "errors.h"

template <class T> class FileReadOnlyStream: public ReadOnlyStream<T> {
private:
    std::ifstream file;
    std::string filename;
    std::function<T(const std::string&)> deserializer;
    size_t pos;
    bool opened;
    bool eofReached;
public:
    FileReadOnlyStream(const std::string &name, std::function<T(const std::string&)> deser) {
        filename = name;
        deserializer = deser;
        pos = 0;
        opened = false;
        eofReached = false;
    }

    ~FileReadOnlyStream() {
        Close();
    }

    bool IsEndOfStream() {
        if (!opened) return true;
        if (file.eof()) {
            eofReached = true;
        }
        return eofReached;
    }

    T Read() {
        if (!opened) throw STREAM_NOT_OPEN;
        if (IsEndOfStream()) throw END_OF_STREAM;
        std::string token;
        file >> token;
        if (file.eof()) {
            eofReached = true;
            throw END_OF_STREAM;
        }
        if (file.fail()) throw READING_ERROR;
        T item = deserializer(token);
        pos++;
        return item;
    }

    size_t GetPosition() const {
        return pos;
    }

    bool IsCanSeek() const {
        return false;
    }

    size_t Seek(size_t index) {
        throw SEEK_NOT_SUPPORTED;
    }

    bool IsCanGoBack() const {
        return false;
    }

    void Open() {
        if (opened) throw STREAM_NOT_CLOSED;
        file.open(filename);
        if (!file.is_open()) throw STREAM_NOT_OPEN;
        opened = true;
        pos = 0;
        eofReached = false;
    }

    void Close() {
        if (file.is_open()) file.close();
        opened = false;
    }
};

#endif // FILEREADONLYSTREAM_H
