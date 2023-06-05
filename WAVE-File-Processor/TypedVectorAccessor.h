#pragma once

#include <vector>

template <typename T>
class TypedVectorAccessor {
private:
    const std::vector<char>& data;
public:
    TypedVectorAccessor(const std::vector<char>&);
    const std::vector<char>& getData() const;
    size_t size() const;
    const T& operator[](const size_t index) const;
};
