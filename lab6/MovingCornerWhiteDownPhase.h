#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingCornerWhiteDownPhase: public ISolutionPhase
{
public:
	MovingCornerWhiteDownPhase(RuleEngine* engine, CubeModel* cubeModel);
	~MovingCornerWhiteDownPhase(void);

	void solvePhase();
	void executeAll();

private:
	CubeModel* cube;
	RuleEngine* ruleEngine;
};

