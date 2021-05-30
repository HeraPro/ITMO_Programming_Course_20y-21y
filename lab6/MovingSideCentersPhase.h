#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingSideCentersPhase: public ISolutionPhase
{
public:
	MovingSideCentersPhase(RuleEngine* engine, CubeModel* cubeModel);
	~MovingSideCentersPhase(void);

	void solvePhase();
	void executeAll();

private:
	CubeModel* cube;
	RuleEngine* ruleEngine;
};

