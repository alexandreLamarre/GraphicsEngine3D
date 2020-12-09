#ifndef GRAPHICSENGINE3D_VECTOR_H
#define GRAPHICSENGINE3D_VECTOR_H

#endif //GRAPHICSENGINE3D_VECTOR_H
#include <iostream>

/**
 * Class for Vector and Point Objects in affine algebra (for graphics engines).
 * Distinctions between the two will be made in naming of
 * Vector type objects.
 *
 * Vector type objects follow the convention of being column-vectors;
 * so that matrix multiplication is done from the left.
 */
class Vector{
public:
    Vector();
    Vector(float x, float y, float z, float c);
    Vector operator+ (Vector V) const;
    Vector operator- (Vector V) const;
    Vector operator* (float c) const;
    friend Vector operator* (float c, Vector V);
    Vector Rotate(int axis);
    Vector generalRotate(Vector directionVector);
    friend std::ostream& operator<< (std::ostream &o, Vector V);
    static Vector AffineCSum (int N, float C[], Vector Q[]);
    static Vector AffineDsum (int N, float d[], Vector Q[]);
private:
    float tuple[4]{}; // (x,y,z, collision), collision should always be initialized to 0.0 for a new vector/point
};

