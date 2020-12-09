#ifndef GRAPHICSENGINE3D_MATRIX_H
#define GRAPHICSENGINE3D_MATRIX_H

#endif //GRAPHICSENGINE3D_MATRIX_H

#include <stddef.h>
#include <vector>
#include "vector.h"

/**
 * Square matrix class that stores elements of type T
 * @tparam T the elements in the matrix
 * @tparam N the dimension of the square matrix
 */
template<typename T, size_t N>
class Matrix{
public:
    Matrix(std::initializer_list<T> elems, size_t dim);
    std::vector<T> row();
    std::vector<T> col();
    Vector rowVector(); // rows must be 3D float tuple only
    Vector rowColumn(); //cols must be 3D float tuple only
    Matrix<T,N> operator+(Matrix<T,N>) const;
    Matrix<T,N> operator-(Matrix<T,N>) const;
    Matrix<T,N> operator*(float c) const;
    friend Matrix<T,N> operator*(Matrix<T,N> M, Vector V);
private:
    size_t size;
    std::vector<T> elems;

//    template<typename U> Matrix(const Matrix_ref<U,N>&);
};

