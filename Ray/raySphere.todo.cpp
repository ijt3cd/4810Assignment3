#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySphere.h"
#include <iostream>
using namespace std;

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){

	double tPlus = -1;
	double tMinus = -1;
	Point3D unitDir = ray.direction.unit();
	double a = 1;
	double b = 2*unitDir.dot(ray.position-center);
	double c = (ray.position-center).dot(ray.position-center) - pow(radius,2);

	

	if(pow(b,2)-4*a*c>=0){
		tPlus = (-b+pow(pow(b,2)-4*a*c,0.5))  /(2*a);
		tMinus = (-b-pow(pow(b,2)-4*a*c,0.5)) /(2*a);
	}
	

	
	if((tMinus>0)) {
		if (mx < 0 || (tMinus < mx)) {
			Point3D p = ray.position+unitDir.scale(tMinus);
			Point3D normal = (p-center)/(p-center).length();
			iInfo.material = material;
			iInfo.iCoordinate = p;
			iInfo.normal = normal.unit();
			return tMinus;
		} else {
			return -1;
		}
	}
	if((tPlus>0)) { 
		if (mx < 0 || (tPlus < mx)) {
			Point3D p = ray.position+unitDir.scale(tPlus);
			Point3D normal = (p-center)/(p-center).length();
			iInfo.material = material;
			iInfo.iCoordinate = p;
			iInfo.normal = normal.unit();


			return tPlus;
		} else {
			return -1;
		}
	}
	

	return -1;
}
BoundingBox3D RaySphere::setBoundingBox(void){

	bBox = BoundingBox3D(center-Point3D(radius,radius,radius),center+Point3D(radius,radius,radius));




	return bBox;
}
	
//////////////////
// OpenGL stuff //
//////////////////
int RaySphere::drawOpenGL(int materialIndex){
	return -1;
}
