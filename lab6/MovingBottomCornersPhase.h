#pragma once

#include "isolutionphase.h"

class MovingBottomCornersPhase: public ISolutionPhase
{
public:
	MovingBottomCornersPhase(RuleEngine* engine, CubeModel* cubeModel);
	~MovingBottomCornersPhase(void);

	void solvePhase();
	double sarokChkSum(int num);
	double sarokPosChkSum(int num);

private:
	RuleEngine* ruleEngine;
	CubeModel* cube;
};

