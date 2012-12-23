
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
typedef pair<string,int> P;

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

void bfs(const string& goal,map<const string,int>& table){

	queue<P> que;
	que.push(P(goal,0));

	const int tx[] = {0,-1,0,1};
	const int ty[] = {1,0,-1,0};

	while(!que.empty()){
		string now = que.front().first;
		int c = que.front().second;
		que.pop();

		table[now] = c;

		int pos = now.find("0");

		//if(now[pos]==input[pos]) continue;
		int sx = pos % 4;
		int sy = pos / 4;
		for(int i=0;i<4;i++){

			int dx = (sx+tx[i]);
			int dy = (sy+ty[i]);

			if(dx < 0 || dx >=4 || dy < 0 || dy >=2) continue;
			string next = now;
			swap(next[pos],next[dy*4+dx]);

			if(table.find(next) == table.end()){
				que.push(P(next,c+1));
			}

			//cout << c+1 << " " << next << endl;
		}
	}

}


int main(){
	string str;
	string goal = "01234567";

	map<const string, int> table;

	bfs(goal,table);

	while(getline(cin,str)){
		string input = split(" ",str);
		cout << table[input] << endl;
	}
}



