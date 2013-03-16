
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

P move(char** stage){
	set<P> visited;
	int c=1;
	int x=0,y=0;

	visited.insert(P(x,y));

	while(1){
		if(stage[y][x] == '>') x++;
		else if(stage[y][x] == '^') y--;
		else if(stage[y][x] == '<') x--;
		else if(stage[y][x] == 'v') y++;
		else if(stage[y][x] == '.') break;

		visited.insert(P(x,y));
		if(++c != visited.size()) return P(-1,-1);
	}

	return P(x,y);
}

int main(){

	string str;
	int h,w;
	while(getline(cin,str)){
		sscanf(str.c_str(),"%d %d",&h,&w);
		if(h==w && h==0) break;

		char** stage = new char*[h];
		for(int i=0;i<h;i++) stage[i] = new char[w];

		for(int y=0;y<h;y++){
			getline(cin,str);
			for(int x=0;x<w;x++){
				stage[y][x] = str[x];
			}
		}

		P pos = move(stage);

		if(pos.first == -1 && pos.second == -1) cout << "LOOP" << endl;
		else printf("%d %d\n",pos.first,pos.second);

		for(int i=0;i<h;i++) delete[] stage[i];
		delete[] stage;
	}
}

