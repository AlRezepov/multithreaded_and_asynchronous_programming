#define _USE_MATH_DEFINES

#include "shape.h"

Shape::Shape() {}

Line::Line(const std::vector<int>& coordinates) : arr_coordinates(coordinates) {
    if (coordinates.size () != 4)
    {
        std::cout << "В массиве координат должно быть 4-е значения";
    }
}

void Line::SetCoordinates() {

    line_axis_coordinates.clear();

    for (int i = 0; i < arr_coordinates.size(); i++) 
    {
        int part = (i / 2) + 1;

        if (i % 2 == 0) {
            line_axis_coordinates.emplace("x" + std::to_string(part), arr_coordinates[i]);
        }
        else {
            line_axis_coordinates.emplace("y" + std::to_string(part), arr_coordinates[i]);
        }
    }
}

void Line::SetSide() {
    this->a = std::abs(line_axis_coordinates.at("x1") - line_axis_coordinates.at("x2"));
}
    
double Line::CalculateSquare() const {
    return 0.0;
}

double Line::CalculateVolume() const {
    return 0.0;
}

void Line::Shift(int _x, int _y, int _z = 0) {
    char filter_x = 'x';
    for (auto& i : line_axis_coordinates)
    {
        if (i.first[0] == filter_x) {
            i.second += _x;
        }
    }
    char filter_y = 'y';
    for (auto& i : line_axis_coordinates)
    {
        if (i.first[0] == filter_y) {
            i.second += _y;
        }
    }
}

void Line::ScaleX(int _x) {
    char filter_x = 'x';
    for (auto& i : line_axis_coordinates)
    {
        if (i.first[0] == filter_x) {
            i.second *= _x;
        }
    }
}

void Line::ScaleY(int _y) {
    char filter_y = 'y';
    for (auto& i : line_axis_coordinates)
    {
        if (i.first[0] == filter_y) {
            i.second *= _y;
        }
    }
}

void Line::ScaleZ(int _z) {}

void Line::Scale(int s) {
    for (auto& i : line_axis_coordinates)
    {
        i.second *= s;
    }
}

Rectangle::Rectangle(const std::vector<int>& coordinates) : arr_coordinates(coordinates) {
    if (coordinates.size() != 8)
    {
        std::cout << "В массиве координат должно быть 8-ь значений";
    }
}

void Rectangle::SetCoordinates() {

    rectangle_axis_coordinates.clear();
    
    for (int i = 0; i < arr_coordinates.size(); i++)
    {
        int part = (i / 2) + 1;

        if (i % 2 == 0) {
            rectangle_axis_coordinates.emplace("x" + std::to_string(part), arr_coordinates[i]);
        }
        else {
            rectangle_axis_coordinates.emplace("y" + std::to_string(part), arr_coordinates[i]);
        }
    }
}

void Rectangle::SetSide() {
    this->a = std::abs(rectangle_axis_coordinates.at("x1") - rectangle_axis_coordinates.at("x2"));
    this->b = std::abs(rectangle_axis_coordinates.at("y1") - rectangle_axis_coordinates.at("y2"));
}
    
double Rectangle::CalculateSquare() const {
    return this->a * this->b;
}

double Rectangle::CalculateVolume() const {
    return 0.0;
}

void Rectangle::Shift(int _x, int _y, int _z = 0) {
    char filter_x = 'x';
    for (auto& i : rectangle_axis_coordinates)
    {
        if (i.first[0] == filter_x) {
            i.second += _x;
        }
    }
    char filter_y = 'y';
    for (auto& i : rectangle_axis_coordinates)
    {
        if (i.first[0] == filter_y) {
            i.second += _y;
        }
    }
}

void Rectangle::ScaleX(int _x) {
    char filter_x = 'x';
    for (auto& i : rectangle_axis_coordinates)
    {
        if (i.first[0] == filter_x) {
            i.second *= _x;
        }
    }
}

void Rectangle::ScaleY(int _y) {
    char filter_y = 'y';
    for (auto& i : rectangle_axis_coordinates)
    {
        if (i.first[0] == filter_y) {
            i.second *= _y;
        }
    }
}

void Rectangle::ScaleZ(int _z) {}

void Rectangle::Scale(int s) {
    for (auto& i : rectangle_axis_coordinates)
    {
        i.second *= s;
    }
}

Parallelepiped::Parallelepiped(const std::vector<int>& coordinates) : arr_coordinates(coordinates) {
    if (coordinates.size() != 24)
    {
        std::cout << "В массиве координат должно быть 24 значения";
    }
}

void Parallelepiped::SetCoordinates() {

    parallelepiped_axis_coordinates.clear();
    
    for (int i = 0; i < arr_coordinates.size(); i++)
    {
        int part = (i / 3) + 1;

        if (i % 3 == 0) {
            parallelepiped_axis_coordinates.emplace("x" + std::to_string(part), arr_coordinates[i]);
        }
        else if (i % 3 == 1)
        {
            parallelepiped_axis_coordinates.emplace("y" + std::to_string(part), arr_coordinates[i]);
        }
        else {
            parallelepiped_axis_coordinates.emplace("z" + std::to_string(part), arr_coordinates[i]);
        }
    }
}

void Parallelepiped::SetSide() {
    this->a = std::abs(parallelepiped_axis_coordinates.at("x1") - parallelepiped_axis_coordinates.at("x2"));
    this->b = std::abs(parallelepiped_axis_coordinates.at("y1") - parallelepiped_axis_coordinates.at("y2"));
    this->c = std::abs(parallelepiped_axis_coordinates.at("z1") - parallelepiped_axis_coordinates.at("z2"));
}
    
double Parallelepiped::CalculateSquare() const {
    return 2 * (this->a * this->b + this->a * this->c + this->b * this->c);
}

double Parallelepiped::CalculateVolume() const {
    return this->a * this->b * this->c;
}

void Parallelepiped::Shift(int _x, int _y, int _z) {
    char filter_x = 'x';
    for (auto& i : parallelepiped_axis_coordinates)
    {
        if (i.first[0] == filter_x) {
            i.second += _x;
        }
    }
    char filter_y = 'y';
    for (auto& i : parallelepiped_axis_coordinates)
    {
        if (i.first[0] == filter_y) {
            i.second += _y;
        }
    }
    char filter_z = 'z';
    for (auto& i : parallelepiped_axis_coordinates)
    {
        if (i.first[0] == filter_z) {
            i.second += _z;
        }
    }
}

void Parallelepiped::ScaleX(int _x) {
    char filter_x = 'x';
    for (auto& i : parallelepiped_axis_coordinates)
    {
        if (i.first[0] == filter_x) {
            i.second *= _x;
        }
    }
}

void Parallelepiped::ScaleY(int _y) {
    char filter_y = 'y';
    for (auto& i : parallelepiped_axis_coordinates)
    {
        if (i.first[0] == filter_y) {
            i.second *= _y;
        }
    }
}

void Parallelepiped::ScaleZ(int _z) {
    char filter_z = 'z';
    for (auto& i : parallelepiped_axis_coordinates)
    {
        if (i.first[0] == filter_z) {
            i.second *= _z;
        }
    }
}

void Parallelepiped::Scale(int s) {
    for (auto& i : parallelepiped_axis_coordinates)
    {
        i.second *= s;
    }
}

Circle::Circle(double R) : radius(R) {}

double Circle::CalculateSquare() const {
    return M_PI * radius * radius;
}

double Circle::CalculateVolume() const {
    return 0.0;
}

Cylinder::Cylinder(double R, double H) : radius(R), height(H) {}

double Cylinder::CalculateSquare() const {
    return 2 * M_PI * radius * (radius + height);
}

double Cylinder::CalculateVolume() const {
    return M_PI * radius * radius * height;
}