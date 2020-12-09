#ifndef GRAPHICSENGINE3D_MATRIX_H
#define GRAPHICSENGINE3D_MATRIX_H

#endif //GRAPHICSENGINE3D_MATRIX_H

#include <stddef.h>
#include <vector>
template<typename T, size_t N>
class Matrix{
public:
    static constexpr size_t order = N;
    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    Matrix()=default;
    Matrix(Matrix&&) = default;
    Matrix& operator=(Matrix&&)= default;
    Matrix(const Matrix&) = default;
    Matrix& operator=(const Matrix&) = default;
    ~Matrix()=default;

//    template<typename U> Matrix(const Matrix_ref<U,N>&);
};