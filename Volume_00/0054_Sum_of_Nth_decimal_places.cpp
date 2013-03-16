
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
 
    int a,b,n;
    while(~scanf("%d %d %d",&a,&b,&n)){
        double num = (double)a/(double)b;
        int sum = 0;
        for(int i=1;i<=n;i++){
            num *= 10.0;
            ll tmp = (ll)(num + EPS);
            num -= (double)tmp;
            sum += tmp % 10;        
        }
 
        printf("%d\n",sum);
    }
}

