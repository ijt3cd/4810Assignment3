#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v,Point3D n){
	return (v-n.scale(2*v.dot(n))).unit();
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
	
	double irMult = ir;

	if (ir == 1){
		cout<<"plz"<<endl;
		irMult == 1/ir;
	}
	//double irMult = 1;

	double cosi = -n.unit().dot(v.unit());

	if((1-pow(ir,2)*(1-pow(cosi,2)))<0){
		return 0;
	}

	double cosr = sqrt(1-pow(ir,2)*(1-pow(cosi,2)));

	refract = (n.unit().scale((irMult*cosi-cosr)) - v.unit().scale(irMult)).unit().negate();
	

	

	return 1;
}

Ray3D RayScene::GetRay(RayCamera* camera,int i,int j,int width,int height){
	Ray3D* retRay = new Ray3D();
	float d = 1;
	float h = 2 * d * tan(0.5*camera->heightAngle);
	float w = h * camera->aspectRatio;
	float u = -w/2.0 + w * ((i+0.5)/width);
	float v = -h/2.0 + h * ((j+0.5)/height);
	Point3D* dir = new Point3D((camera->direction).scale(d)+(camera->right).scale(u)+(camera->up).scale(v));
	*dir = dir->unit();
	retRay->direction = *dir;
	retRay->position = camera->position;
	return *retRay;
}

Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit){

	
	struct RayIntersectionInfo iInfo;
	struct RayIntersectionInfo tempInfo;

	double emEx = (group->intersect(ray,iInfo,-1));
	if(emEx>0){
		Point3D* addedLights = new Point3D(0,0,0);
		
		int k = 0;

		for (int i = 0; i < lightNum; ++i)
		{
			*addedLights=*addedLights+lights[i]->getDiffuse(ray.position,iInfo);
			*addedLights=*addedLights+lights[i]->getSpecular(ray.position,iInfo);
			*addedLights=*addedLights*(lights[i]->isInShadow(iInfo,group,k));
		}
		Point3D intensity = *addedLights+ iInfo.material->emissive+iInfo.material->ambient*ambient;




		Point3D reflVect = Reflect(ray.direction,iInfo.normal);
		Ray3D reflRay = Ray3D(iInfo.iCoordinate+reflVect.scale(0.001),reflVect);

		if(rDepth>0){
			if(iInfo.material->specular.p[0] > cLimit.p[0]){
				if(iInfo.material->specular.p[1] > cLimit.p[1]){
					if(iInfo.material->specular.p[2] > cLimit.p[2]){
						intensity = intensity + GetColor(reflRay,rDepth-1,cLimit/(iInfo.material->specular))*iInfo.material->specular;
					}
				}
			}	
		}

//////////////////////




//////////////////////////////////////////////////////////
		// Point3D refrVect;
		// Refract(ray.direction.unit(),iInfo.normal.unit(),iInfo.material->refind,refrVect);
	
		
		

		// Ray3D refrRay = Ray3D(iInfo.iCoordinate+refrVect.scale(0.001),refrVect.unit());
		
	
		// if(rDepth>0){
		// 	if(iInfo.material->transparent.p[0] > cLimit.p[0]){
		// 		if(iInfo.material->transparent.p[1] > cLimit.p[1]){
		// 			if(iInfo.material->transparent.p[2] > cLimit.p[2]){
		// 				intensity = intensity + GetColor(refrRay,rDepth-1,cLimit/(iInfo.material->transparent))*iInfo.material->transparent;
		// 			}
		// 		}
		// 	}
		// }
	
		

		


		if(intensity[0]<0){
			intensity[0]=0;
		}
		if(intensity[0]>1){
			intensity[0]=1;
		}

		if(intensity[1]<0){
			intensity[1]=0;
		}
		if(intensity[1]>1){
			intensity[1]=1;
		}

		if(intensity[2]<0){
			intensity[2]=0;
		}
		if(intensity[2]>1){
			intensity[2]=1;
		}

		return intensity;
	}

	return background;
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
