
#define _USE_MATH_DEFINES
#define INF 10000000
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
#include <bitset>
#include <list>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

struct DICE{
	int top;
	int bottom;
	int lhs;
	int rhs;
	int front;
	int rear;
};

int main(){
	
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		int sum=1;
		DICE dice = {1,6,4,3,2,5};
		for(int i=0;i<n;i++){
			char buf[32];
			scanf("%s",buf);
			switch(buf[0]){
			case 'N':{
				//bot2fro
				//fro2top
				//top2rear
				//rear2bot
				int bottom = dice.bottom;
				int front = dice.front;
				int top = dice.top;
				int rear = dice.rear;
				dice.bottom = rear;
				dice.front = bottom;
				dice.top = front;
				dice.rear = top;
				sum += dice.top;
				break;
					 }
			case 'S':{
				int bottom = dice.bottom;
				int front = dice.front;
				int top = dice.top;
				int rear = dice.rear;
				dice.bottom = front;
				dice.front = top;
				dice.top = rear;
				dice.rear = bottom;
				sum += dice.top;
				break;
					 }
			case 'W':{
				int bottom = dice.bottom;
				int top = dice.top;
				int lhs = dice.lhs;
				int rhs = dice.rhs;
				dice.bottom = lhs;
				dice.top = rhs;
				dice.lhs = top;
				dice.rhs = bottom;
				sum += dice.top;
				break;
					 }
			case 'E':{
				int bottom = dice.bottom;
				int top = dice.top;
				int lhs = dice.lhs;
				int rhs = dice.rhs;
				dice.bottom = rhs;
				dice.top = lhs;
				dice.lhs = bottom;
				dice.rhs = top;
				sum += dice.top;
				break;
					 }
			case 'R':{
				int lhs = dice.lhs;
				int rhs = dice.rhs;
				int front = dice.front;
				int rear = dice.rear;
				dice.lhs = front;
				dice.rhs = rear;
				dice.front = rhs;
				dice.rear = lhs;
				sum += dice.top;
				break;
					 }
			case 'L':{
				int lhs = dice.lhs;
				int rhs = dice.rhs;
				int front = dice.front;
				int rear = dice.rear;
				dice.lhs = rear;
				dice.rhs = front;
				dice.front = lhs;
				dice.rear = rhs;
				sum += dice.top;
				break;
					 }
			default:
				break;
			}
		}
		printf("%d\n",sum);
	}
}

