#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

#define CAPACITY_ADD 10  // То есть шаг увеличения capacity равен этому

template <class T> class ArraySequence: public Sequence<T> {
private:
    DynamicArray<T>* seq;
    size_t size;  // capacity - это seq->GetSize()
public:
    ArraySequence(const T* items, size_t count) {
        seq = new DynamicArray<T>(items, count);
        size = count;
    }

    ArraySequence() {
        seq = new DynamicArray<T>(CAPACITY_ADD);  // явно же сейчас добавлять будут
        size = 0;
    }

    ArraySequence(const DynamicArray<T> &dynamicArray) {
        seq = new DynamicArray<T>(dynamicArray);
        size = dynamicArray.size;
    }

    ArraySequence(const ArraySequence<T> &other) {
        seq = new DynamicArray<T>(*other.seq);
        size = other.size;
    }

    ~ArraySequence() override {
        delete seq;
    }

    T GetFirst() const override {
        if (size == 0) throw INDEX_ERROR;
        return seq->Get(0);
    }

    T GetLast() const override {
        if (size == 0) throw INDEX_ERROR;
        return seq->Get(GetLength() - 1);
    }

    T Get(size_t index) const override {
        if (index >= GetLength()) throw INDEX_ERROR;
        return seq->Get(index);
    }

    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override {
        if (endIndex > GetLength() || endIndex < startIndex) throw INDEX_ERROR;
        ArraySequence<T>* subseq = new ArraySequence<T>();
        subseq->seq->Resize(endIndex - startIndex + 1);
        for (size_t index = startIndex; index <= endIndex; index++) {
            subseq->seq->Set(index - startIndex, seq->Get(index));
        }
        subseq->size = endIndex - startIndex + 1;
        return (Sequence<T>*)subseq;
    }

    size_t GetLength() const override {
        return size;
    }

    Sequence<T>* Append(T item) override {
        if (seq->GetSize() == size) {
            seq->Resize(size + CAPACITY_ADD);
        }
        seq->Set(size, item);
        size++;
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        if (seq->GetSize() == size) {
            seq->Resize(size + CAPACITY_ADD);
        }
        for (size_t index = size; index > 0; index--) {
            seq->Set(index, seq->Get(index - 1));
        }
        seq->Set(0, item);
        size++;
        return this;
    }

    Sequence<T>* InsertAt(T item, size_t index) override {
        if (index > size) throw INDEX_ERROR;
        if (seq->GetSize() == size) {
            seq->Resize(size + CAPACITY_ADD);
        }
        for (size_t current = size; current >= index; current--) {
            seq->Set(current, seq->Get(current - 1));
        }
        seq->Set(index, item);
        size++;
        return this;
    }

    Sequence<T>* Concat(Sequence<T>* list) override {
        size_t otherSize = list->GetLength();
        seq->Resize(GetLength() + otherSize);
        for (size_t index = 0; index < otherSize; index++) {
            seq->Set(size + index, list->Get(index));
        }
        size += otherSize;
        return this;
    }

    Sequence<T>* Map(T (*func)(T)) const override {
        ArraySequence<T>* mapped = new ArraySequence<T>();
        mapped->seq->Resize(GetLength());
        for (size_t index = 0; index < GetLength(); index++) {
            mapped->seq->Set(index, func(seq->Get(index)));
        }
        mapped->size = GetLength();
        return (Sequence<T>*)mapped;
    }

    Sequence<T>* Where(bool (*func)(T)) const override {
        ArraySequence<T>* filtered = new ArraySequence<T>();
        T item;
        for (size_t index = 0; index < GetLength(); index++) {
            item = seq->Get(index);
            if (func(item)) filtered->Append(item);
        }
        return (Sequence<T>*)filtered;
    }

    T Reduce(T (*func)(T, T), T initial) const override {
        T result = initial;
        for (size_t index = 0; index < GetLength(); index++) {
            result = func(seq->Get(index), result);
        }
        return result;
    }

    ArraySequence<T> operator=(const Sequence<T> &other) {
        if (seq && this != &other) delete seq;
        seq = new DynamicArray<T>(other.GetLength());
        size = other.GetLength();
        for (size_t index = 0; index < size; index++) {
            seq->Set(index, other.Get(index));
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

#endif  // ARRAY_SEQUENCE_H
