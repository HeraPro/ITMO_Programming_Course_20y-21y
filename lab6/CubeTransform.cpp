#include "RubikCubeController.h"

CubeTransform::CubeTransform(void* cubeModel)
{
	cube = reinterpret_cast<CubeModel*>(cubeModel);

	rotated = 0;
	showRotating = 0;
}

void CubeTransform::cTransformN(int n)
{
	char retval[6];
	switch(n)
	{
		case 0: sprintf(retval, "1j"); break;
		case 1: sprintf(retval, "1b"); break;
		case 2: sprintf(retval, "2j"); break;
		case 3: sprintf(retval, "2b"); break;
		case 4: sprintf(retval, "3j"); break;
		case 5: sprintf(retval, "3b"); break;
		case 6: sprintf(retval, "4j"); break;
		case 7: sprintf(retval, "4b"); break;
		case 8: sprintf(retval, "5j"); break;
		case 9: sprintf(retval, "5b"); break;
		case 10: sprintf(retval, "6j"); break;
		case 11: sprintf(retval, "6b"); break;
		case 12: sprintf(retval, "7j"); break;
		case 13: sprintf(retval, "7b"); break;
		case 14: sprintf(retval, "8j"); break;
		case 15: sprintf(retval, "8b"); break;
		case 16: sprintf(retval, "9j"); break;
		case 17: sprintf(retval, "9b"); break;
	}

	cTransform(retval);
}

void CubeTransform::setRotated(int rot) 
{
	rotated = rot;
}

int CubeTransform::getRotated() 
{
	return rotated;
}

void CubeTransform::startRotating() 
{
	showRotating = 1;
}

void CubeTransform::stopRotating() 
{
	showRotating = 0;
}

int CubeTransform::getRotating() 
{
	return showRotating;
}

void CubeTransform::cTransform(char *id)
{
	if(!showRotating) getRubikCubeController()->cAddQueue(id);

	CubeModel tempCube;

	int transid=-1;
	if(strcmp(id, "1j") == 0) transid = 0;
	else if(strcmp(id, "1b") == 0) transid = 1;
	else if(strcmp(id, "2j") == 0) transid = 2;
	else if(strcmp(id, "2b") == 0) transid = 3;
	else if(strcmp(id, "3j") == 0) transid = 4;
	else if(strcmp(id, "3b") == 0) transid = 5;
	else if(strcmp(id, "4j") == 0) transid = 6;
	else if(strcmp(id, "4b") == 0) transid = 7;
	else if(strcmp(id, "5j") == 0) transid = 8;
	else if(strcmp(id, "5b") == 0) transid = 9;
	else if(strcmp(id, "6j") == 0) transid = 10;
	else if(strcmp(id, "6b") == 0) transid = 11;
	else if(strcmp(id, "7j") == 0) transid = 12;
	else if(strcmp(id, "7b") == 0) transid = 13;
	else if(strcmp(id, "8j") == 0) transid = 14;
	else if(strcmp(id, "8b") == 0) transid = 15;
	else if(strcmp(id, "9j") == 0) transid = 16;
	else if(strcmp(id, "9b") == 0) transid = 17;

	if(showRotating == 1) 
	{	
		getRubikCubeController()->rotateColorSide(transid);
	}
	
	int side, cellId;
	for(side=1; side!=7; side++) {
		for(cellId=1; cellId!=10; cellId++) {
			tempCube.SetCellColor(side, cellId, cube->GetCellColor(side, cellId));
		}
	}

	int i=0;
	int tside, tplace, sside, splace;
	while(CubeTransformData::cubeTransform[transid].steps[i].target_side != -1)
	{
		if(CubeTransformData::cubeTransform[transid].steps[i].target_side != -1)
		{
			tside = CubeTransformData::cubeTransform[transid].steps[i].target_side;
			tplace = CubeTransformData::cubeTransform[transid].steps[i].target_place;
			sside = CubeTransformData::cubeTransform[transid].steps[i].source_side;
			splace = CubeTransformData::cubeTransform[transid].steps[i].source_place;

			cube->SetCellColor(tside, tplace, tempCube.GetCellColor(sside, splace));
		}
		i++;
	}
}

