#ifndef ERRORS_H
#define ERRORS_H

enum ErrorCode {
    OK = 0,
    INDEX_ERROR = 1,
    NEGATIVE_SIZE = 2,
    STREAM_NOT_OPEN = 3,
    STREAM_NOT_CLOSED = 4,
    END_OF_STREAM = 5,
    READING_ERROR = 6,
    WRITING_ERROR = 7,
    SEEK_NOT_SUPPORTED = 8,
};

#endif  // ERRORS_H
