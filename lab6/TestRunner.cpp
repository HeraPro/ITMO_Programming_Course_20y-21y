#include "RubikCubeController.h"
#include <time.h>

#ifdef MODE_COMMAND_LINE

using namespace std;

int main() 
{
	// Init
	//string uniqueId = random_string(12);
	getRubikCubeController()->getCube()->DefaultColors();

	// Random rotate
	srand (time(NULL));
	for (int i=0; i!=50; i++) {
		getRubikCubeController()->getCube()
			->getTransformEngine()->stopRotating();         // to register cTransform

		getRubikCubeController()->setStepCount(0);                // collecting graphical movements from 0 index
		int random = rand()%16;
		getRubikCubeController()->getCube()->getTransformEngine()->cTransformN(random);  // random transformation saved to history
	}

	// Save cube in file
	writeCubeIntoFile("cube-initial.txt");

	// Solve cube in memory
	getRubikCubeController()->saveCubeColors();                // save current cube. solutionStrategy will do transformations on it
	getRubikCubeController()->setStepCount(0);                 // start step count from zero
	getRubikCubeController()->setRotatingStep(0);
	getRubikCubeController()->getCube()
		->getTransformEngine()->stopRotating();          // no graphical movements allowed
				
	if(getSolutionStrategy()->run())                          // solve cube. this will make transformations on current cube
	{
		getRubikCubeController()->getCube()->getTransformEngine()->startRotating();      // graphics movements are allowed
		printf("Cube solved in %d steps", getRubikCubeController()->getStepCount());

		// Save solved cube in file
		writeCubeIntoFile("cube-solved.txt");
	} else {
		printf("Cube could not be soleved");
	}
	
	// Exit
	getRubikCubeController()->shutDown(); 
}

void writeCubeIntoFile(string filename)
{
	ofstream outfile(filename.c_str());
	string cubeAsString =  getRubikCubeController()->getCube()->ToString();
	printf("Writing cube into file: %s\n%s", filename.c_str(), cubeAsString.c_str());
	outfile << cubeAsString;
	outfile.close();
}
//
//std::string random_string(size_t length)
//{
//    auto randchar = []() -> char
//    {
//        const char charset[] =
//        "0123456789"
//        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//        "abcdefghijklmnopqrstuvwxyz";
//        const size_t max_index = (sizeof(charset) - 1);
//        return charset[ rand() % max_index ];
//    };
//    std::string str(length,0);
//    std::generate_n( str.begin(), length, randchar );
//    return str;
//}

#endif
