#include "transform.h"

void Transformation::Shift(Shape& shape, int _x, int _y, int _z) {
	shape.Shift(_x, _y, _z);
}

void Transformation::ScaleX(Shape& shape, int _x) {
	shape.ScaleX(_x);
}

void Transformation::ScaleY(Shape& shape, int _y) {
	shape.ScaleY(_y);
}

void Transformation::ScaleZ(Shape& shape, int _z) {
	shape.ScaleZ(_z);
}

void Transformation::Scale(Shape& shape, int s) {
	shape.Scale(s);
}