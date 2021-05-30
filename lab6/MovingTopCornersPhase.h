#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingTopCornersPhase: public ISolutionPhase
{
public:
	MovingTopCornersPhase(RuleEngine* engine, CubeModel* cubeModel);
	~MovingTopCornersPhase(void);
	void solvePhase();

private:
	void executeAll();
	int executeBottom();
	CubeModel* cube;
	RuleEngine* ruleEngine;
};

