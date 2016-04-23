#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"
#include <iostream>
using namespace std;

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void){
}
double RayTriangle::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){

	Point3D normal = v[0]->normal.unit();

	Point3D vOne = v[0]->position-ray.position;
	Point3D vTwo = v[1]->position-ray.position;
	Point3D vThree = v[2]->position-ray.position;
	Point3D nOne = vTwo.crossProduct(vOne);
	Point3D nTwo = vThree.crossProduct(vTwo);
	Point3D nThree = vOne.crossProduct(vThree);

	double t = -ray.position.dot(normal)/(ray.direction.dot(normal));


	Point3D p = ray.position+ray.direction.scale(t);

	Point3D pCheck = p-ray.position;

	if (t < 0 || (mx > 0 && t > mx)) {
		return -1;
	}

	if(pCheck.dot(nOne)>=0){
		if(pCheck.dot(nTwo)>=0){
			if(pCheck.dot(nThree)>=0){

				iInfo.material = material;
				iInfo.iCoordinate = p;
				iInfo.normal = normal;
				

				return t;
			}
		}
	}


	return -1;
}
BoundingBox3D RayTriangle::setBoundingBox(void){

	
	double minX = v[0]->position[0];
	for (int i = 0; i < 3; ++i)
	{
		if(v[i]->position[0]<minX){
			minX = v[i]->position[0];
		}
	}
	double minY = v[0]->position[1];
	for (int i = 0; i < 3; ++i)
	{
		if(v[i]->position[1]<minY){
			minY = v[i]->position[1];
		}
	}
	double minZ = v[0]->position[2];
	for (int i = 0; i < 3; ++i)
	{
		if(v[i]->position[2]<minZ){
			minZ = v[i]->position[2];
		}
	}
	double maxX = v[0]->position[0];
	for (int i = 0; i < 3; ++i)
	{
		if(v[i]->position[0]>maxX){
			maxX = v[i]->position[0];
		}
	}
	double maxY = v[0]->position[1];
	for (int i = 0; i < 3; ++i)
	{
		if(v[i]->position[1]>maxY){
			maxY = v[i]->position[1];
		}
	}
	double maxZ = v[0]->position[2];
	for (int i = 0; i < 3; ++i)
	{
		if(v[i]->position[2]>maxZ){
			maxZ = v[i]->position[2];
		}
	}

	bBox = BoundingBox3D(Point3D(minX,minY,minZ),Point3D(maxX,maxY,maxZ));



	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	return -1;
}
