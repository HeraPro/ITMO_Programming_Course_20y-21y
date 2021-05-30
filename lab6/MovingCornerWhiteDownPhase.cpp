#include "RubikCubeController.h"

MovingCornerWhiteDownPhase::MovingCornerWhiteDownPhase(RuleEngine* engine, CubeModel* cubeModel)
{
	ruleEngine = engine;
	cube = cubeModel;
}


MovingCornerWhiteDownPhase::~MovingCornerWhiteDownPhase(void)
{
}

void MovingCornerWhiteDownPhase::solvePhase()
{
	int iter = 0;
	while(ruleEngine->findPattern(PATTERN_PHASE3) == -1)
	{
		executeAll();
		iter++;
		if(iter >5) return;
	}
}

void MovingCornerWhiteDownPhase::executeAll() 
{
	int find;
	int i,j,old,m;
	int find2;
	if(ruleEngine->findPattern(PATTERN_PHASE2) == -1) 
	{
		getRubikCubeController()->setWarning("Second phase (prerequisite) is not complete. Please extend rule base to cover this situation.");
		return;
	}
	
	for(old=0; old!=4; old++)
	{
		find2 = ruleEngine->findPattern(CORNERWHITE_TO_BOTTOM);
		if(find2!=-1)
			ruleEngine->applySolution(find2, 0);

		for(j=0; j!=5; j++)
		{
			find = ruleEngine->findPattern(WHITE_TO_BOTTOM_POS);
			if(find != -1) 
				ruleEngine->applySolution(find, 0);

			cube->getTransformEngine()->cTransform("6j");
		}
	}
}