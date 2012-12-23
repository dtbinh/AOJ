
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double eps = 1e-8;

int main(){
	char table[5][5];
	while(~scanf("%s",table)){
		if(table[0][0] == '0') break;
		for(int i=1;i<=2;i++){
			scanf("%s",table+i);
		}

		int winner=0;
		for(int i=0;i<3;i++){
			int w=0,b=0;
			for(int j=0;j<3;j++){
				if(table[i][j] == 'w') w++;
				if(table[i][j] == 'b') b++;
			}
			if(w==3) winner = 1;
			if(b==3) winner = -1;
		}

		for(int i=0;i<3;i++){
			int w=0,b=0;
			for(int j=0;j<3;j++){
				if(table[j][i] == 'w') w++;
				if(table[j][i] == 'b') b++;
			}
			if(w==3) winner = 1;
			if(b==3) winner = -1;
		}

		if(table[0][0] == table[1][1]
		&& table[1][1] == table[2][2]
		&& table[2][2] =='w') winner = 1;

		if(table[0][0] == table[1][1]
		&& table[1][1] == table[2][2]
		&& table[2][2] =='b') winner = -1;

		if(table[0][2] == table[1][1]
		&& table[1][1] == table[2][0]
		&& table[2][0] =='w') winner = 1;

		if(table[0][2] == table[1][1]
		&& table[1][1] == table[2][0]
		&& table[2][0] =='b') winner = -1;

		printf("%s\n", winner == 1 ? "w" : winner == -1 ? "b" : "NA");

	}
}

