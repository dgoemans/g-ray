#include "BaseObject.h"

/** @brief BaseObject
  *
  * @todo: document this function
  */
BaseObject::BaseObject( const Vector3f& position,
                        const Color& color,
                        const float& reflectivity,
                        const float& refractivity )
:
position( position ),
color( color ),
reflectivity( reflectivity )

{

}

/** @brief ~BaseObject
  *
  * @todo: document this function
  */
 BaseObject::~BaseObject()
{

}
/** @brief Intersect
  *
  * @todo: document this function
  */
bool BaseObject::Intersect(Ray ray, IntersectionInfo &outInfo)
{
  return false;
}




