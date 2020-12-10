#include "vector.h"
#include <iostream>
#include <cassert>

//Implementation Details of Float Vector 'Vectorf<N>' objects.

template<size_t N>
Vectorf<N>::Vectorf() {

}

template<size_t N>
Vectorf<N>::Vectorf(std::initializer_list<float>) {

}

template<size_t N>
Vectorf<N> Vectorf<N>::operator+(Vectorf<N> V) {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::operator-(Vectorf<N> V) {
    return Vectorf<N>();
}

template<size_t N>
float Vectorf<N>::operator*(Vectorf<N> V) {
    return 0;
}

template<size_t N>
Vectorf<N> Vectorf<N>::operator^(Vectorf<N> V) {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> operator*(float c, Vectorf<N> V) {
    return Vectorf<N>();
}

template<size_t N>
std::ostream &operator<<(std::ostream &o, Vectorf<N> V) {

}

template<size_t N>
Vectorf<N> Vectorf<N>::normalize() {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::rotate() {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::gRotate() {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::reflect() {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::gReflect() {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::oProject() {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::sProject() {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::pProject() {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::AffineCSum(int n, float *C, Vectorf<N> *Q) {
    return Vectorf<N>();
}

template<size_t N>
Vectorf<N> Vectorf<N>::AffineDsum(int n, float *d, Vectorf<N> *Q) {
    return Vectorf<N>();
}
