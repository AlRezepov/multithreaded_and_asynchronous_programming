#pragma once
#include "shape.h"

class Transformation {
public:
    void Shift(Shape& shape, int _x, int _y, int _z);
    void ScaleX(Shape& shape, int _x);
    void ScaleY(Shape& shape, int _y);
    void ScaleZ(Shape& shape, int _z);
    void Scale(Shape& shape, int s);
};
