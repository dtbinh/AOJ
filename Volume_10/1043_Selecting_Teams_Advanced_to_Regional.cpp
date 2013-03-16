
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

class Team{
public:
	int id;
	int univ;
	int success;
	int penalty;

	Team() : id(0),univ(0),success(0),penalty(0){}
	Team(int id,int univ,int success,int penalty){
		this->id = id;
		this->univ = univ;
		this->success = success;
		this->penalty = penalty;
	}
};

class mycmp{
public:
	bool operator()(const Team t1,const Team t2){
		if(t1.success == t2.success
			&& t1.penalty == t2.penalty){
				return (t1.id < t2.id);
		}
		else if(t1.success == t2.success){
			return (t1.penalty < t2.penalty);
		}

		return (t1.success > t2.success);
	}
};

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		vector<Team> teams;
		for(int i=0;i<n;i++){
			int ID,U,A,P;
			scanf("%d %d %d %d",&ID,&U,&A,&P);
			teams.push_back(Team(ID,U,A,P));
		}

		map<int,bool> passedTeam;
		map<int,int> univCount;
		sort(teams.begin(),teams.end(),mycmp());
		for(int i=0;i<teams.size();i++){
			if(passedTeam.size() < 10){
				if(univCount[teams[i].univ] < 3){
					univCount[teams[i].univ]++;
					passedTeam[teams[i].id] = true;
					printf("%d\n",teams[i].id);
				}
			}
			else if(passedTeam.size() < 20){
				if(univCount[teams[i].univ] < 2){
					univCount[teams[i].univ]++;
					passedTeam[teams[i].id] = true;
					printf("%d\n",teams[i].id);
				}
			}
			else if(passedTeam.size() < 26){
				if(univCount[teams[i].univ] < 1){
					univCount[teams[i].univ]++;
					passedTeam[teams[i].id] = true;
					printf("%d\n",teams[i].id);
				}
			}
		}
	}
}


