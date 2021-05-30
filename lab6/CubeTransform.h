#pragma once

#ifndef _CUBETRANSFORM_H_INCLUDED_
#define _CUBETRANSFORM_H_INCLUDED_

#include <string>

// forward declaration
class CubeModel; 

class CubeTransform
{
	public:
		CubeTransform(void* cubeModel);
		void startRotating();
		void stopRotating(); 
		int getRotating();
		void setRotated(int rot);
		int getRotated();
		void cTransformN(int n);
		void cTransform(char *id);	

	private:
		CubeModel* cube;
		int rotated;
		int showRotating;
};

#endif