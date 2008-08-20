#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED
#include "../RayTracerHelper.h"
#include "vmmlib/vmmlib.h"

using namespace vmml;
using namespace RayTracerHelper;

class BaseObject
{
public:
  BaseObject( const Vector3f& position,
              const Color& color,
              const float& reflectivity,
              const float& refractivity);
  virtual ~BaseObject();
  virtual bool Intersect( Ray ray, IntersectionInfo &outInfo );
  const float& GetRefletivity() { return reflectivity; }
  const Vector3f& GetPosition() { return position; }
  const Color& GetColor() { return color; }
protected:
  Color color;
  Vector3f position;
  float reflectivity;
};


#endif // BASEOBJECT_H_INCLUDED
