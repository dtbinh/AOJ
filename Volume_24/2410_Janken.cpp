
#define _USE_MATH_DEFINES
#define INF 100000000
 
#include <iostream>
#include <cstdio>
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
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
int judge_ai_hand;
 
int path[11][11];
 
int main(){
	int N;
	while(~scanf("%d",&N)){
		for(int y=0;y<N;y++){
			string str;
			cin >> str;
			for(int x=0;x<N;x++){
				if(str[x]=='o') path[y+1][x+1] = 3;
				if(str[x]=='-') path[y+1][x+1] = 1;
				else path[y+1][x+1] = 0;
			}
			
		}
 
		int good_hand = 1;
		int max_score = 0;
		for(int i=1;i<=N;i++){
			int score = 0;
			for(int j=0;j<1000;j++){
				int ai = rand() % N + 1;
				score += path[i][ai];
			}
 
			if(score >= max_score){
				max_score = score;
				good_hand = i;
			}
 
		}
 
 
		int score = 0;
		int decade = 0;
 
		int freq[11];
		memset(freq,0,sizeof(freq));
		for(int i=0;i<1000;i++){
			if(i!=0 && i%50==0){
				if((decade/(i/50))*20 < 350){
					int maxv = 0;
					for(int j=1;j<=N;j++){
						for(int k=1;k<=N;k++){
							if(maxv < path[j][k]*freq[k]){
								maxv = path[j][k]*freq[k];
								good_hand = j;
							}
						}
					}
				}
				decade = 0;
			}
			printf("%d\n",good_hand); fflush(stdout);
			scanf("%d", &judge_ai_hand);
			score += path[good_hand][judge_ai_hand];
			decade += path[good_hand][judge_ai_hand];
			freq[judge_ai_hand]++;
		}
		break;
	}
}


