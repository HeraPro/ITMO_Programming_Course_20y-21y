#include "RubikCubeController.h"

MovingTopCornersPhase::MovingTopCornersPhase(RuleEngine* engine, CubeModel* cubeModel)
{
	ruleEngine = engine;
	cube = cubeModel;
}


MovingTopCornersPhase::~MovingTopCornersPhase(void)
{
}

void MovingTopCornersPhase::solvePhase()
{
	int iter = 0;
	while(ruleEngine->findPattern(PATTERN_PHASE2) == -1) 
	{
		executeAll();

		iter++;
		if(iter > 5) return;
	}
}

void MovingTopCornersPhase::executeAll() 
{
	int j,i,k;
	for(j=0; j!=4; j++)
	{
		if(executeBottom()) continue;
		for(i=0; i!=ruleEngine->rulesLen();  i++)
		{
			if(rules[i].group == WHITE_TO_BOTTOM)
			{
				if(ruleEngine->checkPattern(i)) 
				{	
					ruleEngine->applySolution(i, 0);
					int k;
					for(k=0; k!=4; k++)
					{
						if(executeBottom()) break;
						cube->getTransformEngine()->cTransform("6j");
					}
				}
			}
		}
	}

	for(i=0; i!=ruleEngine->rulesLen(); i++)
	{
		if(rules[i].group == PATTERN_PHASE2) 
			if(!ruleEngine->checkPattern(i)) getRubikCubeController()->setWarning("Error: phase 2 was not successful. Rule set should be extended to cover this situation.");
	}
}

int MovingTopCornersPhase::executeBottom() 
{
	int i=0;
	for(i=0; i!=ruleEngine->rulesLen(); i++)
	{
		if(rules[i].group == PATTERN_CROWN_MOVEUP)
		{
			if(ruleEngine->checkPattern(i))
			{
				char buff[256];
				sprintf(buff, "%d true", i);
				getRubikCubeController()->setWarning(buff);
				ruleEngine->applySolution(i,0);
				return 1; 
			} else getRubikCubeController()->setWarning("");
		}
	}
	return 0; 
}