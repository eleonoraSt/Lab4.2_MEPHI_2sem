TEMPLATE = app
TARGET = name_of_the_app

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    include/ArraySequence.h \
    include/BinaryHeap.h \
    include/DynamicArray.h \
    include/FileReadOnlyStream.h \
    include/FileWriteOnlyStream.h \
    include/LinkedList.h \
    include/ListSequence.h \
    include/Node.h \
    include/ReadOnlyStream.h \
    include/Sequence.h \
    include/SequenceReadOnlyStream.h \
    include/SequenceWriteOnlyStream.h \
    include/Window.h \
    include/WriteOnlyStream.h \
    include/errors.h \
    include/serializing.h \
    tests/testAll.h \
    tests/testSequence.h

SOURCES += \
    src/Window.cpp \
    src/main.cpp \
    src/serializing.cpp \
    tests/testAll.cpp \
    tests/testSequence.cpp
