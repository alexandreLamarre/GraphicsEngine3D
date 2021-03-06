#include <stddef.h>
#include <vector>
#include "vector.h"



/***
 * Square Matrix object that only stores floats
 * Used to speed up computations
 * @tparam N dimension of the square matrix
 */
template<size_t N>
class Matrixf{
public:
    Matrixf();
    Matrixf(std::initializer_list<float> elements);
    Matrixf(std::initializer_list<std::initializer_list<float>> elements);
    explicit Matrixf(std::string &special_matrix);
    std::vector<float> row(int index);
    std::vector<float> col(int index);
    Matrixf<N> operator+(Matrixf<N> M) const;
    Matrixf<N> operator-(Matrixf<N> M) const;
    Matrixf<N> operator^(int power);
    std::vector<float> operator[](int index);

    template<size_t n>
    friend Matrixf<n> operator*(float c, Matrixf<n> M);
    template<size_t n>
    friend Matrixf<n> operator*(Matrixf<n> M, Matrixf<n> K);
    template<size_t n>
    friend Vectorf<n> operator*(Matrixf<n> T, Vectorf<n> V); //left matrix mult
    template<size_t n>
    friend Vectorf<n> operator*(Vectorf<n> V, Matrixf<n> M);
    static float dotProduct(std::vector<float> row, std::vector<float> col);
    Matrixf<N> invert();
    template<size_t n>
    friend float det(Matrixf<n> M);

    template<size_t n>
    friend float* adj(Matrixf<n> M);
    static Matrixf<N> mProduct(Vectorf<N> A, Vectorf<N> B);
private:
    friend class Vectorf<N>;
    size_t size;
    std::vector<float> elems;
    friend float det(float matrix[N][N], size_t cur_size);
    friend void adj(float matrix[N][N], float ADJ[N][N]);
    friend void getCofactor(float matrix[N][N], float temp[N][N], int p, int q, int n);
};



/**
 * Non-square custom dimension matrix object that stores only floats.
 * Should only be used when necessary to improve time/space complexity
 * of some calculations.
 */
template<size_t n, size_t m>
class NMatrixf{
public:
    NMatrixf();
    NMatrixf(std::initializer_list<float>);
    NMatrixf(std::initializer_list<std::initializer_list<float>>);
private:
    size_t num_cols;
    size_t num_rows;
    std::vector<float> elems;
};


/**
 * more general Square matrix object that stores elements of type T
 * @tparam T the elements in the matrix
 * @tparam N the dimension of the square ma trix
 */
template<typename T, size_t N>
class Matrix{
public:
    Matrix(std::initializer_list<T> elems, size_t dim);
    std::vector<T> row();
    std::vector<T> col();
//    Vector rowVector(); // rows must be 3D float tuple only
//    Vector rowColumn(); //cols must be 3D float tuple only
    Matrix<T,N> operator+(Matrix<T,N>) const;
    Matrix<T,N> operator-(Matrix<T,N>) const;
    Matrix<T,N> operator*(float c) const;
//    friend Matrix<T,N> operator*(Matrix<T,N> M, Vector V);
private:
    size_t size;
    std::vector<T> elems;

//    template<typename U> Matrix(const Matrix_ref<U,N>&);
};

