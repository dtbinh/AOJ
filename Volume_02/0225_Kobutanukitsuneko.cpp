
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
typedef pair <P,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

int path[26][26];
int visited[26];

int dfs(int src,int* visited){
	visited[src] = 1;
	int res = 1;
	for(int i=0;i<26;i++){
		if(path[src][i] && visited[i] == 0){
			res += dfs(i,visited);
		}
	}
	return res;
}

int main(){
	int n;
	
	while(~scanf("%d",&n)){
		if(n==0) break;
		memset(path,0,sizeof(path));
		memset(visited,0,sizeof(visited));
		set<int> src;
		for(int i=0;i<n;i++){
			string str;
			cin >> str;
			path[*str.begin()-'a'][*(str.end()-1)-'a']++;

			src.insert(*(str.end()-1)-'a');
			src.insert(*str.begin()-'a');
		}
				
		if(src.size() != dfs(*src.begin(),visited)){
			printf("NG\n");
			continue;
		}

		bool isok=true;

		for(set<int>::iterator it = src.begin(); it != src.end(); it++){
			int out=0;
			for(int j=0;j<26;j++){
				out += path[*it][j];
			}

			int in=0;
			for(int j=0;j<26;j++){
				in += path[j][*it];
			}

			if(out != in) isok = false;
		}

		printf("%s\n",isok ? "OK" : "NG");
	}
}

