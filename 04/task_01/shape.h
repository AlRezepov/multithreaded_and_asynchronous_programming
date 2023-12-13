#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Shape {
public:
    Shape();
    virtual void SetCoordinates() = 0;
    virtual void SetSide() = 0;

    virtual double CalculateSquare() const = 0;
    virtual double CalculateVolume() const = 0;

    virtual void Shift(int _x, int _y, int _z) = 0;
    virtual void ScaleX(int _x) = 0;
    virtual void ScaleY(int _y) = 0;
    virtual void ScaleZ(int _z) = 0;
    virtual void Scale(int s) = 0;
};

class Line : public Shape {
private:
    std::vector<int> arr_coordinates;
    std::map<std::string, int> line_axis_coordinates;
    int a;

public:
    Line(const std::vector<int>& coordinates);

    void SetCoordinates() override;

    void SetSide() override;

    double CalculateSquare() const override;

    double CalculateVolume() const override;

    void Shift(int _x, int _y, int _z) override;

    void ScaleX(int _x) override;

    void ScaleY(int _y) override;

    void ScaleZ(int _z) override;

    void Scale(int s) override;
};

class Rectangle : public Shape {
private:
    std::vector<int> arr_coordinates;
    std::map<std::string, int> rectangle_axis_coordinates;
    int a, b;

public:
    Rectangle(const std::vector<int>& coordinates);

    void SetCoordinates() override;

    void SetSide() override;

    double CalculateSquare() const override;

    double CalculateVolume() const override;

    void Shift(int _x, int _y, int _z) override;

    void ScaleX(int _x) override;

    void ScaleY(int _y) override;

    void ScaleZ(int _z) override;

    void Scale(int s) override;
};

class Parallelepiped : public Shape {
private:
    std::vector<int> arr_coordinates;
    std::map<std::string, int> parallelepiped_axis_coordinates;
    int a, b, c;

public:
    Parallelepiped(const std::vector<int>& coordinates);

    void SetCoordinates() override;

    void SetSide() override;

    double CalculateSquare() const override;

    double CalculateVolume() const override;

    void Shift(int _x, int _y, int _z) override;

    void ScaleX(int _x) override;

    void ScaleY(int _y) override;

    void ScaleZ(int _z) override;

    void Scale(int s) override;
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double R);

    double CalculateSquare() const override;

    double CalculateVolume() const override;
};

class Cylinder : public Shape {
private:
    double radius;
    double height;

public:
    Cylinder(double R, double H);

    double CalculateSquare() const override;

    double CalculateVolume() const override;
};
