#include "graphics/3dmath.h"
#include <math.h>

///Cross
//Возвращает вектор перепендикулярный двум векторам
CVector3 Cross(CVector3 vVector1, CVector3 vVector2) {
    CVector3 vNormal;

    vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
    vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
    vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

    return vNormal;
}

///Vector
//Возвращает вектор между двумя точками
CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2) {
    CVector3 vVector = {0};

    vVector.x = vPoint1.x - vPoint2.x;
    vVector.y = vPoint1.y - vPoint2.y;
    vVector.z = vPoint1.z - vPoint2.z;

    return vVector;
}

///Magnitude
//Возвращает величину нормали, используя теорему Пифагора
float Magnitude(CVector3 vNormal) {
    return sqrt((vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z));
}

///Normalize
//Возвращает нормализованный вектор (с длинной 1)
CVector3 Normalize(CVector3 vNormal) {
    float magnitude = Magnitude(vNormal);

    vNormal.x /= magnitude;
    vNormal.y /= magnitude;
    vNormal.z /= magnitude;

    return vNormal;
}

///Normal
//Возвращает нормаль полигона. Из треугольника (а это 3 вектора) мы берём нижнюю левую сторону,
//для вычисления перпендикуляра (Cross()). В нешем случае мы работаем в противо-часовом направлении.
CVector3 Normal(CVector3 vTriangle[]) {
    CVector3 vVector1 = Vector(vTriangle[2], vTriangle[0]);
    CVector3 vVector2 = Vector(vTriangle[1], vTriangle[0]);

    CVector3 vNormal = Cross(vVector1, vVector2);
    vNormal = Normalize(vNormal);

    return vNormal;
}

///PlaneDistance
//Возвращает расстрояние плоскости от начала координат(0, 0, 0).
//Принимает нормаль плоскости и ЛЮБУЮ точку, лежащую на этой плоскости.
float PlaneDistance(CVector3 Normal, CVector3 Point) {
    float distance = 0;
    //A*x + B*y + C*z + D = 0; gde A,B,C eto znachenija X,Y,Z nashej normali, a x,y,z eto koordianty tochki
    distance = - ((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));

    return distance;
}

///IntersectedPlane
//Принимает треугольник(плоскость) и линию, и возвращает true при их пересечении.
bool IntersectedPlane(CVector3 vPoly[], CVector3 vLine[], CVector3 &vNormal, float &originDistance) {
    float distance1 = 0, distance2 = 0;
    vNormal = Normal(vPoly);

    originDistance = PlaneDistance(vNormal, vPoly[0]);

    distance1 = ((vNormal.x * vLine[0].x) +
                 (vNormal.y * vLine[0].y) +
                 (vNormal.z * vLine[0].z)) + originDistance;

    distance2 = ((vNormal.x * vLine[1].x) +
                 (vNormal.y * vLine[1].y) +
                 (vNormal.z * vLine[1].z)) + originDistance;

    if(distance1 * distance2 >= 0)
        return false;

    return true;
}

float Dot(CVector3 vVector1, CVector3 vVector2) {
    //V1.V2 = (V1.x * V2.x + V1.y * V2.y + V1.z * V2.z)
    //Math: V1.V2 = ||V1|| ||V2|| cos(theta),    "." - DOT,  "|| ||" > 0;
    return ((vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z));
}

double AngleBetweenVectors(CVector3 Vector1, CVector3 Vector2) {
    float dotProduct = Dot(Vector1, Vector2);
    float vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2);
    double angle = acos(dotProduct / vectorsMagnitude);
    //necessary test
    if(isnan(angle))
        return 0;
    //angle in degrees
    return angle;
}

CVector3 IntersectionPoint(CVector3 vNormal, CVector3 vLine[], double distance) {
    CVector3 vPoint = {0}, vLineDir = {0};
    double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

    //We need to find a 3d point, which is on a plane
    //1)
    vLineDir = Vector(vLine[1], vLine[0]);
    vLineDir = Normalize(vLineDir);
    //2)    Distance negative, 'cause we go BACK from point to plane.
    Numerator = - (vNormal.x * vLine[0].x +
                   vNormal.y * vLine[0].y +
                   vNormal.z * vLine[0].z + distance);
    //3)
    Denominator = Dot(vNormal, vLineDir);
    //Normal.Vector != 0
    if(Denominator == 0.0)
        return vLine[0];

    dist = Numerator / Denominator;

    vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
    vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
    vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));
    //intersection point
    return vPoint;
}

bool InsidePolygon(CVector3 vIntersection, CVector3 vPoly[], long verticeCount) {
    const double MATCH_FACTOR = 0.9999;     //for floating point error
    double Angle = 0.0;
    CVector3 vA, vB;

    for(int i = 0; i<verticeCount; i++) {
        vA = Vector(vPoly[i], vIntersection);
        vB = Vector(vPoly[(i+1)%verticeCount], vIntersection);
        Angle += AngleBetweenVectors(vA, vB);
    }
    //360 degrees test with an error
    if(Angle >= (MATCH_FACTOR * (2.0 * PI)))
        return true;
    return false;
}

//does line intersect polygon?
bool IntersectedPolygon(CVector3 vPoly[], CVector3 vLine[], int verticeCount) {
    CVector3 vNormal = {0};
    float originDistance = 0;
                        //Pointer     //Pointer
    if(!IntersectedPlane(vPoly, vLine, vNormal, originDistance))
        return false;
    CVector3 vIntersection = IntersectionPoint(vNormal, vLine, originDistance);
    if(InsidePolygon(vIntersection, vPoly, verticeCount))
        return true;
    return false;
}


