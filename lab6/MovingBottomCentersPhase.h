#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingBottomCentersPhase: public ISolutionPhase
{
public:
	MovingBottomCentersPhase(RuleEngine* engine, CubeModel* cubeModel);
	~MovingBottomCentersPhase(void);

	void solvePhase();
	void executeAll();

private:
	CubeModel* cube;
	RuleEngine* ruleEngine;
};

