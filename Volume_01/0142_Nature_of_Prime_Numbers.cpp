
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
typedef pair<double,int> P;

static const double eps = 10e-9;

int main(){
	int n;

	while(~scanf("%d",&n)){
		if(n==0) break;

		vector<int> input;
		for(int i=1;i<=n-1;i++){
			input.push_back((i*i)%n);
		}

		int* table = new int[(n-1)/2+1]();

		sort(input.begin(),input.end());

		vector<int>::iterator end_it = unique(input.begin(),input.end());
		input.erase(end_it,input.end());

		for(int i=0;i<input.size();i++){
			for(int j=0;j<input.size();j++){
				if(i==j) continue;
				int calc = input[i]-input[j] ;
				if(calc < 0) calc+=n;
				if(calc > (n-1)/2) calc = n - calc;

				table[calc]++;
			}
		}

		for(int i=1;i<(n-1)/2+1;i++){
			printf("%d\n",table[i]);
		}

		delete[] table;
	}
}

