#include "BodyBasics.h"
#include <iostream>
#include <Windows.h>
using namespace std;


int main(){
	CBodyBasics application;
	application.Run();
	while (true)
	{
		float x = application.SkeletPointsXY(11).x;
		float z = application.DepthSkeletonPoints(11);

		cout << x << "  " << z << "\n";

		Sleep(100);
	} 
}