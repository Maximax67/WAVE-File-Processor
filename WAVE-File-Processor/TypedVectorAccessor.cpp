#include "TypedVectorAccessor.h"

template <typename T>
TypedVectorAccessor<T>::TypedVectorAccessor(const std::vector<char>& d) : data(d) {};

template <typename T>
const T& TypedVectorAccessor<T>::operator[](const size_t index) const {
    union {
        const char* charPtr;
        const T* typePtr;
    } converter;
    converter.charPtr = data.data() + (index * sizeof(T));
    return *converter.typePtr;
}

template <typename T>
size_t TypedVectorAccessor<T>::size() const {
    return data.size() / sizeof(T);
}

template <typename T>
const std::vector<char>& TypedVectorAccessor<T>::getData() const {
    return data;
}

template class TypedVectorAccessor<int16_t>;
template class TypedVectorAccessor<uint8_t>;
