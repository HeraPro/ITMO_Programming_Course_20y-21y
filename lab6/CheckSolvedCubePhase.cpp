#include "RubikCubeController.h"

CheckSolvedCubePhase::CheckSolvedCubePhase(RuleEngine *engine, CubeModel* cubeModel)
{
	ruleEngine = engine;
	cube = cubeModel;
}


CheckSolvedCubePhase::~CheckSolvedCubePhase(void)
{
}

void CheckSolvedCubePhase::solvePhase()
{
	int find;

	while(ruleEngine->findPattern(SOLVEDCUBE) == -1)
	{
		find = ruleEngine->findPattern(FINISH);
		if(find == -1) find = ruleEngine->findPattern(FINISH_RESC);
		if(find != -1)
			ruleEngine->applySolution(find, 0);
	} 
}