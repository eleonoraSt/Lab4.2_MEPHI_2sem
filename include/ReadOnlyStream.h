#ifndef READONLYSTREAM_H
#define READONLYSTREAM_H

#include <cstdlib>  // size_t

template <class T> class ReadOnlyStream {
public:
    virtual ~ReadOnlyStream() {}

    virtual bool IsEndOfStream() = 0;
    virtual T Read() = 0;
    virtual size_t GetPosition() const = 0;
    virtual bool IsCanSeek() const = 0;
    virtual size_t Seek(size_t index) = 0;
    virtual bool IsCanGoBack() const = 0;

    virtual void Open() = 0;
    virtual void Close() = 0;
};

#endif // READONLYSTREAM_H
