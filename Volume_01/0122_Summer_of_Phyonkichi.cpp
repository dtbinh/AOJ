
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
typedef pair<int,int> P;
typedef pair<P,int> PP;

string split(string delim,string str){
	string res="";
	str += delim;
	for(int i=0;i<str.size();i++){
		for(int j=1;i+j<=str.size();j++){
			if(str.substr(i,j).find_first_of(delim) != string::npos){
				//cout << str.substr(i,j) << endl;
				if(str.substr(i,j-1).size() > 0 ){
					int num;
					sscanf(str.substr(i,j-1).c_str(),"%d",&num);
					res+=num+'0';
					//res.push_back(str.substr(i,j-1));

				}
				i+=j-1;
				break;
			}
		}
	}

	return res;
}

bool bfs(queue<P> fountain,int x,int y){
	int size = fountain.size();
	int c=0;
	const int t[][2] = {{-1,-2},{0,-2},{1,-2},{2,-1},{2,0},{2,1},{1,2},{0,2},{-1,2},{-2,-1},{-2,0},{-2,1}};
	int visited[10][10];
	memset(visited,0,sizeof(visited));

	queue<PP> pyon;
	pyon.push(PP(P(x,y),0));

	int upper = 0;
	//bool isok = false;
	while(!fountain.empty()){
		int fx = fountain.front().first;
		int fy = fountain.front().second;
		fountain.pop();
		bool isok = false;
		while(!pyon.empty()){
			int px = pyon.front().first.first;
			int py = pyon.front().first.second;
			c = pyon.front().second;
			if(c == size) goto found;

			if(upper == c) pyon.pop();
			else { upper++; memset(visited,0,sizeof(visited)); break; }
			
			for(int i=0;i<12;i++){
				int dx = px + t[i][0];
				int dy = py + t[i][1];

				if(dx < 0 || dx > 9 || dy < 0 || dy > 9) continue;
				if((fx-1 <= dx && dx <= fx+1) && (fy-1 <= dy && dy <= fy+1)){
					if(visited[dy][dx] == 1) continue;					
					pyon.push(PP(P(dx,dy),c+1));
					visited[dy][dx] = 1;
					//printf("x:%d y:%d c:%d\n",dx,dy,c);
					isok=true;
				}
			}
		}
		if(!isok) break;
	}
found:;
	return c>=size && fountain.empty() ? true : false;
}


int main(){
	string str;
	int px,py;
	while(~scanf("%d %d",&px,&py)){
		if(px == 0 && py == 0) break;
		int n;
		scanf("%d",&n);
		queue<P> fountain;
		for(int i=0;i<n;i++){
			int x,y;
			scanf("%d %d",&x,&y);
			fountain.push(P(x,y));
		}

		printf("%s\n",bfs(fountain,px,py) ? "OK" : "NA");
	}
}


