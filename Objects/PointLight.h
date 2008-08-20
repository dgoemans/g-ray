#ifndef POINTLIGHT_H_INCLUDED
#define POINTLIGHT_H_INCLUDED
#include "../RayTracerHelper.h"

using namespace vmml;
using namespace RayTracerHelper;

class PointLight
{
public:
  PointLight( const Vector3f& position,
              const Color& color,
              const float& power,
              const float& attenuation  );
  ~PointLight();
  const Color& GetColor() { return color; }
  const float& GetPower() { return power; }
  const float& GetAttenuation() { return attenuation; }
  const Vector3f& GetPosition() { return position; }

protected:
  Vector3f position;
  Color color;
  float power;
  float attenuation;
};

#endif // POINTLIGHT_H_INCLUDED
