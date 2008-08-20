#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED
#include "BaseObject.h"

using namespace vmml;
using namespace RayTracerHelper;

class Sphere : public BaseObject
{
public:
  Sphere( const Vector3f& position,
          const float& radius,
          const Color& color,
          const float& reflectivity,
          const float& refractivity );
  virtual ~Sphere();
  virtual bool Intersect(Ray ray, IntersectionInfo &outInfo);
private:
  float radius;
};


#endif // SPHERE_H_INCLUDED
