#ifndef GRAPHICSENGINE3D_VECTOR_H
#define GRAPHICSENGINE3D_VECTOR_H

#endif //GRAPHICSENGINE3D_VECTOR_H
#include <iostream>


/**
 * General n-dimensional Vector/Point float class.  * Distinctions between the two
 * should be made in the naming of the object.
 * Stores 1 extra float for clipping/culling and collision detection.
 * Vector type objects follow the convention of being column-vectors;
 * so that matrix transformations are done from the left.
 * 3 dimensional vectors are 16-bit, so compatible with console development.
 * @tparam N dimension of float vector
 */
template<size_t N>
class Vectorf{
public:
    Vectorf();
    Vectorf(std::initializer_list<float> input);
    Vectorf<N> operator+(Vectorf<N> V);
    Vectorf<N> operator-(Vectorf<N> V);
    float operator*(Vectorf<N> V); //dot product
    Vectorf<N> operator^(Vectorf<N> V); //cross product
    friend Vectorf<N> operator*(float c, Vectorf<N> V);
    float norm();
    float norm2(); //square of norm to avoid sqrt operations
    bool operator<(Vectorf<N> other_vector); //between origin and other vector
    bool operator<(float dist); // norm is smaller than given norm
    friend std::ostream& operator<< (std::ostream &os, Vectorf<N> V);

    Vectorf<N> normalize();
    Vectorf<N> rotate3(std::string& plane, float radians); //3d orthonormal rotation
    Vectorf<N> gRotate3(float axis[3], float radians); // general 3d rotation
    Vectorf<N> reflect3(std::string& plane); //reflection through a plane
    Vectorf<N> gReflect3(float pos[N]); //reflection through a plane specified by a normal

    Vectorf<N> scale(Vectorf<N> D, Vectorf<N> S);
    Vectorf<N> orthoProject3(std::string &plane); //3D orthogonal projection onto plane
    Vectorf<N> oblProject3(std::string &plane, Vectorf<N> D); // 3D oblique projection onto plane
    Vectorf<N> pProject(Vectorf<N> E, Vectorf<N> P, Vectorf<N> Normal); //perspective projection

    static Vectorf<N> AffineCSum (int n, float C[], Vectorf<N> Q[]);
    static Vectorf<N> AffineDsum (int n, float d[], Vectorf<N> Q[]);
    friend Vectorf<N> extend(Vectorf<N> V, size_t dim);

private:
    float pos[N];
    float e; //default = 0
};


// ============= Helper functions =====================
/**
 * Fast sgn function for valid types: double, float, int and other constructible types from 0
 * @tparam T type to extract sign from
 * @param val value to extract sign from
 * @return the sign of val when applicable
 */
template<typename T> int sgn(T val){
    return (T(0) < val) - (val < T(0));
}


