// Copyright T.E.A de Souza 2012-2015 - MIT LICENSE

#include "ray3f.h"
//
#include <math.h>
#include "vecmath3f.h"

v3f r3fProject(const v3f* P,const ray3f* r){

	return v3fProjectPointOnLine(P, &r->origin, &r->direction);
	
}

v3f r3fIntersectPlane(const ray3f* ray,
					  const p3f* plane){
	
	v3f A = plane->origin;
	
	v3f B = plane->u;
	v3fAdd(&B, &A);
	
	v3f C = plane->v;
	v3fAdd(&C, &A);
	
	v3f P = ray->origin;
	v3f Q = ray->origin;
	v3fAdd(&Q, &ray->direction);
	
	v3f    u, v, n;             // triangle vectors
	v3f    dir, w0;          // ray vectors
	float  r, a, b;             // params to calc ray-plane intersect
	
	// get triangle edge vectors and plane normal
	
	u = v3fMake(&A,&B);
	v = v3fMake(&A,&C);
	
	qcross2(u,v,n);
	
	if (v3fIsZero(&n)){
		//rintf("triangle is degenerate");
		return v3fNaN();
	}
	
	dir	=	v3fMake(&P,&Q);
	w0	=	v3fMake(&P,&A);
	
	a = -dot(n,w0);
	b = dot(n,dir);
	
	if (fabs(b) < SMALL_NUM) {		// ray is parallel to triangle plane
		if (a == 0){                // ray lies in triangle plane
			return P;
			// this seems safer for our purpose.
			//return v3fNaN();
			//rintf("ray is inside the plane\n");
		}else{
			//rintf("ray is disjoint from the plane\n");
			return v3fNaN();        // ray disjoint from plane
		}
	}
	
	// get intersect point of ray with triangle plane
	
	r = a / b;
	if (r > 0 /* TOLERANCE */ ){                   // ray goes away from triangle
		//rintf("intersection is before P\n");
		return v3fNaN();           // => no intersect
	}
	// for a segment, also test if (r > 1.0) => no intersect
	
	// if(r<-1.0 /*-TOLERANCE*/ ){
	//	//rintf("intersection is beyond Q\n");
	//	return v3fNaN();
	//}
	
	// This is the intersection with the plane;
	
	v3f I = v3fDuplicate(dir);
	v3fMul(&I, -r);
	v3fAdd(&I, &P);
	
	return I;
	
}

/* origin: http://www.lighthouse3d.com/tutorials/maths/ray-sphere-intersection/ */
v3f r3fIntersectSphere(const ray3f* ray,
					   const sphere3f* s){
	
	v3f p = ray->origin;
	v3f d = ray->direction;
	
	v3f c = s->location;
	float r = s->radius;
	
	v3f vpc = v3fMake(&p,&c);
	
	if(dot(vpc, d) < 0 ){
		
		float L = v3fLength(&vpc);
		
		if(L>r){
			
			return v3fNaN();
			
		}else if(L == r){
			
			return p;
			
		}else{
			
			v3f pc = r3fProject(&c,ray);
			v3f cpc = v3fMake(&c, &pc);
			v3f ppc = v3fMake(&p, &pc);
			float cpcsq = v3fLength(&cpc); cpcsq*=cpcsq;
			
			float dist = sqrt(r*r - cpcsq);
			float di1 = dist - v3fLength(&ppc);
			
			v3f I = d;
			v3fMul(&I,di1);
			v3fAdd(&I,&p);
			
			return I;
			
		}
		
	}else{
		
		v3f pc = r3fProject(&c,ray);
		
		v3f pcc=v3fMake(&c,&pc);
		if(v3fLength(&pcc)>r){
			
			return v3fNaN();
			
		}else{
			
			v3f cpc = v3fMake(&c, &pc);
			float cpcsq = v3fLength(&cpc); cpcsq*=cpcsq;
			
			float dist = sqrt(r*r-cpcsq);
			
			float L = v3fLength(&vpc);
			
			float di1;
			
			v3f ppc = v3fMake(&p,&pc);
			float Lppc = v3fLength(&ppc);
			di1 = Lppc + ( L>r ? -dist : dist );
			
			v3f I = d;
			v3fMul(&I,di1);
			v3fAdd(&I,&p);
			
			return I;
			
		}
		
	}
	
}