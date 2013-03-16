
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;


int main(){
	double eps = 10e-9;
	
	int N;
	scanf("%d",&N);

	for(int n=0;n<N;n++){
		string str;
		cin >> str;
		vector<int> tmp;
		for(int i=0;i<str.size();i++){
			tmp.push_back(str[i]-'0');
		}
		sort(tmp.begin(),tmp.end());

		int a=0;
		for(int i=tmp.size()-1;i>=0;i--){
			a += tmp[i] * (pow(10,(double)i) + eps);
		}

		int b=0;
		sort(tmp.begin(),tmp.end(),greater<int>());
		for(int i=tmp.size()-1;i>=0;i--){
			b += tmp[i] * (pow(10,(double)i) + eps);
		}
		cout << a-b << endl;
	}

}


