#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <class T> class ListSequence: public Sequence<T> {
private:
    LinkedList<T>* seq;
    size_t length;
public:
    ListSequence(const T* items, size_t count) {
        seq = new LinkedList<T>(items, count);
        length = count;
    }

    ListSequence() {
        seq = new LinkedList<T>();
        length = 0;
    }

    ListSequence(const LinkedList<T> &linkedList) {
        seq = new LinkedList<T>(linkedList);
        length = linkedList.GetLength();
    }

    ListSequence(const ListSequence<T> &other) {
        seq = new LinkedList<T>(*other.seq);
        length = other.length;
    }

    ~ListSequence() override {
        delete seq;
    }

    T GetFirst() const override {
        return seq->GetFirst();
    }

    T GetLast() const override {
        return seq->GetLast();
    }

    T Get(size_t index) const override {
        if (index >= length) throw INDEX_ERROR;
        return seq->Get(index);
    }

    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override {
        if (endIndex >= length) throw INDEX_ERROR;
        ListSequence<T>* subseq = new ListSequence<T>();
        subseq->seq = seq->GetSubList(startIndex, endIndex);
        subseq->length = endIndex - startIndex + 1;
        return (Sequence<T>*)subseq;
    }

    size_t GetLength() const override {
        return length;
    }

    Sequence<T>* Append(T item) override {
        seq->Append(item);
        length++;
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        seq->Prepend(item);
        length++;
        return this;
    }

    Sequence<T>* InsertAt(T item, size_t index) override {
        if (index > length) throw INDEX_ERROR;
        seq->InsertAt(item, index);
        length++;
        return this;
    }

    Sequence<T>* Concat(Sequence<T>* list) override {
        size_t otherLength = list->GetLength();
        for (size_t index = 0; index < otherLength; index++) {
            seq->Append(list->Get(index));
        }
        length += otherLength;
        return this;
    }

    Sequence<T>* Map(T (*func)(T)) const override {
        ListSequence<T>* mapped = new ListSequence<T>();
        for (size_t index = 0; index < length; index++) {
            mapped->Append(func(seq->Get(index)));
        }
        return (Sequence<T>*)mapped;
    }

    Sequence<T>* Where(bool (*func)(T)) const override {
        ListSequence<T>* filtered = new ListSequence<T>();
        T item;
        for (size_t index = 0; index < length; index++) {
            item = seq->Get(index);
            if (func(item)) filtered->Append(item);
        }
        return (Sequence<T>*)filtered;
    }

    T Reduce(T (*func)(T, T), T initial) const override {
        T result = initial;
        for (size_t index = 0; index < length; index++) {
            result = func(seq->Get(index), result);
        }
        return result;
    }

    ListSequence<T> operator=(const Sequence<T> &other) {
        if (seq && this != &other) delete seq;
        seq = new LinkedList<T>();
        size_t size = other.GetLength();
        for (size_t index = 0; index < size; index++) {
            Append(other.Get(index));
        }
        return *this;
    }

    bool operator==(const Sequence<T> &other) {
        bool equal = GetLength() == other.GetLength();
        for (size_t index = 0; index < GetLength() && equal; index++) {
            equal = Get(index) == other.Get(index);
        }
        return equal;
    }
};

#endif // LIST_SEQUENCE_H
