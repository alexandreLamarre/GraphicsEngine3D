#include "matrix.h"
#include <iostream>
#include <stddef.h>
//================= Matrixf:  Float square Matrix methods =======================
/**
 * Default Square matrix initializer. Initializes a matrix to the identity.
 * @tparam N dimension of the square matrix
 */
template<size_t N>
Matrixf<N>::Matrixf() {
    size = N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i == j) {elems.push_back(1.0);}
            else {elems.push_back(0.0);}
        }
    }
}


/**
 * Initialize a square matrix from an initializer list of floats.
 * Fills up the matrix by cols (by the convention we define).
 * Pads the matrix with zeroes as necessary. Truncates initializer
 * list as necessary.
 * @tparam N
 * @param elements the elements of the matrix
 */
template<size_t N>
Matrixf<N>::Matrixf(std::initializer_list<float> elements) {
    size = N;

    for(auto &el: elements){
        elems.push_back(el);
        if(elems.size() >= N*N){break;}
    }

    for(int i = 0; i < elems.size() - N*N; i++){
        elems.push_back(0);
    };

}

/**
 * Initialize a square matrix from a nested intializer list of floats.
 * In this way each nested list represents the column vectors of the matrix, in order.
 * Pads (with zeroes) and truncates each column vector as necessary
 * @tparam N size of square matrix
 * @param elements the nested initializer list of elements in the matrix
 */
template<size_t N>
Matrixf<N>::Matrixf(std::initializer_list<std::initializer_list<float>> elements) {
    size = N;
    for(auto el_list: elements){
        for(auto el: el_list){
            elems.push_back(el);
            if(elems.size()%N == 0){break;}
        }

        if(elems.size()%N != 0){
            for(int i = 0; i < N - elems.size()%N; i++){
                elems.push_back(0);
            }
        }
    }
};


/**
 * Returns a std::vector containing the row with given index
 * @tparam N size
 * @param index index(0-indexed) of the row we want
 * @return a copy of the matrix row at given index
 */
template<size_t N>
std::vector<float> Matrixf<N>::row(int index) {
    if(index < 0 || index >= N){
        std::cout << "Warning: Invalid row accessed";
    }
    std::vector<float> row;
    for(int i = 0; i < N; i++){
        row.push_back(elems[i*N+index]);
    }
    return row;
}

/**
 * Returns a std::vector containing the column with given index
 * @tparam N size
 * @param index index(0-indexed) of the column we want
 * @return a copy of the matrix column at given index
 */
template<size_t N>
std::vector<float> Matrixf<N>::col(int index) {
    if(index < 0 || index >= N){
        std::cout<<"Warning: Invalid column accessed";
    }
    std::vector<float> col = std::vector<float>(elems.begin()+N*index, elems.begin()+(N+1)*index);
    return col;
}

/**
 * Standard matrix algebra addition
 * @tparam N Dimension of square matrix
 * @param M the Square Matrix to add
 * @return The Square Matrix obtained from the matrix addition
 */
template<size_t N>
Matrixf<N> Matrixf<N>::operator+(Matrixf<N> M) const {
    std::vector<float> new_elems;
    for(int i = 0; i < N*N; i++){
        new_elems.push_back(elems[i] + M.elems[i]);
    }
    Matrixf<N> add_matrix = {new_elems};
    return add_matrix;
}

/**
 * Standard matrix algebra subtraction
 * @tparam N Dimension of square matrix
 * @param M The Square Matrix to subtract
 * @return The Square Matrix obtained from matrix subtraction
 */
template<size_t N>
Matrixf<N> Matrixf<N>::operator-(Matrixf<N> M) const {
    std::vector<float> new_elems;
    for(int i = 0; i < N*N; i++){
        new_elems.push_back(elems[i] - M.elems[i]);
    }
    Matrixf<N> sub_matrix = {new_elems};
    return sub_matrix;
}


/**
 * Standard matrix algebra scalar multiplication
 * @tparam N Size of square matrix
 * @param c scalar
 * @param M The matrix to multiply
 * @return The square matrix obtained from scalar multiplication
 */
template<size_t N>
Matrixf<N> operator*(float c, Matrixf<N> M) {
    std::vector<float> new_elems;
    for(int i = 0; i < N*N; i++){
        new_elems.push_back(c*M.elems[i]);
    }
    Matrixf<N> scal_matrix = {new_elems};
    return scal_matrix;
}

/**
 * Standard matrix algebra multiplication.
 * Elements are added by column to construct matrices, so matrix multiplication
 * algorithm multiplies by rows then cols, instead of the (standard other way around)
 * @tparam N dimension of the square matrix
 * @param M the matrix to multiply with
 * @return Square Matrix obtained from matrix multiplication
 */
template<size_t N>
Matrixf<N> operator*(Matrixf<N> M, Matrixf<N> K) {
    std::vector<float> new_elems;
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j++){

            new_elems.push_back(M.dotProduct(M.get_row(j), K.get_col(i)));
        }
    }
    Matrixf<N> m_matrix = {new_elems};
    return m_matrix;
}


/**
 * Standard Matrix algebra exponentiation.
 * Supports both negative, zero and positive exponents.
 * Negative powers can only be computed for invertible powers.
 * By convention, matrix^0 will yield the identity matrix of dim N.
 * @tparam N Size of Square matrix
 * @param power the exponent of the operation
 * @return The Square matrix obtained from the exponentiation
 */
template<size_t N>
Matrixf<N> Matrixf<N>::operator^(int power) {
     if(power == 0){
        return Matrixf<N>(); //the identity matrix of dim N
     }
     if(power < 0){
        //invert the matrix if possible the apply successive mult.
     }
     if(power > 0){

     }
}

/**
 * Static dot Product method, helper function for Matrix multiplication
 * @tparam N Dimension of the Square Matrix
 * @param row first vector in the dot product
 * @param col second vector in the dot product
 * @return float result of the dot product of the two given vectors
 */
template<size_t N>
float Matrixf<N>::dotProduct(const std::vector<float> row, const std::vector<float> col) {
    if(row.size() != col.size()){
        std::cout << "Warning--Mismatched size: vector arguments for dotProduct";
    }
    float res = 0;
    for(int i = 0; i < row.size(); i++){
        res += row[i]*col[i];
    }
    return res;
}

template<size_t N>
Matrixf<N> Matrixf<N>::invert() {
    return Matrixf<N>();
}

template<size_t N>
Matrixf<N> Matrixf<N>::det() {
    return Matrixf<N>();
}






//NMatrixf: Float nxm Matrix methods



//General Square Matrix methods
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
Vector Matrix<T, N>::rowVector() {

}

template<typename T, size_t N>
Vector Matrix<T, N>::rowColumn() {

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

