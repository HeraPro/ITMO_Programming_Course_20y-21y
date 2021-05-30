#include "RubikCubeController.h"

RuleEngine::RuleEngine(CubeModel* cubeModel)
{
	cube = cubeModel;
}

int RuleEngine::rulesLen()
{
	int i = 0;
	while(rules[i].group != ENDRULE) i++;
	return i;
}

int RuleEngine::checkPattern(int n)
{
	int i=0;
	double pseudoColor[10][4];
	int pseudoC=0;
	int checkSide = 0;


	while(rules[n].patt[i].side != -1)
	{
		if(rules[n].patt[i].side == -1) return 1;
		if(rules[n].patt[i].side == OLDAL) checkSide = 0;
		else checkSide = rules[n].patt[i].side;

		if((cube->GetCellColor(checkSide, rules[n].patt[i].place).Red == rules[n].patt[i].r) &&
			(cube->GetCellColor(checkSide, rules[n].patt[i].place).Green == rules[n].patt[i].g) &&
			(cube->GetCellColor(checkSide, rules[n].patt[i].place).Blue == rules[n].patt[i].b))
		{
			
		} else 
		{
			if(rules[n].patt[i].r > 1.0)
			{
				if(rules[n].patt[i].r == 100.0) 
				{
					i++;
					continue;
				}

				int exists = 0;
				int j, index;
				
				for(j=0; j!=pseudoC; j++)
					if(pseudoColor[j][3] == rules[n].patt[i].r) 
					{ 
						exists=1; index=j; 
					
					}
				

				if(!exists)
				{
					int k;
					for(k=0; k!=pseudoC; k++)
					{
						if((pseudoColor[k][0] == cube->GetCellColor(checkSide, rules[n].patt[i].place).Red) &&
							(pseudoColor[k][1] == cube->GetCellColor(checkSide, rules[n].patt[i].place).Green) &&
							(pseudoColor[k][2] == cube->GetCellColor(checkSide, rules[n].patt[i].place).Blue))
						{ return 0; }


					}
					pseudoColor[pseudoC][0] = cube->GetCellColor(checkSide, rules[n].patt[i].place).Red;
					pseudoColor[pseudoC][1] = cube->GetCellColor(checkSide, rules[n].patt[i].place).Green;
					pseudoColor[pseudoC][2] = cube->GetCellColor(checkSide, rules[n].patt[i].place).Blue;
					pseudoColor[pseudoC][3] = rules[n].patt[i].r;
					pseudoC++;
				} else
				{
					if((cube->GetCellColor(checkSide, rules[n].patt[i].place).Red == pseudoColor[index][0]) &&
						(cube->GetCellColor(checkSide, rules[n].patt[i].place).Green == pseudoColor[index][1]) &&
						(cube->GetCellColor(checkSide, rules[n].patt[i].place).Blue == pseudoColor[index][2]))
					{
					
					} else return 0;

				}
			} else 
			{
				return 0; 
			}
		}
		
		i++;
	}
	
	return 1;
}


void RuleEngine::applySolution(int n, int rotnum)
{
	char cmd[16];
	int i=0;
	int grr=0;
	while(rules[n].sol[i].side != -1)
	{
		grr=0;
		if(rules[n].sol[i].side == -1) return;
		sprintf(cmd, "%d%s", rules[n].sol[i].side, rules[n].sol[i].rotate);
		cube->getTransformEngine()->cTransform(cmd);			
		i++;
	}
	return;
}

int RuleEngine::findPattern(int code)
{
	int i;
	for(i=0; i!=rulesLen(); i++)
	{
		if(rules[i].group == code)
		{
			if(checkPattern(i)) return i;
		}
	}
	return -1;
}
