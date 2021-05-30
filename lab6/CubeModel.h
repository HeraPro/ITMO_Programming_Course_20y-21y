#pragma once

#ifndef _CUBEMODEL_H_INCLUDED_
#define _CUBEMODEL_H_INCLUDED_

#include "CubeTransform.h"

using namespace std;

class CubeModel
{
	public:
		struct CubeColor
		{
			double Red;
			double Green;
			double Blue;

			string ToString() {
				string cubeColorStr;
				cubeColorStr.append("R=").append(to_string(Red)).append(" G=").append(to_string(Green)).append(" B=").append(to_string(Blue));
				return cubeColorStr;
			}
		};

		CubeModel(void);
		void DefaultColors();
		void SetCellColor(int side, int cellId, const CubeColor color);
		CubeColor GetCellColor(int side, int cellId);
		CubeTransform* getTransformEngine(void);
		string ToString(void);
		~CubeModel(void);

	private: 
		CubeColor cubeColors[7][10];
		CubeTransform* transformEngine;
};

#endif
