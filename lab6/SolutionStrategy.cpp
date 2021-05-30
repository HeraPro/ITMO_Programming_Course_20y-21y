#include "RubikCubeController.h"

using namespace std;

SolutionStrategy::SolutionStrategy(RuleEngine *engine, CubeModel* cubeModel)
{
	ruleEngine = engine;
	cube = cubeModel;
}

int SolutionStrategy::run()
{
	std::list<ISolutionPhase*> solutionPhases;
	solutionPhases.push_back(new MovingWhiteCellUpToCenterPhase(ruleEngine, cube));
	solutionPhases.push_back(new MovingTopCornersPhase(ruleEngine, cube));
	solutionPhases.push_back(new MovingCornerWhiteDownPhase(ruleEngine, cube));
	solutionPhases.push_back(new MovingSideCentersPhase(ruleEngine, cube));
	solutionPhases.push_back(new MovingBottomCentersPhase(ruleEngine, cube));
	solutionPhases.push_back(new MovingBottomCornersPhase(ruleEngine, cube));
	solutionPhases.push_back(new CheckSolvedCubePhase(ruleEngine, cube));
	
	for (std::list<ISolutionPhase*>::const_iterator iterator = solutionPhases.begin(), end = solutionPhases.end(); iterator != end; ++iterator) {
		ISolutionPhase* currentPhase = *iterator;
		currentPhase->solvePhase();
	}

	if(ruleEngine->findPattern(PATTERN_PHASE5) == -1) return 0;

	return 1;
}
