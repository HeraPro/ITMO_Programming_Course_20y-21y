#!/bin/bash
# Test script for RubikCube.exe
#
# RubikCube.exe should be compiled with "#define MODE_COMMAND_LINE" directive to avoid OpenGL 
# animation, and get application results in output files (cube-initial.txt is the randomly 
# rotated cube, and cube-solved.txt is the solved cube, if program runs normally)

echo "Running tests ..."

while [ true ]
do
    echo "Cleaning up previous run results"
    
    # Cleanup
    rm *.txt
    ./RubikCube.exe
    
    # Increment run count
    runCount=`cat stats-runcount`
    failCount=`cat stats-failcount`
    newCount=`expr $runCount + 1`
    echo $newCount > "stats-runcount"
    
    # Process results
    if [ -f "cube-solved.txt" ];
    then
	echo "Cube solved"
    else
	failCount=`cat stats-failcount`
	newFailCount=`expr $failCount + 1`
	echo $newFailCount > "stats-failcount"
	mv cube-initial.txt "fail-cases/cube-initial-$failCount.txt"
    fi;
    
    failureRate=`expr $failCount \* 100 / $runCount`
    echo "Run Count: $runCount, Fail Count: $failCount, Failure rate: $failureRate%"
    
    # Waiting one second to save processor time
    sleep 1;
done