
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
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-6;

class mycmp{
public:
	bool operator() (const P p1,const P p2){
		if(p1.second == p2.second) return p1.first < p2.first;
		else return p1.second > p2.second;
	}
};

vector<int> split(string delim,string str){
	vector<int> res;
	str += delim;
	for(int i=0;i<str.size();i++){
		for(int j=1;i+j<=str.size();j++){
			if(str.substr(i,j).find(delim) != string::npos){
				int num = atoi(str.substr(i,j-1).c_str());
				if(str.substr(i,j-1).size() >0 ) res.push_back(num);
				i+=j-1;
				break;
			}
		}
	}

	return res;
}

int main(){

	string str;
	while(getline(cin,str)){
		int n = atoi(str.c_str());
		if(n==0) break;

		vector<P> board;
		for(int t=0;t<n;t++){
			
			getline(cin,str);
			vector<int> data = split(" ",str);

			int num = data[0];
			int score = 0;
			for(int i=1,j=1;i<data.size();){
				if(j==10){
					if(data[i] == 10){
						score += data[i] + data[i+1] + data[i+2];
						i+=3;
					}

					else if(i+2< data.size() && data[i] + data[i+1] == 10){
						score += data[i] + data[i+1] + data[i+2];
						i+=3;
					}

					else if(i+1< data.size() && data[i] + data[i+1] < 10){
						score += data[i] + data[i+1];
						i+=2;
					}
				}

				else if(data[i] == 10) {
					score += 10;
					if(i+1 < data.size()) score += data[i+1];
					if(i+2 < data.size()) score += data[i+2];
					j++;
					i++;
				}
				else if(i+1< data.size() && data[i] + data[i+1] == 10){
					score += 10;
					if(i+1 < data.size()) score += data[i+2];
					j++;
					i+=2;
				}
				else if(i+1< data.size() && data[i] + data[i+1] < 10){
					score += data[i] + data[i+1];
					j++;
					i+=2;
				}

			}
			board.push_back(P(num,score));
		}

		sort(board.begin(),board.end(),mycmp());

		for(int i=0;i<board.size();i++){
			printf("%d %d\n",board[i].first,board[i].second);
		}
	}
}

