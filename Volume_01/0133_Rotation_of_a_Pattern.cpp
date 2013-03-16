
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>

using namespace std;

typedef long long ll;
typedef pair<char,int> P;

static const double eps = 10e-9;

void rotate90(char input[8][8], char output[8][8])
{
	for(int y=0;y<8;y++){
		for(int x=0;x<8;x++){
			double dx = x*cos(M_PI/2.0) - y*sin(M_PI/2.0) + 7;
			double dy = x*sin(M_PI/2.0) + y*cos(M_PI/2.0);

			output[(int)(dy+eps)][(int)(dx+eps)]=input[y][x];
		}
	}
}

void rotate180(char input[8][8], char output[8][8])
{
	for(int y=0;y<8;y++){
		for(int x=0;x<8;x++){
			double dx = x*cos(M_PI) - y*sin(M_PI) + 7;
			double dy = x*sin(M_PI) + y*cos(M_PI) + 7;
			output[(int)(dy+eps)][(int)(dx+eps)]=input[y][x];
		}
	}
}

void rotate270(char input[8][8], char output[8][8])
{
	for(int y=0;y<8;y++){
		for(int x=0;x<8;x++){
			double dx = x*cos(3.0*M_PI/2.0) - y*sin(3.0*M_PI/2.0);
			double dy = x*sin(3.0*M_PI/2.0) + y*cos(3.0*M_PI/2.0) + 7;

			output[(int)(dy+eps)][(int)(dx+eps)]=input[y][x];
		}
	}
}

void printStage(char stage[8][8])
{
	for(int y=0;y<8;y++){
		for(int x=0;x<8;x++){
			printf("%c%s",stage[y][x],x==7 ? "\n" : "");
		}
	}
}




int main(){

	double eps = 10e-9;
	char stage[8][8];
	for(int y=0;y<8;y++){
		string str;
		getline(cin,str);
		for(int x=0;x<8;x++){
			stage[y][x] = str[x];
		}
	}

	char res[8][8];
	rotate90(stage,res);
	cout << 90 << endl;
	printStage(res);

	rotate180(stage,res);
	cout << 180 << endl;
	printStage(res);

	rotate270(stage,res);
	cout << 270 << endl;
	printStage(res);
}

