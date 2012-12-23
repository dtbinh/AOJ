
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
 
        int S = 0;
        for(int i=1;i*i<=n;i++){
            if(n % i == 0 && i != n){
                S+=i;
                if(n/i != i && n/i != n) S+=n/i;
            }
        }
         
        if(S < n){
            printf("deficient number\n");
        }
        else if(S==n){
            printf("perfect number\n");
        }
        else{
            printf("abundant number\n");
        }
    }
}

