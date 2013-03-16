
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
#include <cctype>
#include <utility>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
const int tx[] = {0,1,0,-1};
const int ty[] = {1,0,-1,0};
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
 
        vector<int> score;
        for(int i=0;i<n;i++){
            int s;
            scanf("%d",&s);
            score.push_back(s);
        }
 
        sort(score.begin(),score.end());
 
        int sum=0;
        for(int i=1;i<score.size()-1;i++){
            sum += score[i];
        }
 
        printf("%d\n",sum/(score.size()-2));
    }
}

