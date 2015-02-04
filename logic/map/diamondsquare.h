#ifndef DIAMONDSQUARE
#define DIAMONDSQUARE
#include <stdlib.h>
#include <glm/glm.hpp>
#include <vector>
#include "sge/ClassicNoise.h"

template<typename T> class Array2D
{
public:
    Array2D(unsigned int w, unsigned int h):
        width(w), height(h), data(new T[w*h]) {}
    ~Array2D() { if(data) {delete[] data;} data = nullptr; }

    template <typename C>
    T* operator[](C i) {return data+((int)i)*height;}
private:
    T* data = nullptr;
    unsigned int width = 0, height = 0;
};

struct DiamondSquare
{
    Array2D<float> *DsGenerate(int iWidth, int iHeight, double iRoughness)
    {
        Array2D<float> *points = new Array2D<float>(iWidth + 1, iHeight + 1);

        double c1 = rand()/(double)RAND_MAX;
        double c2 = rand()/(double)RAND_MAX;
        double c3 = rand()/(double)RAND_MAX;
        double c4 = rand()/(double)RAND_MAX;
        _dRoughness = iRoughness;
        _dBigSize = iWidth + iHeight;
        DsDivide(points, 0, 0, iWidth, iHeight, c1, c2, c3, c4);
        return points;
    }

private:
    double _dBigSize;
    double _dRoughness;

    static double Normalize(double iNum) {
        if (iNum < 0) {
            iNum = 0;
        }
        else if (iNum > 1.0) {
            iNum = 1.0;
        }
        return iNum;
    }

    void DsDivide(Array2D<float> *points, double x, double y, double width, double height, double c1, double c2, double c3, double c4)
    {
        double newWidth = glm::floor(width/2.0);
        double newHeight = glm::floor(height/2.0);

        if (width > 1 || height > 1) {
            double middle = ((c1 + c2 + c3 + c4)/4.0) + PMove(newWidth + newHeight);
            double edge1 = ((c1 + c2)/2.0);
            double edge2 = ((c2 + c3)/2.0);
            double edge3 = ((c3 + c4)/2.0);
            double edge4 = ((c4 + c1)/2.0);
            middle = Normalize(middle);
            edge1 = Normalize(edge1);
            edge2 = Normalize(edge2);
            edge3 = Normalize(edge3);
            edge4 = Normalize(edge4);
            DsDivide(points, x, y, newWidth, newHeight, c1, edge1, middle, edge4);
            DsDivide(points, x + newWidth, y, width - newWidth, newHeight, edge1, c2, edge2, middle);
            DsDivide(points, x + newWidth, y + newHeight, width - newWidth, height - newHeight, middle, edge2, c3, edge3);
            DsDivide(points, x, y + newHeight, newWidth, height - newHeight, edge4, middle, edge3, c4);
        }
        else {
            float c = (float) (c1 + c2 + c3 + c4)/4.0;

            (*points)[(int)x][(int)y] = c;
            if (width == 2) {
                (*points)[(int)x + 1][(int)y] = c;
            }
            if (height == 2) {
                (*points)[(int)x][(int)y + 1] = c;
            }
            if ((width == 2) && (height == 2)) {
                (*points)[(int)x + 1][(int)y + 1] = c;
            }
        }
    }

    double PMove(double smallSize)
    {
        return (rand()/(float)RAND_MAX - 0.5)*smallSize / _dBigSize * _dRoughness;
    }
};

#endif // DIAMONDSQUARE

