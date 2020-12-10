#include "vector.h"
#include <iostream>
#include <math.h>

//Implementation Details of Float Vector 'Vectorf<N>' objects.

/**
 * Default intialization of N-dimensional Vector of floats.
 * Initalized to zero vector, with default 0 collision.
 * @tparam N dimension of the vector
 */
template<size_t N>
Vectorf<N>::Vectorf() {
    float new_pos[N];
    for(int i = 0; i < N; i++){
        new_pos[i] = 0;
    }
    pos = new_pos;
    e = 0;
}

/**
 * Initializer of an N-dimensional Vector of floats
 * where positions and collisions are at least partially specified
 * Instatiation is padded with zeroes and truncated as necessary.
 * @tparam N vector dimension
 * @param input initializer list of floats representing position, then collision parameter
 */
template<size_t N>
Vectorf<N>::Vectorf(std::initializer_list<float> input) {
    float new_pos[N];
    int cur_index = 0;
    for(auto coord: input){
        if(cur_index < N)new_pos[cur_index] = coord;
        else{ e = coord;}
        cur_index++;
        if(cur_index == N) break;
    }

    for(int i = 0; i < N-cur_index; i++){
        new_pos[i] = 0.0; // if not enough positions are specified set to 0
    }
    //if not enough parameters are specified, set collision to 0
    if(cur_index <= N+1){
        e = 0;
    }
    pos = new_pos;
}

/**
 * Standard n-dimensional vector addition
 * @tparam N dimension of the vectors to add
 * @param V the vector to add
 * @return the vector obtained from vector addition with V
 */
template<size_t N>
Vectorf<N> Vectorf<N>::operator+(Vectorf<N> V) {
    float new_pos[N];
    for(int i = 0; i < N; i++){
        new_pos[i] = pos[i]+V.pos[i];
    }
    return Vectorf<N>{*new_pos};
}

/**
 * Standard n-dimensional vector subtraction
 * @tparam N dimension of the vectors to subtract
 * @param V the vector to subtract
 * @return the vector obtained from vector subtraction with V
 */
template<size_t N>
Vectorf<N> Vectorf<N>::operator-(Vectorf<N> V) {
    float new_pos[N];
    for(int i = 0; i < N; i++){
        new_pos[i] = pos[i] - V.pos[i];
    }
    return Vectorf<N>{*new_pos};
}

/**
 * Standard n-dimensional dot product of vectors
 * @tparam N dimension of vectors
 * @param V the vector to dotproduct with
 * @return the float representing the dot product of the two vectors
 */
template<size_t N>
float Vectorf<N>::operator*(Vectorf<N> V) {
    int sum = 0;
    for(int i = 0; i < N; i++){
        sum+= pos[i]*V.pos[i];
    }
}
/**
 * Standard n-dimensional cross product of vectors.
 * In practice should never be used for N>3 and will produce a warning
 * instead of the computation.
 * @tparam N dimension of vectors
 * @param V the vector to cross product with
 * @return the vector resulting from the cross product with V
 */
template<size_t N>
Vectorf<N> Vectorf<N>::operator^(Vectorf<N> V) {
    if(N > 3){
        std::cout << "Warning: cross product called on vector of dim > 3"
        << "returning original vector.";
        return this;
    }
    if(N== 1){
        return Vectorf<1>{pos[0]*V.pos[1]}; //return dot product
    }
    if(N == 2){
        return Vectorf<1>{pos[0]*V.pos[1] - pos[1]*V.pos[0]};
    }
    if(N==3){
        float new_pos[N];
        new_pos[0] = pos[1]*V.pos[2] - pos[2]*V.pos[1];
        new_pos[1] = pos[0]*V.pos[2] - pos[2]*V.pos[0];
        new_pos[2] = pos[0]*V.pos[1] - pos[1]*V.pos[0];
        return Vectorf<N>{*new_pos};
    }
}
/**
 * Calculate norm of n-dimensional float vector
 * @tparam N dimension of vector
 * @return the norm of the vector
 */
template<size_t N>
float Vectorf<N>::norm(){
   return sqrt(norm2());
}

/**
 * Calculate norm squared of n-dimensional float vector.
 * Saves math.sqrt() method time complexity. Should be prefered when possible.
 * @tparam N dimension of vector
 * @return the squared norm of the vector
 */
template<size_t N>
float Vectorf<N>::norm2(){
    float val = 0;
    for(int i = 0; i < N; i++){ val += pow(pos[i],2);}
    return val;
}

/**
 * Standard vector scalar multiplication
 * @tparam N dimension of the vector
 * @param c the scalar to use
 * @param V the vector to multiply
 * @return the vector resulting from scalar multiplication with c
 */
template<size_t N>
Vectorf<N> operator*(float c, Vectorf<N> V) {
    float new_pos[N];
    for(int i = 0; i < N; i++){
        new_pos[i] = c* V.pos[i];
    }
    return Vectorf<N>{*new_pos, V.e}; //TODO: depending on future implementation c*e
}

/**
 * True iff Vector is betweem origin 0 and other vector
 * @tparam N dimension of vectors
 * @param V other vector
 * @return our vector is between origin 0 and other vector
 */
template<size_t N>
bool Vectorf<N>::operator<(Vectorf<N> V){
    for(int i = 0; i < N; i++){
        if(!(sgn(pos[i]) == sgn(V.pos[i]) && abs(pos[i]) < abs(V.pos[i]))) return false;
    }
    return true;
}

/**
 * True iff norm of the vector is smaller than the provided norm
 * @tparam N dimension of the vector
 * @param dist the norm vector is compared to
 * @return whether the vectors norm is smaller than dist
 */
template<size_t N>
bool Vectorf<N>::operator<(float dist){
    return norm2() < pow(dist,2);
}

/**
 * std::cout representation of an n-dimesional vector
 * @tparam N dimension of the vector
 * @param o std::cout stream
 * @param V the Vectpr
 * @return string representation in std::cout of Vector
 */
template<size_t N>
std::ostream &operator<<(std::ostream &os, Vectorf<N> V) {
    os << "Position : ";
    for(int i = 0; i < N; i ++){
        os << pos[i]<<" , ";
    }
    os << "Collision : " << e;
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

template<size_t N>
Vectorf<N> extend(Vectorf<N> V, size_t dim) {
    return Vectorf<N + dim-N>{*V.pos};
}


