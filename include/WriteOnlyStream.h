#ifndef WRITEONLYSTREAM_H
#define WRITEONLYSTREAM_H

#include <cstdlib>  // size_t

template <class T> class WriteOnlyStream {
    virtual ~WriteOnlyStream() {}

    virtual size_t GetPosition() const = 0;

    virtual size_t Write(T item) = 0;
    virtual void Open() = 0;
    virtual void Close() = 0;
};

#endif // WRITEONLYSTREAM_H
