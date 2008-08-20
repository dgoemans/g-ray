#include "PointLight.h"

/** @brief PointLight
  *
  * @todo: document this function
  */
PointLight::PointLight(const Vector3f& position,
                        const Color& color,
                        const float& power,
                        const float& attenuation)
:
position( position ),
color( color ),
power( power ),
attenuation( attenuation )
{

}



/** @brief ~PointLight
  *
  * @todo: document this function
  */
PointLight::~PointLight()
{

}
