#include <math.h>
#include <GL/glut.h>
#include "rayPointLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayPointLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){

	Point3D direction = location - iInfo.iCoordinate;
	Point3D d = iInfo.iCoordinate-location;
	Point3D i = color/(Point3D(constAtten,constAtten,constAtten)+d.scale(linearAtten)+(d*d).scale(quadAtten));
	// return iInfo.material->diffuse.scale(iInfo.normal.dot(direction))*i;

	if(iInfo.normal.dot(direction.negate())>0){
		return iInfo.material->diffuse.scale(iInfo.normal.dot(direction.negate()))*i;
	}
	else{
		return Point3D(0,0,0);
	}
}
Point3D RayPointLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	
	Point3D direction = location - iInfo.iCoordinate;
	Point3D d = iInfo.iCoordinate-location;
	Point3D i = color/(Point3D(constAtten,constAtten,constAtten)+d.scale(linearAtten)+(d*d).scale(quadAtten));

	double n=iInfo.material->specularFallOff;
	Point3D r = direction.unit().negate() + iInfo.normal.unit().scale(2*(iInfo.normal.unit().dot(direction.unit())));

	if( iInfo.normal.unit().dot(direction.unit().negate()) > 0 ) {
		return iInfo.material->specular.scale(pow((cameraPosition-iInfo.iCoordinate).unit().dot(r.unit().negate()),n))*i;
	}

	return Point3D(0,0,0);
}
int RayPointLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	struct RayIntersectionInfo infoCopy;
	infoCopy = iInfo;
	Point3D direction = iInfo.iCoordinate - location;
	Ray3D* checkRay = new Ray3D(infoCopy.iCoordinate+direction.negate().unit().scale(0.001),direction.negate().unit());

	double mx = shape->intersect(*checkRay,infoCopy);

	if(mx>=0){
		return 0;
	}
	else{
		return 1;
	}
}
Point3D RayPointLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}


//////////////////
// OpenGL stuff //
//////////////////
void RayPointLight::drawOpenGL(int index){
}
 