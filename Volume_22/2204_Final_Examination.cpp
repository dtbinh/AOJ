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
 
static const int MAX_N = 1000000;
bool isPrime[MAX_N];
 
int main(){
    int n;
 
    while(~scanf("%d",&n)){
        if(n==0) break;
        vector<int> nums;
        for(int i=0;i<n;i++){
            int sum=0;
            for(int j=0;j<5;j++){
                int p;
                scanf("%d",&p);
                sum += p;
            }
            nums.push_back(sum);        
        }
        sort(nums.begin(),nums.end());
        printf("%d %d\n",*(nums.end()-1),*nums.begin());
    }
}
