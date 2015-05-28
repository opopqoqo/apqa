
#include "triangle3us.h"

bool t3usIsContiguous(const triangle3us* A,
					  const triangle3us* B){

	for(int i=0;i<3;i++){
	
		for(int j=0;j<3;j++){
		
			if(A->data[i]==B->data[j]) return true;
			
		}
		
	}return false;
	
}