
#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
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
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
int main(){
 
    int n,k,m;
 
    while(~scanf("%d %d %d",&n,&k,&m)){
        if(n==0) break;
 
        vector<int> nums;
        for(int i=1;i<=n;i++){
            nums.push_back(i);
        }
 
        int pos = m-1;
 
        while(nums.size() > 1){
            nums.erase(nums.begin()+pos);
            pos--;
            pos = (pos + k) % nums.size();
        }
 
        printf("%d\n",nums[0]);
    }
}

