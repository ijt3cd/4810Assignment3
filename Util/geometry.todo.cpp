#include <stdlib.h>
#include <math.h>

#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>

#include "geometry.h"

#include <iostream>
using namespace std;


///////////////////////
// Ray-tracing stuff //
///////////////////////
double BoundingBox3D::intersect(const Ray3D& ray) const {


	double txmin = (this->p[0].p[0] - ray.position.p[0]) / ray.direction.p[0]; 
    double txmax = (this->p[1].p[0] - ray.position.p[0]) / ray.direction.p[0]; 
 
    if (txmin > txmax) swap(txmin, txmax); 
 
    double tymin = (this->p[0].p[1] - ray.position.p[1]) / ray.direction.p[1]; 
    double tymax = (this->p[1].p[1] - ray.position.p[1]) / ray.direction.p[1]; 
 
    if (tymin > tymax) swap(tymin, tymax); 
 
    if ((txmin > tymax) || (tymin > txmax)) 
        return -1; 
 
    if (tymin > txmin) 
        txmin = tymin; 
 
    if (tymax < txmax) 
        txmax = tymax; 
 
    float tzmin = (this->p[0].p[2] - ray.position.p[2]) / ray.direction.p[2]; 
    float tzmax = (this->p[1].p[2] - ray.position.p[2]) / ray.direction.p[2]; 
 
    if (tzmin > tzmax) swap(tzmin, tzmax); 
 
    if ((txmin > tzmax) || (tzmin > txmax)) 
        return -1; 
 
    if (tzmin > txmin) 
        txmin = tzmin; 
 
    if (tzmax < txmax) 
        txmax = tzmax; 
 
 	if(txmax<0){
 		return 0;
 	}
    return 1; 


	// Plane3D xFront =  Plane3D(Point3D(1,0,0),this->p[0]);
	// Plane3D xBack  =  Plane3D(Point3D(-1,0,0),this->p[1]);

	// double  tx1 = -(ray.position.p[0]+xFront.distance)/ray.direction.p[0];
	// double  tx2 = (-ray.position.p[0]+xBack.distance)/ray.direction.p[0];

	


	// Point3D pos1 = ray.position + ray.direction.scale(tx1);
	// Point3D pos2 = ray.position + ray.direction.scale(tx2);



	// if(pos1.p[1]<=this->p[1].p[1]){
	// 	if (pos1.p[1]>=this->p[0].p[1]){
	// 		if (pos1.p[2]<=this->p[1].p[2]){
	// 			if (pos1.p[2]>=this->p[0].p[2]){

	// 				if(tx1<0){
	// 					if(tx2>0)
	// 					return 0;
	// 				}
	// 				return tx1;

	// 			}
	// 		}
	// 	}
	// }

	// if(pos2.p[1]<this->p[1].p[1]){
	// 	if (pos2.p[1]>this->p[0].p[1]){
	// 		if (pos2.p[2]<this->p[1].p[2]){
	// 			if (pos2.p[2]>this->p[0].p[2]){

	// 				if(tx2<0){
	// 					return -1;
	// 				}
					
	// 				return tx2;


	// 			}
	// 		}
	// 	}
	// }
		

	// return -1;
}

/////////////////////
// Animation stuff //
/////////////////////
Matrix3D::Matrix3D(const Point3D& e){
	(*this)=Matrix3D();
}

Matrix3D::Matrix3D(const Quaternion& q){
	(*this)=Matrix3D();
}
Matrix3D Matrix3D::closestRotation(void) const {
	return (*this);
}
/* While these Exp and Log implementations are the direct implementations of the Taylor series, the Log
 * function tends to run into convergence issues so we use the other ones:*/
Matrix3D Matrix3D::Exp(const Matrix3D& m,int iter){
	return m;
}
