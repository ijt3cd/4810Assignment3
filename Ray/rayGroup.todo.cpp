#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"
#include <iostream>
using namespace std;

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	struct RayIntersectionInfo tempInfo;
	double s=(getInverseMatrix().multDirection(ray.direction).length())/(ray.direction.length());


	if(mx>0){
		
		mx=mx*s;
	}
	ray.position=getInverseMatrix().multPosition(ray.position);
	ray.direction=getInverseMatrix().multDirection(ray.direction).unit();
	bool is_hit = false;


	if(bBox.intersect(ray)!=0){
	for (int i = 0; i < sNum; ++i)
	{

		// if(shapes[i]->bBox.intersect(ray)>0){
		// 	if(shapes[i]->bBox.intersect(ray)<mx||mx<0){
				float mxTest = shapes[i]->intersect(ray,tempInfo,mx);

				if(mxTest>0&&(mxTest<mx||mx<0)){
					is_hit = true;
					mx = mxTest;
					iInfo = tempInfo;
				}	
	}
		// 	}
		// }

}
		


	// }

	
	if (is_hit) {
		iInfo.iCoordinate = getMatrix().multPosition(iInfo.iCoordinate);
		iInfo.normal = getNormalMatrix().multDirection(iInfo.normal).unit();
	} else {
		return -1;
	}

	if(mx>0){
		mx=mx/s;
	}
	return mx;
}

BoundingBox3D RayGroup::setBoundingBox(void){



	for (int i = 0; i < sNum; ++i)
	{
		bBox+=shapes[i]->setBoundingBox();
	}


	return bBox;
}

int StaticRayGroup::set(void){

	inverseTransform = localTransform.invert();
	normalTransform = Matrix4D(Matrix3D(localTransform).transpose().invert());


	return 1;
}
//////////////////
// OpenGL stuff //
//////////////////	
int RayGroup::getOpenGLCallList(void){
	return 0;
}

int RayGroup::drawOpenGL(int materialIndex){
	return -1;
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
