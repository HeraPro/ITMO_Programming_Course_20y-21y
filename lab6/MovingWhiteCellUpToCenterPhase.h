#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"
#include "RuleEngine.h"

class MovingWhiteCellUpToCenterPhase: public ISolutionPhase
{
public:
	MovingWhiteCellUpToCenterPhase(RuleEngine *engine, CubeModel* cubeModel);
	~MovingWhiteCellUpToCenterPhase(void);
	void solvePhase();

private:
	RuleEngine* ruleEngine;
	CubeModel* cube;
};

