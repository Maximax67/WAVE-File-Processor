#pragma once

#include <vector>

template <typename T>
class TypedVectorAccessor {
private:
    const std::vector<char>& data;
public:
    TypedVectorAccessor(const std::vector<char>&);
    const T& operator[](const size_t index) const;
    size_t size() const;
    const std::vector<char>& getData() const;
};
