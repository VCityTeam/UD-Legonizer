// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

#include "Ray.hpp"
#include "Hit.hpp"
#include "../../../Triangulate/Triangle.hpp"

//Ray

Ray::Ray(TVec3d ori, TVec3d dir, int id)
{
    this->id = id;
    this->ori = ori;
    this->dir = dir;
    inv_dir = TVec3d(1 / dir.x, 1 / dir.y, 1 / dir.z);
    sign[0] = (inv_dir.x < 0);
    sign[1] = (inv_dir.y < 0);
    sign[2] = (inv_dir.z < 0);
    fragCoord.x = -1;
    fragCoord.y = -1;
}

//Ray triangle intersection, from geometric tools engine
//License : http://www.boost.org/LICENSE_1_0.txt
bool Ray::Intersect(Triangle* triangle, Hit* hit)
{
    bool result;
    Hit tempHit;

    // Compute the offset origin, edges, and normal.
    TVec3d diff = this->ori - triangle->a;
    TVec3d edge1 = triangle->b - triangle->a;
    TVec3d edge2 = triangle->c - triangle->a;
    TVec3d normal = edge1.cross(edge2);

    // Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = ray direction,
    // E1 = edge1, E2 = edge2, N = Cross(E1,E2)) by
    //   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
    //   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
    //   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
    float DdN = this->dir.dot(normal);
    float sign;
    if (DdN > (float)0)
    {
        sign = (float)1;
    }
    else if (DdN < (float)0)
    {
        sign = (float)-1;
        DdN = -DdN;
    }
    else
    {
        // Ray and triangle are parallel, call it a "no intersection"
        // even if the ray does intersect.
        result = false;
        return result;
    }

    float DdQxE2 = sign*DotCross(this->dir, diff, edge2);
    if (DdQxE2 >= (float)0)
    {
        float DdE1xQ = sign*DotCross(this->dir, edge1, diff);
        if (DdE1xQ >= (float)0)
        {
            if (DdQxE2 + DdE1xQ <= DdN)
            {
                // Line intersects triangle, check whether ray does.
                float QdN = -sign*diff.dot(normal);
                if (QdN >= (float)0)
                {
                    // Ray intersects triangle.
                    result = true;

                    tempHit.intersect = true;
                    float inv = ((float)1) / DdN;
                    tempHit.parameter = QdN*inv;
                    tempHit.triangleBary[1] = DdQxE2*inv;
                    tempHit.triangleBary[2] = DdE1xQ*inv;
                    tempHit.triangleBary[0] = (float)1 - tempHit.triangleBary[1]
                        - tempHit.triangleBary[2];
                    tempHit.point = this->ori +
                        this->dir * tempHit.parameter;

                    tempHit.distance = (this->dir * tempHit.parameter).length();
                    tempHit.triangle = *triangle;
                    tempHit.ray = (*this);

                    if (hit != nullptr)
                    {
                        *hit = tempHit;
                    }
                    return result;
                }
                // else: t < 0, no intersection
            }
            // else: b1+b2 > 1, no intersection
        }
        // else: b2 < 0, no intersection
    }
    // else: b1 < 0, no intersection

    result = false;
    return result;
}


float Ray::DotCross(TVec3d v0, TVec3d v1,
    TVec3d v2)
{
    return v0.dot(v1.cross(v2));
}

TVec3d Ray::Normalized(TVec3d vec)
{
    return vec / vec.length();
}









