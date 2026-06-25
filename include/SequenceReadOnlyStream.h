#ifndef SEQUENCEREADONLYSTREAM_H
#define SEQUENCEREADONLYSTREAM_H

#include "ReadOnlyStream.h"
#include "Sequence.h"
#include "errors.h"

template <class T> class SequenceReadOnlyStream: public ReadOnlyStream<T> {
private:
    Sequence<T>* seq;
    size_t pos;
    bool opened;
public:
    SequenceReadOnlyStream(Sequence<T>* sequence) {
        seq = sequence;
        pos = 0;
        opened = true;
    }

    ~SequenceReadOnlyStream() {
        Close();
    }

    bool IsEndOfStream() {
        return pos >= static_cast<size_t>(seq->GetLength());
    }

    T Read() {
        if (!opened) throw STREAM_NOT_OPEN;
        if (IsEndOfStream()) throw END_OF_STREAM;
        return seq->Get(pos++);
    }

    size_t GetPosition() const {
        return pos;
    }

    bool IsCanSeek() const {
        return true;
    }

    size_t Seek(size_t index) {
        if (!opened) throw STREAM_NOT_OPEN;
        size_t length = static_cast<size_t>(seq->GetLength());
        if (index > length) index = length;
        pos = index;
        return pos;
    }

    bool IsCanGoBack() const {
        return true;
    }

    void Open() {
        opened = true;
        pos = 0;
    }

    void Close() {
        opened = false;
    }
};

#endif // SEQUENCEREADONLYSTREAM_H
