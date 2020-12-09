#include "matrix.h"
#include <iostream>

template<typename T, size_t N>
Matrix<T, N>::Matrix(std::initializer_list<T> objs, size_t dim) {
    elems = objs;
    size = dim;
}

template<typename T, size_t N>
std::vector<T> Matrix<T, N>::row() {

}

template<typename T, size_t N>
std::vector<T> Matrix<T, N>::col() {

}

template<typename T, size_t N>
Matrix<T, N> Matrix<T, N>::operator+(Matrix<T, N>) const {

}

template<typename T, size_t N>
Matrix<T, N> Matrix<T, N>::operator-(Matrix<T, N>) const {

}

template<typename T, size_t N>
Matrix<T, N> Matrix<T, N>::operator*(float c) const {

}
template<typename T, size_t N>
Matrix<T, N> operator*(Matrix<T, N> M, Vector V) {

}
