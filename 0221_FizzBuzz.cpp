
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
typedef pair <int,P > PP;

static const double eps = 1e-8;

bool check(int i,string str){

	string ans;
	if(i%15==0) ans = "FizzBuzz";
	else if(i%3==0) ans = "Fizz";
	else if(i%5==0) ans = "Buzz";
	else{
		char buf[128];
		sprintf(buf,"%d",i);
		ans = buf;
	}

	return (ans == str);
}

int main(){
	int m,n;
	while(~scanf("%d %d",&m,&n)){
		if(m==n && n==0) break;
		list<int> player;
		for(int i=1;i<=m;i++) player.push_back(i);

		int alive = m;
		for(int i=0,j=0;i<n;i++){		
			string str;
			cin >> str;
			if(alive>1 && !check(i+1,str)){
				list<int>::iterator it = player.begin();
				advance(it,j);
				player.erase(it);
				alive--;
			}
			else j++;

			j %= alive;
		}

		for(list<int>::iterator it = player.begin(); it != player.end(); it++){
			printf("%s%d",it == player.begin() ? "" : " ",*it);
		}
		printf("\n");
	}
}

