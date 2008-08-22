#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "raytracer.h"

using namespace RayTracerHelper;
using namespace std;
using namespace vmml;

const float SCENE_MAX = 10000.0f;

RayTracer::RayTracer()
:
enabled(true),
objects(),
lights()
{
  {
    Vector3f pos( 190, 170, 300.0f );
    Color col( 0,0,255,255 );
    objects.push_back( new Sphere( pos,
                                   10.0f,
                                   col,
                                   0.5f, 0 ) );

    pos = Vector3f( 170, 190, 300.0f );
    col = Color( 0,0,255,255 );
    objects.push_back( new Sphere( pos,
                                   10.0f,
                                   col,
                                   0.5f, 0 ) );

    pos = Vector3f( 210, 150, 300.0f );
    col = Color( 0,0,255,255 );
    objects.push_back( new Sphere( pos,
                                   10.0f,
                                   col,
                                   0.5f, 0 ) );

    pos = Vector3f( 135, 150, 280.0f );
    col = Color( 255,0,0,255 );
    objects.push_back( new Sphere( pos,
                                   20.0f,
                                   col,
                                   0.5f, 0 ) );

    pos = Vector3f( 190, 115, 300.0f );
    col = Color( 0,255,0,255 );
    objects.push_back( new Sphere( pos,
                                   30.0f,
                                   col,
                                   0.5f, 0 ) );
  }
  {
    Vector3f pos( -1500,500, -100 );
    Color col( 255,255,255,255 );
    lights.push_back( new PointLight( pos,
                                      col,
                                      0.5f,
                                      0.0f ) );
  }
}

RayTracer::~RayTracer()
{
}

void RayTracer::Trace( int width, int height)
{
  cout<<"Raytracing window: "<<width<<"x"<<height<<"\n";
  int screenWidth = width;
  int screenHeight = height;
  for( int i=0; i<screenHeight; i++ )
  {
    for( int j=0; j<screenWidth; j++ )
    {
      Color color(0,0,0,255);

      Vector3f start( screenWidth/2, screenHeight/2, 0.0f );
      Vector3f dir( j - screenWidth/2, i - screenHeight/2, 1000.0f );
      dir.normalize();

      Ray currentRay( start, dir );
      IntersectionInfo nearestIntersection;

      BaseObject* intersectingObject = CastRayOnScene( currentRay, NULL, nearestIntersection );

      if( intersectingObject != NULL )
      {
        // Basic Color
        color = nearestIntersection.diffuseColorOfObject*0.3f;

        // Lighting
        list<PointLight*>::iterator it;
        for( it = lights.begin(); it != lights.end(); ++it )
        {
          PointLight* light = *it;
          // create ray in the direction of the lightsource
          Ray lightRay( nearestIntersection.pointOfIntersection, light->GetPosition() - nearestIntersection.pointOfIntersection );
          //float dist = lightRay.direction.length();
          lightRay.direction.normalize();
          Vector3f invLightRayDir = lightRay.direction;

          IntersectionInfo lightInfo;
          BaseObject* obj = CastRayOnScene( lightRay, intersectingObject, lightInfo );
          float softShadow = 1;
//          if( obj != NULL  )
//          {
//              //color -= Color( 0.3,0.3,0.3,1);
//            Color highlight = color;
//            softShadow = 0.3*invLightRayDir.dot( lightInfo.normal );
//            color += highlight*softShadow;
//          }
//          else //the light is not in shadow of another object
          {
            float dot = invLightRayDir.dot( nearestIntersection.normal );

            Color highlight = color;
            highlight *= dot;

            Vector3f blinnDir = lightRay.direction - currentRay.direction;
            float blinMag = blinnDir.length();
            if (blinMag != 0.0f)
            {
              blinnDir = blinnDir * (1.0f / blinMag);
              float blinnTerm = max(blinnDir.dot( nearestIntersection.normal ), 0.0f);
              blinnTerm = pow(blinnTerm, 100) * 2.0f;
              Vector4f scalor(0.03f,0.03f,0.03f,1.0f);
              scalor *= 255;
              highlight += (highlight+ scalor) * blinnTerm;
            }
            color += highlight;
          }
        }

        // Reflection
        IntersectionInfo currentIntersection = nearestIntersection;
        Ray lastReflectionRay = currentRay;
        BaseObject* lastReflectingObject = intersectingObject;
        int depth = 1;
        while( depth > 0 )
        {
          float iDotN = 1*lastReflectionRay.direction.dot( currentIntersection.normal );
          float secondTerm = 2* iDotN;
          Vector3f reflectionDirection = lastReflectionRay.direction - currentIntersection.normal* secondTerm;
          Ray reflectionRay( currentIntersection.pointOfIntersection, reflectionDirection );
          IntersectionInfo reflectionInfo;
          BaseObject* reflectingObject = CastRayOnScene( reflectionRay, intersectingObject, reflectionInfo );
          if( reflectingObject != NULL )
          {
            color += reflectionInfo.diffuseColorOfObject*lastReflectingObject->GetRefletivity()*(depth)*0.1f;
          }
          else
          {
            color += Color(0,0,0,255)*lastReflectingObject->GetRefletivity();
            break;
          }
          lastReflectingObject = reflectingObject;
          lastReflectionRay = reflectionRay;
          currentIntersection = reflectionInfo;
          depth--;
        }
      }
      else
      {
        //color = Color( 0,0,0,255 );
      }

      glColor4f(color.r/255, color.g/255, color.b/255, color.w/255);
      glVertex2i(j, i);

    }
  }
  cout<<"Frame Done\n";
}

BaseObject* const RayTracer::CastRayOnScene( Ray& rayToCast, BaseObject* objToExlude, IntersectionInfo& outInfo )
{
  BaseObject* intersectingObject = NULL;
  float nearest = SCENE_MAX;
  list<BaseObject*>::iterator it;
  for( it = objects.begin(); it != objects.end(); ++it )
  {
    //perform some sort of bounding sphere optimization here
    BaseObject* obj = *it;
    if( obj == objToExlude )
      continue;

    IntersectionInfo info;
    if( obj->Intersect( rayToCast, info ) )
    {
      float dist = info.distOnRay;
      //if( fabs(dist) < 1000 )
      //cout<<"Dist: "<<dist<<"\n";
      if( fabs(dist) < nearest && fabs(dist) > 0.001f )
      {
        //cout<<"Point of int-- X: "<<info.pointOfIntersection.x<<", Y:"<<info.pointOfIntersection.y<<", Z:"<<info.pointOfIntersection.z<<"\n";
        intersectingObject = obj;
        nearest = fabs(dist);
        outInfo = info;
      }
    }
  }

  return intersectingObject;
}


