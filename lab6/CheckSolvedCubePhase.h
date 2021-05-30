#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class CheckSolvedCubePhase: public ISolutionPhase
{
public:
	CheckSolvedCubePhase(RuleEngine *engine, CubeModel* cubeModel);
	~CheckSolvedCubePhase(void);

	void solvePhase();
private:
	RuleEngine *ruleEngine;
	CubeModel* cube;
};

