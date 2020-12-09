#include "vector.h"
#include <iostream>
#include <cassert>

// Implementation details of Vector(also Point) objects.
// Norms are determined by cross product of orthonormal basis X,Y,Z
//such that X x Y = Z, so that our coordinate system obeys the 'right-handedness' rule




/**
 * Default constructor for Vector/Point when no parameters are specified.
 * Position tuple is intialized to all zeroes.
 */
Vector::Vector(){
    tuple[0] = 0;
    tuple[1] = 0;
    tuple[2] = 0;
    tuple[3] = 0;
};

/**
 * Constructor for Vector using specified parameters.
 * Collision Parameter c should always be initialized to 0 for new vectors.
 * Collision Parameter can be non-zero only when specifying Vectors/Points obtained from operations.
 * @param x float indicating x position
 * @param y float indicating y position
 * @param z float indicating z position
 * @param c float indicating collision parameter
 */
Vector::Vector(float x, float y, float z, float c){
    tuple[0] = x;
    tuple[1] = y;
    tuple[2] = z;
    tuple[3] = c;
};

/**
 * Operation for adding to Vectors. Follows the rules of affine algebra.
 * @param V vector to be added to our vector
 * @return vector obtained from vector addition
 */
Vector Vector::operator+(Vector V) const {
    Vector new_vector(tuple[0]+ V.tuple[0], tuple[1] + V.tuple[1], tuple[2] + V.tuple[2],
                      tuple[3] + V.tuple[3]);
    return new_vector;
};
/**
 * Vector Subtraction operation between two vectors. Follows the rules of affine algebra.
 * @param V vector to be subtracted from our vector
 * @return vector obtained from the vector subtraction operation
 */
Vector Vector::operator-(Vector V) const{
    Vector new_vector{tuple[0]-V.tuple[0], tuple[1] - V.tuple[1], tuple[2] - V.tuple[2],
                      tuple[3] - V.tuple[3]};
    return new_vector;
};

/**
 * Vector scalar multiplication
 * @param c scalar to multiply the vector by
 * @return vector obtained from scalar multiplication by c
 */
Vector Vector::operator*(float c) const {
    return Vector{c*tuple[0], c*tuple[1], c*tuple[2], c*tuple[3]};
}
Vector operator*(float c, Vector V) {
    return Vector{c*V.tuple[0], c*V.tuple[1], c*V.tuple[2], c*V.tuple[3]};
}

/**
 * std::cout representation of a Vector.
 * @param os the ostream to write to
 * @param V the vector to parse
 * @return Vector parsed into string format in a ostream object
 */
std::ostream& operator<<(std::ostream& os, Vector V){
    os<< "x: "<< V.tuple[0] << ", y: "<< V.tuple[1] << ", z: "
      << V.tuple[2] << ", collision: " << V.tuple[3];
    return os;
};

/**
 * Weighted sum of an array of Vectors representing points into another Point.
 * Coefficients must Sum to 1.
 * By convention, in affine algebra, used as a way to sum points to another point.
 * @param N size of array parameters
 * @param C coefficient array of sine N
 * @param Q Vector array of size N representing Points
 * @return Affine sum of vectors and coefficients
 */
Vector Vector::AffineCSum(int N, float *C, Vector *Q) {
    int sum = 0;
    Vector new_vector = Vector();
    for(int i = 0; i < N; i++){
        new_vector = new_vector + C[i]*Q[i];
        sum += C[i];
    }
    assert(sum == 1);
    return new_vector;
};

/**
 * Weighted sum of an array of Vectors representing points into a Vector.
 * Coefficients must sum to 0.
 * @param N size of the parameter arrays
 * @param d coefficients array of size N
 * @param Q Vector array of size N representing Points
 * @return Affine sum of vectors and coefficients
 */
Vector Vector::AffineDsum(int N, float *d, Vector *Q) {
    int sum = 0;
    Vector new_vector = Vector();
    for(int i = 0; i < N; i++){
        new_vector = new_vector + d[i]*Q[i];
        sum+= d[i];
    };
    assert(sum == 0);
    return new_vector;
};

/**
 * rotate the xy-plane by the z-axis  OR
 * rotate the xz-plane by the y-axis OR
 * rotate the yz-plane by the x-axis
 * @param axis Z = 1, Y = 2, X = 3
 * @return rotated vector
 */
Vector Vector::Rotate(int axis) {
//    float rotationMatrix =
};
