#pragma once
namespace Rain
{

class ViewManipulator
{
public:
    ViewManipulator();
    ~ViewManipulator();

public:
    void fitview();
    void pan(int x, int y);
    void zoom(float direction, float deta);
};

}


