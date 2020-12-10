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
    Vectorf(std::initializer_list<float>);
    Vectorf<N> operator+(Vectorf<N> V);
    Vectorf<N> operator-(Vectorf<N> V);
    float operator*(Vectorf<N> V); //dotproduct
    Vectorf<N> operator^(Vectorf<N> V); //cross product
    friend Vectorf<N> operator*(float c, Vectorf<N> V);
    friend std::ostream& operator<< (std::ostream &o, Vectorf<N> V);

    Vectorf<N> normalize();
    Vectorf<N> rotate();
    Vectorf<N> gRotate();
    Vectorf<N> reflect();
    Vectorf<N> gReflect();
    Vectorf<N> oProject(); //orthogonal projection
    Vectorf<N> sProject(); //spherical projection
    Vectorf<N> pProject(); //plane projection

    static Vectorf<N> AffineCSum (int n, float C[], Vectorf<N> Q[]);
    static Vectorf<N> AffineDsum (int n, float d[], Vectorf<N> Q[]);

private:
    float pos[N];
    float e;
};





