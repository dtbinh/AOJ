
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>

typedef long long ll;
using namespace std;

typedef pair<int,int> P;

int main()
{
	string str;
	int rect_num=0;
	int diam_num=0;
	int edge1, edge2, diag;
	while(~scanf("%d,%d,%d",&edge1,&edge2,&diag)){

		if(edge1 + edge2 <= diag) continue;

		if(edge1*edge1 + edge2*edge2 == diag * diag){
			rect_num++;
		}
		else if(edge1 == edge2){
			diam_num++;
		}
	}

	printf("%d\n%d\n",rect_num,diam_num);
}

