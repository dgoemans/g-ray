#ifndef RAYTRACERHELPER_H_INCLUDED
#define RAYTRACERHELPER_H_INCLUDED
#include "vmmlib/vmmlib.h"

#ifndef NULL
#define NULL 0
#endif

using namespace vmml;

namespace RayTracerHelper
{
  typedef Vector4f Color;

  struct Ray
  {
    Vector3f start, direction;
    Ray( Vector3f start, Vector3f dir )
    :
    start( start ),
    direction( dir )
    {
    }
  };

  struct IntersectionInfo
  {
    Vector3f normal;
    Vector3f pointOfIntersection;
    Color diffuseColorOfObject;
    float distOnRay;
  };

};


#endif // RAYTRACERHELPER_H_INCLUDED
