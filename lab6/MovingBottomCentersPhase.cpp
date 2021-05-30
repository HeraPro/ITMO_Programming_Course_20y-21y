#include "RubikCubeController.h"


MovingBottomCentersPhase::MovingBottomCentersPhase(RuleEngine *engine, CubeModel* cubeModel)
{
	ruleEngine = engine;
	cube = cubeModel;
}


MovingBottomCentersPhase::~MovingBottomCentersPhase(void)
{
}

void MovingBottomCentersPhase::solvePhase()
{
	int iter=0;

	while(ruleEngine->findPattern(PATTERN_PHASE5) == -1)
	{
		executeAll();
		iter++;
		if(iter>5) return;
	}
}

void MovingBottomCentersPhase::executeAll()
{
	int s;
	int i,j;

	if(ruleEngine->findPattern(PATTERN_PHASE5) != -1) return;
	for(j=0; j!=10; j++)
	{
		for(i=0; i!=10; i++)
		{
			s = ruleEngine->findPattern(BOTTOM1);
			if(s!=-1)
			{
				ruleEngine->applySolution(s, 0);
				if(ruleEngine->findPattern(PATTERN_PHASE5) != -1)
				{
					return;
				}
			}
		}
		cube->getTransformEngine()->cTransform("6j");
	}
}