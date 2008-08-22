#ifndef RAYTRACER_H_INCLUDED
#define RAYTRACER_H_INCLUDED

#include <list>
#include "vmmlib/vmmlib.h"
#include "Objects/AllObjects.h"
#include "RayTracerHelper.h"

#include <GL/gl.h>
#include <GL/glut.h>

using namespace RayTracerHelper;
using namespace vmml;
using namespace std;

class RayTracer
{
public:
  RayTracer();
  ~RayTracer();
  void Trace( int width, int height );
private:
  BaseObject* const CastRayOnScene( Ray& rayToCast, BaseObject* objectToExclude, IntersectionInfo& outInfo );
  bool enabled;
  list<BaseObject*> objects;
  list<PointLight*> lights;
};

#endif // RAYTRACER_H_INCLUDED
