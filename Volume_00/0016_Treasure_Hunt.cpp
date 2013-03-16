
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int main()
{	
	double posX=0;
	double posY=0;
	double angle=90;
	string str;
	while(getline(cin,str,',')){
		string str2;
		getline(cin,str2);

		int a,b;
		sscanf(str.c_str(),"%d",&a);
		sscanf(str2.c_str(),"%d",&b);

		if(a==0 && b==0) break;

		posX -= a * sin(M_PI/2.0 -angle/180.0*M_PI);
		posY += a * cos(M_PI/2.0 -angle/180.0*M_PI);

		angle += b;	
	}
	printf("%.0f\n%.0f\n",floor(posX),ceil(posY));
}

