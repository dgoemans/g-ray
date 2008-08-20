#include "Sphere.h"

using namespace vmml;

/** @brief Sphere
  *
  * @todo: document this function
  */
Sphere::Sphere( const Vector3f& position,
                const float& radius,
                const Color& color,
                const float& reflectivity,
                const float& refractivity )
:
BaseObject( position, color, reflectivity, refractivity ),
radius( radius )
{
}

/** @brief ~Sphere
  *
  * @todo: document this function
  */
Sphere::~Sphere()
{

}



/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool Sphere::Intersect(Ray ray, IntersectionInfo &outInfo)
{
  // Assumes ray direction is normalized
	// Uses quadratic formula, A = 1 because ray.d is normalized.
	// For derivation, see:
	// http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter1.htm
	Vector3f dist = position - ray.start;
	float B = dist.dot(ray.direction); // B really equals 2.0f this value
	float C = dist.dot(dist) - radius*radius;
	float D = B*B - C;  // Discriminant.  D really equals 4.0f times this value
	if (D < 0)
    return false;
		//return std::numeric_limits<float>::infinity();
	float sqrtD = sqrt(D); // sqrtD really equals 2.0f times this value
//	float t0 = (-2.0f * B - 2.0f * sqrtD) * 0.5f;  // The factors cancel out
	float t0 = (-B - sqrtD); // Will always be the smaller, but may be negative
	float t1 = (-B + sqrtD); // The second intersection, if you care
	//return t0;
	outInfo.pointOfIntersection = ray.start - ray.direction*t1;
	outInfo.diffuseColorOfObject = color;
	outInfo.distOnRay = t1;
	outInfo.normal = (outInfo.pointOfIntersection - position)/radius;
//	if( outInfo.normal.z > 0.5 )
  //std::cout<<"Int: "<<outInfo.pointOfIntersection <<"\n";
  //std::cout<< "t0: " << t0 <<"\t t1: "<< t1 << "\n";
	outInfo.normal.normalize();
	return true;
}
