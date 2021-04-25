
#include<math.h>

struct point
{
    float x;
    float y;
};

float sign(point p1, point p2, point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(point pt, point v1, point v2, point v3)
{
    float d1, d2, d3;
    bool neg, pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(neg && pos);
}

