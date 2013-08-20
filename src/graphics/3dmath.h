/*
 *  This file is part of Experiental.
 *
 *  Experiental is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Experiental is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Experiental.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _3DMATH_H_
#define _3DMATH_H_

#include <cfloat>  //_isnan() for acos()

#define PI 3.1415926535897932

struct CVector3 {
public:
    float x, y, z;
};

CVector3 Cross(CVector3 vVector1, CVector3 vVector2);
CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2);
float Magnitude(CVector3 vNormal);
CVector3 Normalize(CVector3 vNormal);
CVector3 Normal(CVector3 vTriangle[]);
float PlaneDistance(CVector3 Normal, CVector3 Point);

bool IntersectedPlane(CVector3 vPoly[], CVector3 vLine[], CVector3 &vNormal, float &originDistance);
//dot product between two vectors
float Dot(CVector3 vVector1, CVector3 vVector2);
//angle between two vectors
double AngleBetweenVectors(CVector3 Vector1, CVector3 Vector2);
//point of the polygon and line intersection (plane intersection)
CVector3 IntersectionPoint(CVector3 vNormal, CVector3 vLine[], double distance);
//true if intersection is inside the polygon
bool InsidePolygon(CVector3 vIntersection, CVector3 Poly[], long verticeCount);
//need to use this function for line and polygon intersection test
bool IntersectedPolygon(CVector3 vPoly[], CVector3 vLine[], int verticeCount);

#endif // _3DMATH_H_
