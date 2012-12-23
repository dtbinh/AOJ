
#define _USE_MATH_DEFINES
#define INF 100000000
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

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

int students[100][100];

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		for(int y=0;y<n;y++){
			for(int x=0;x<n;x++){
				scanf("%d",&students[y][x]);
			}
		}

		map<P,int> table;
		vector<int>* row_low = new vector<int>[n];
		for(int y=0;y<n;y++){
			int minv = numeric_limits<int>::max();

			for(int x=0;x<n;x++){
				if(minv > students[y][x]){
					minv = students[y][x];
					row_low[y].clear();
					row_low[y].push_back(x);
				}
				else if(minv == students[y][x]){
					row_low[y].push_back(x);
				}
			}

			for(int i=0;i<row_low[y].size();i++){
				table[P(row_low[y][i],y)]++;
			}
		}

		vector<int>* col_high = new vector<int>[n];
		for(int x=0;x<n;x++){
			int maxv = numeric_limits<int>::min();

			for(int y=0;y<n;y++){
				if(maxv < students[y][x]){
					maxv = students[y][x];
					col_high[x].clear();
					col_high[x].push_back(y);
				}
				else if(maxv == students[y][x]){
					col_high[x].push_back(y);
				}
			}

			for(int i=0;i<col_high[x].size();i++){
				table[P(x,col_high[x][i])]++;
			}
		}

		int maxv = 0;
		for(int x=0;x<n;x++){
			for(int y=0;y<n;y++){
				if(table[P(x,y)]==2){
					maxv = max(students[y][x],maxv);
				}
			}
		}

		printf("%d\n",maxv);
	}
}

