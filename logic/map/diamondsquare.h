#ifndef DIAMONDSQUARE
#define DIAMONDSQUARE
#include <stdlib.h>
#include <glm/glm.hpp>
#include <vector>
#include "sge/ClassicNoise.h"

template<typename T> class Array2D
{
public:
    Array2D(size_t w, size_t h):
        width(w), height(h), data(new T[w*h]) {}
    ~Array2D() { if(data) {delete[] data;} data = nullptr; }

    glm::vec2 size() {return{width, height};}

    template <typename C>
    T *operator[](C i) {return data+((int)i)*height;}
private:
    T *data;
    size_t width, height;
};

struct DiamondSquare
{
    Array2D<float> *DsGenerate(int iWidth, int iHeight, float iRoughness)
    {
        Array2D<float> *points = new Array2D<float>(iWidth + 1, iHeight + 1);

        float c1 = rand()/(float)RAND_MAX;
        float c2 = rand()/(float)RAND_MAX;
        float c3 = rand()/(float)RAND_MAX;
        float c4 = rand()/(float)RAND_MAX;
        _dRoughness = iRoughness;
        _dBigSize = iWidth + iHeight;
        DsDivide(points, 0, 0, iWidth, iHeight, c1, c2, c3, c4);
        return points;
    }

private:
    float _dBigSize;
    float _dRoughness;

    static float Normalize(float iNum) {
        if (iNum < 0) {
            iNum = 0;
        }
        else if (iNum > 1.0f) {
            iNum = 1.0f;
        }
        return iNum;
    }

    void DsDivide(Array2D<float> *points, float x, float y, float width, float height, float c1, float c2, float c3, float c4)
    {
        float newWidth = glm::floor(width/2.0f);
        float newHeight = glm::floor(height/2.0f);

        if (width > 1 || height > 1) {
            float middle = ((c1 + c2 + c3 + c4)/4.0f) + PMove(newWidth + newHeight);
            float edge1 = ((c1 + c2)/2.0f);
            float edge2 = ((c2 + c3)/2.0f);
            float edge3 = ((c3 + c4)/2.0f);
            float edge4 = ((c4 + c1)/2.0f);
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

    float PMove(float smallSize)
    {
        return (rand()/(float)RAND_MAX - 0.5)*smallSize / _dBigSize * _dRoughness;
    }
};

#endif // DIAMONDSQUARE

