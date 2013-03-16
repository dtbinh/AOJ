
#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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
#include <cctype>
#include <utility>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

static const double EPS = 1e-8;

int gSum = 0;
int key[24];

class Piece{
public:
	int pos[4];
	Piece(){
		memset(pos,0,sizeof(pos));
	}
};

bool check(char pos){
	if(pos == 0) return true;
	//012
	//345
	//678

	else if(pos==1){
		return (key[0] + key[1]==0);
	}

	else if(pos==2){
		return  (key[2] + key[3]==0);
	}

	else if(pos==3){
		return (key[4] + key[7]==0);
	}

	else if(pos==4){
		return ((key[5] + key[8]==0)
			&& (key[10] + key[11]==0));
	}
	else if(pos==5){
		return ((key[6] + key[9]==0)
			&& (key[12] + key[13]==0));
	}

	else if(pos==6){
		return (key[14] + key[17]==0);
	}

	else if(pos==7){
		return ((key[15] + key[18]==0)
			&& (key[20] + key[21]==0));
	}

	else if(pos==8){
		return ((key[16] + key[19]==0)
			&& (key[22] + key[23]==0));
	}
	else{
		return false;
	}
}

int dfs(char state,char puzzle[9][5],int visited){

	if(state==9){
		return 1;
	}

	int res = 0;

	for(int i=0;i<9;i++){
		if(visited & (1<<i)) continue;
		if(state==0){

			key[0] = puzzle[i][0];
			key[4] = puzzle[i][1];
			res += dfs(1,puzzle,visited | (1<<i));
			key[0] = puzzle[i][1];
			key[4] = puzzle[i][2];
			res += dfs(1,puzzle,visited | (1<<i));
			key[0] = puzzle[i][2];
			key[4] = puzzle[i][3];
			res += dfs(1,puzzle,visited | (1<<i));
			key[0] = puzzle[i][3];
			key[4] = puzzle[i][0];
			res += dfs(1,puzzle,visited | (1<<i));
		}
		else if(state==1){

			key[2] = puzzle[i][0];
			key[5] = puzzle[i][1];
			key[1] = puzzle[i][2];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[2] = puzzle[i][1];
			key[5] = puzzle[i][2];
			key[1] = puzzle[i][3];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[2] = puzzle[i][2];
			key[5] = puzzle[i][3];
			key[1] = puzzle[i][0];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[2] = puzzle[i][3];
			key[5] = puzzle[i][0];
			key[1] = puzzle[i][1];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));
		}
		else if(state==2){  
			key[6] = puzzle[i][0];
			key[3] = puzzle[i][1];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[6] = puzzle[i][1];
			key[3] = puzzle[i][2];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[6] = puzzle[i][2];
			key[3] = puzzle[i][3];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[6] = puzzle[i][3];
			key[3] = puzzle[i][0];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));
		}
		else if(state==3){

			key[7] = puzzle[i][0];
			key[10] = puzzle[i][1];
			key[14] = puzzle[i][2];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[7] = puzzle[i][1];
			key[10] = puzzle[i][2];
			key[14] = puzzle[i][3];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[7] = puzzle[i][2];
			key[10] = puzzle[i][3];
			key[14] = puzzle[i][0];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[7] = puzzle[i][3];
			key[10] = puzzle[i][0];
			key[14] = puzzle[i][1];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));
		}
		else if(state==4){
			key[8] = puzzle[i][0];
			key[12] = puzzle[i][1];
			key[15] = puzzle[i][2];
			key[11] = puzzle[i][3];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[8] = puzzle[i][1];
			key[12] = puzzle[i][2];
			key[15] = puzzle[i][3];
			key[11] = puzzle[i][0];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[8] = puzzle[i][2];
			key[12] = puzzle[i][3];
			key[15] = puzzle[i][0];
			key[11] = puzzle[i][1];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[8] = puzzle[i][3];
			key[12] = puzzle[i][0];
			key[15] = puzzle[i][1];
			key[11] = puzzle[i][2];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));
		}
		else if(state==5){
			key[16] = puzzle[i][0];
			key[13] = puzzle[i][1];
			key[9] = puzzle[i][2];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[16] = puzzle[i][1];
			key[13] = puzzle[i][2];
			key[9] = puzzle[i][3];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[16] = puzzle[i][2];
			key[13] = puzzle[i][3];
			key[9] = puzzle[i][0];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[16] = puzzle[i][3];
			key[13] = puzzle[i][0];
			key[9] = puzzle[i][1];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

		}
		else if(state==6){
			key[17] = puzzle[i][0];
			key[20] = puzzle[i][1];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[17] = puzzle[i][1];
			key[20] = puzzle[i][2];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[17] = puzzle[i][2];
			key[20] = puzzle[i][3];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[17] = puzzle[i][3];
			key[20] = puzzle[i][0];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));
		}
		else if(state==7){
			key[21] = puzzle[i][0];
			key[18] = puzzle[i][1];
			key[22] = puzzle[i][2];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[21] = puzzle[i][1];
			key[18] = puzzle[i][2];
			key[22] = puzzle[i][3];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[21] = puzzle[i][2];
			key[18] = puzzle[i][3];
			key[22] = puzzle[i][0];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[21] = puzzle[i][3];
			key[18] = puzzle[i][0];
			key[22] = puzzle[i][1];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));
		}
		else if(state==8){
			key[23] = puzzle[i][0];
			key[19] = puzzle[i][1];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[23] = puzzle[i][1];
			key[19] = puzzle[i][2];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[23] = puzzle[i][2];
			key[19] = puzzle[i][3];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));

			key[23] = puzzle[i][3];
			key[19] = puzzle[i][0];
			if(check(state)) res += dfs(state+1,puzzle,visited | (1<<i));
		}
	}
	return res;
}

char table[256];

int main(){
	int n;

	table['r'] = 1;
	table['g'] = 2;
	table['b'] = 3;
	table['w'] = 4;
	table['R'] = -1;
	table['G'] = -2;
	table['B'] = -3;
	table['W'] = -4;

	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){

			char puzzle[9][5];
			char buf[5];
			for(int j=0;j<9;j++){

				scanf("%s",buf);
				for(int k=0;k<4;k++){
					puzzle[j][k] = table[buf[k]];
				}
			}

			printf("%d\n",dfs(0,puzzle,0));
		}
	}
}


