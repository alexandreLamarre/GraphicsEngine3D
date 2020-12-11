#include "matrix.h"
#include <iostream>
#include <stddef.h>
#include <math.h>

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
        if(elems.size() >= N*N){break;} //truncate additional elements
    }
    // pad with zeroes as necessary
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
            if(elems.size()%N == 0){break;} //truncate extra elements
        }
        //pad with zeroes as necessary
        if(elems.size()%N != 0){
            for(int i = 0; i < N - elems.size()%N; i++){
                elems.push_back(0);
            }
        }
        if(elems.size() == N*N) break; // truncate extra columns
    }
    //pads with zeroes if not enough columns are specified
    for(int i = 0; i < N*N - elems.size(); i++){
        elems.push_back(0.0);
    }
};

/**
 * Constructor the builds unit transformation matrices
 * based on the x,y,z axes labeled as i,j,k by convention in linear algebra.
 * @tparam N
 * @param special_matrix char identifier for a special matrix 'i', 'j' or 'k'
 */
template<size_t N>
Matrixf<N>::Matrixf(std::string &special_matrix){
    size = N;
    for(int i = 0 ; i < N; i++){
        elems.push_back(0.0);
    }
    if(special_matrix == "i") elems[0] = 1.0;
    if(special_matrix == "j" && N>= 2) elems[N+1] = 1.0;
    if(special_matrix == "k" && N>=3 ) elems[2*N+2] = 1.0;

}

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

template<size_t N>
Vectorf<N> operator*(Matrixf<N> T, Vectorf<N> V){
    float new_pos[N];
    for(int i = 0; i < N; i++){
        Vectorf<N> Ti{T.row(i)};
        new_pos[i] = Ti*V;
    }
    return Vectorf<N>{*new_pos};
}

template<size_t N>
Vectorf<N> operator*(Vectorf<N> V, Matrixf<N> M){
    float new_pos[N];
    for(int i = 0; i < N; i++){
        Vectorf<N> Mi{M.col(i)};
        new_pos[i] = V*Mi;
    }
    return Vectorf<N>{*new_pos};
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

     Matrixf<N> new_matrix = this;
     if(power < 0) new_matrix = this->invert();

     for(int i = 1; i < abs(power); i++){new_matrix = new_matrix*new_matrix;}
     return new_matrix;

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

/**
 * Invert the square matrix if possible, otherwise return itself
 * @tparam N dimension of the square matrix
 * @return the inverted matrix, if possible
 */
template<size_t N>
Matrixf<N> Matrixf<N>::invert() {
    float res_det = this->det();
    if(res_det == 0) return this; //non-invertible, return self
    float adjoint[N][N] = adj(this);

    std::vector<float> inv_elems;
    for(int col = 0; col < N; col++){
        for(int row = 0; row < N; row++){
            inv_elems.push_back(adjoint[row][col]/res_det);
        }
    }
    return Matrixf<N>{inv_elems};

}

/**
 * The determinant of a square matrix.
 * Converts Matrixf object to 2D array to be called by helper methods.
 * @tparam N Dimension of the square matrix
 * @param M The matrix whose determinant we want to find.
 * @return determinant of matrix M
 */
template<size_t N>
float det(Matrixf<N> M) {
    float submatrix[N][N];
    //constructing reusable 2-D float array
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            submatrix[row][col] = M[row][col];
        }
    }
    return M.det(submatrix, M.size);
}

/**
 * Determinant helper function, uses 2D array of floats to compute
 * cofactors & determinants
 * @tparam N dimension of the square matrix
 * @param M the 2D array representing the matrix M
 * @param cur_size dimension of submatrix when recursively calculating det
 * @return determinant of M
 */
template<size_t N>
float det(float matrix[N][N], size_t cur_size) {
    float det = 0;
    float submatrix[N][N];
    if(cur_size == 1) return matrix[0][0]; // should only happen if N = 1 from the start
    if(cur_size == 2) return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    else{
        for(int x = 0; x < cur_size; x++){
            int subi = 0;
            for(int i = 0; i < cur_size; i++){
                int subj = 0;
                for(int j = 0; j < cur_size; j++){
                    if(j == x) continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
            }
            det = det + (pow(-1,x))*matrix[0][x]* det(submatrix, cur_size-1);
        }
    }
    return det;
}

/**
 * Access row at given index
 * @tparam N dimension of square matrix
 * @param index the index of the row
 * @return  row vector at given index
 */
template<size_t N>
std::vector<float> Matrixf<N>::operator[](int index) {
    return this->row(index);
}


/**
 * Public method for determining the adjoint of a matrix.
 * Returns a 2D array representing the matrix, for use in invert()
 * matrixf method.
 * @tparam N dimension of the square matrix
 * @param M the matrix whose adjoint we want to find
 */
template<size_t N>
void adj(Matrixf<N> M){
    float submatrix[N][N];
    //constructing reusable 2-D float array
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            submatrix[row][col] = M[row][col];
        }
    }
    float adj[N][N];
    adj(submatrix, adj); // copy adjoint matrix to 2d array data
    return adj;

}


/**
 * Adjoint helper functiion that takes 2D array representation
 * of a matrixf object. Copies adjoint matrix entries to a 2D array.
 * @tparam N dimension of the square matrix
 * @param matrix the matrix whose adjoint we want to find
 * @param ADJ 2D array whose memory is allocated for use to copy adjoint data into
 */
template<size_t N>
void adj(float matrix[N][N], float ADJ[N][N]) {
    if(N == 1) {ADJ[0][0] = 1; return;}
    int s = 1;
    float t[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            getCofactor(matrix,t,i,j,N);
            s = (i+j)%2 == 0? 1: -1;
            ADJ[j][i] = s* det(t, N-1);
        }
    }
}

/**
 * Helper function to calculate the cofactor of a given entry of a matrix.
 * @tparam N dimension of the square matrix
 * @param matrix the2d array representation of a matrix
 *          whose cofactor entries we want to find
 * @param temp 2d array used to store cofactor calculations
 * @param p index to row we just removed in cofactor expansion
 * @param q index to col we just removed in cofactor expansion
 * @param n submatrix size at given iteration
 */
template<size_t N>
void getCofactor(float matrix[N][N], float temp[N][N], int p, int q, int n){
    int i =0; int j = 0;
    for(int r = 0; r < n; r++){
        for(int c = 0; c <n; c++){
            if(r!= p && c!=q){
                temp[i][j++] = matrix[r][c];
                if(j == n-1){
                    j = 0; i++;
                }
            }
        }
    }
}



//================NMatrixf: Float nxm general Matrix methods=====================

/**
 * Default simple initializer for a zero nxm general matrix.
 * Issues warnings if you construct a square matrix using this data type.
 * @tparam n num rows
 * @tparam m num cols
 */
template<size_t n, size_t m>
NMatrixf<n, m>::NMatrixf() {
    if(n == m){
        std::cout << "Warning: square matrix intialize as general matrix, expected"
                  << "square matrix methods will not be available";
    }
    num_rows = n;
    num_cols = m;
    for(int i = 0; i < n*m; i++){
        elems.push_back(0.0);
    }
}

/**
 * Initializer for General(non-square) matrix using an intializer list.
 * The list fills the columns of the matrix (by the convention we define).
 * Pads with zeroes and truncates input as necessary.
 * Position vectors in these matrices will always be columns.
 * A warning will be generated if n == m, letting users know that a
 * square matrix instatiated as a general matrix will not have access to
 * square matrix methods.
 * @tparam n num rows of matrix
 * @tparam m num cols of matrix
 */
template<size_t n, size_t m>
NMatrixf<n, m>::NMatrixf(std::initializer_list<float> input) {
    if(n == m){
        std::cout << "Warning: square matrix intialize as general matrix, expected"
                     << "square matrix methods will not be available";
    }
    num_rows = n;
    num_cols = m;
    for(auto el: input){
        elems.push_back(el);
        if(elems.size() == n*m) break; //truncate additional elements
    }
    //pad with zeroes as necessary
    for(int i = 0; i < n*m - elems.size(); i++){
        elems.push_back(0.0);
    }
}

/**
 * Initializer for general(non-square) matrix using a nested initializer list.
 * The nested lists represent the columns of the matrix.
 * Pads with zeroes and truncates each column based on input as necessary,.
 * @tparam n num rows of matrix
 * @tparam m num cols of matrix
 * @param input the 2D initializer list specifying the columns of the matrix in order
 */
template<size_t n, size_t m>
NMatrixf<n, m>::NMatrixf(std::initializer_list<std::initializer_list<float>> input) {
    if(n == m){
        std::cout << "Warning: square matrix intialize as general matrix, expected"
                  << "square matrix methods will not be available";
    }
    num_rows = n;
    num_cols = m;
    for(auto col: input){
        for(auto el: col){
            elems.push_back(el);
            if(elems.size()%m == 0) break; //truncate additional elements
        }
        //pad with zeroes as necessary
        for(int i = 0; i < m - elems.size()%m; i++){
            elems.push_back(0.0);
        }
        if(elems.size() == n*m) break; // truncate extra columns
    }
    //pads with zeroes if not enough columns are specified
    for(int i = 0; i < n*m - elems.size(); i++){
        elems.push_back(0.0);
    }
}



// ================= General Square Matrix methods ========================
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

//template<typename T, size_t N>
//Vector Matrix<T, N>::rowVector() {
//
//}
//
//template<typename T, size_t N>
//Vector Matrix<T, N>::rowColumn() {
//
//}


template<typename T, size_t N>
Matrix<T, N> Matrix<T, N>::operator+(Matrix<T, N>) const {

}

template<typename T, size_t N>
Matrix<T, N> Matrix<T, N>::operator-(Matrix<T, N>) const {

}

template<typename T, size_t N>
Matrix<T, N> Matrix<T, N>::operator*(float c) const {

}
//template<typename T, size_t N>
//Matrix<T, N> operator*(Matrix<T, N> M, Vector V) {
//
//}
//
