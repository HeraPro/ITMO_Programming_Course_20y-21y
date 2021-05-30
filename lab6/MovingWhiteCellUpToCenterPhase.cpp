#include "RubikCubeController.h"

MovingWhiteCellUpToCenterPhase::MovingWhiteCellUpToCenterPhase(RuleEngine *engine, CubeModel* cubeModel)
{
	ruleEngine = engine;
	cube = cubeModel;
}


MovingWhiteCellUpToCenterPhase::~MovingWhiteCellUpToCenterPhase(void)
{
}

void MovingWhiteCellUpToCenterPhase::solvePhase() 
{
	int i;
	
	for(i=1; i!=7; i++)
	{
		if((int)cube->GetCellColor(i, 5).Red == 1 &&
			(int)cube->GetCellColor(i, 5).Green == 1 &&
			(int)cube->GetCellColor(i, 5).Blue == 1)
		{
			switch(i)
			{
			case 1: cube->getTransformEngine()->cTransform("7j"); break;
			case 2: cube->getTransformEngine()->cTransform("8j"); break;
			case 3: cube->getTransformEngine()->cTransform("7b"); break;
			case 4: cube->getTransformEngine()->cTransform("8b"); break;
			case 5: break;
			case 6: 
				cube->getTransformEngine()->cTransform("8b");
				cube->getTransformEngine()->cTransform("8b");
				break;	
			}
			return;
		}
	}
}