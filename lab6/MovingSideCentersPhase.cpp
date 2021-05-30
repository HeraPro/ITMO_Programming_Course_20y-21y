#include "RubikCubeController.h"


MovingSideCentersPhase::MovingSideCentersPhase(RuleEngine* engine, CubeModel* cubeModel)
{
	ruleEngine = engine;
	cube = cubeModel;
}

MovingSideCentersPhase::~MovingSideCentersPhase(void)
{
}

void MovingSideCentersPhase::solvePhase()
{
	int iter=0;

	while(ruleEngine->findPattern(PATTERN_PHASE4) == -1)
	{
		executeAll();
		iter++;
		if(iter>5) return;
	}
}

void MovingSideCentersPhase::executeAll()
{
	int h;
	int find;
	int iteration;
	for(iteration=0; iteration!=15; iteration++)
	{

		if(ruleEngine->findPattern(PATTERN_PHASE3) == -1)
		{
			getRubikCubeController()->setWarning("Phase 3 (prerequisite) failed");
			return;
		}
		
		find = ruleEngine->findPattern(BIGT_SMALLT);
		if(find != -1) 
		{
			if(rules[find].elofeltetel[0] != RESCUE) 
			{
				h = 0;
				ruleEngine->applySolution(find, 0);
			} else 
			{
				h++;
				cube->getTransformEngine()->cTransform("6j");
				if(h>4) {
					ruleEngine->applySolution(find, 0);
					h = 0;
				}

			}
		}
		else 
		{
			cube->getTransformEngine()->cTransform("6j");
		}
		
		if(ruleEngine->findPattern(PATTERN_PHASE4) == -1)
			getRubikCubeController()->setWarning("Phase 4 failed");
	}
}
