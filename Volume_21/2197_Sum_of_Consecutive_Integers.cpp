
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
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        int count = 0;
        for(int i=1;i<=n;i++){
 
            int sum = 0;
            for(int j=i;j<=n;j++){
                sum += j;
                if(sum == n && j!=i) count++;
                if(sum >=n) break;
            }
        }
 
        printf("%d\n",count);
    }
}

