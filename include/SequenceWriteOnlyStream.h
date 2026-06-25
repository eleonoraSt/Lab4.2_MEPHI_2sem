#ifndef SEQUENCEWRITEONLYSTREAM_H
#define SEQUENCEWRITEONLYSTREAM_H

#include "WriteOnlyStream.h"
#include "Sequence.h"
#include "ListSequence.h"  // тут аппенды удобнее
#include "errors.h"

template <class T> class SequenceWriteOnlyStream: public WriteOnlyStream<T> {
private:
    Sequence<T>* seq;
    size_t pos;
    bool opened;
public:
    SequenceWriteOnlyStream(const Sequence<T>* sequence) {
        seq = sequence;
        pos = 0;
        opened = true;
    }

    ~SequenceWriteOnlyStream() {
        Close();
    }

    size_t GetPosition() const {
        return pos;
    }

    size_t Write(T item) {
        if (!opened) throw STREAM_NOT_OPEN;
        seq->Append(item);
        pos++;
        return pos;
    }

    void Open() {
        if (opened) throw STREAM_NOT_CLOSED;
        seq = new ListSequence<T>();
        pos = 0;
        opened = true;
    }

    void Close() {
        delete seq;
        opened = false;
    }
};

#endif // SEQUENCEWRITEONLYSTREAM_H
