
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
 
static const double EPS = 1e-8;
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
 
        int atk[20];
        for(int i=0;i<n;i++){
            scanf("%d",atk+i);
        }
 
        int diff=numeric_limits<int>::max();
        for(int S=0;S<=(1<<n)-1;S++){
            int sumA=0;
            int sumB=0;
            for(int i=0;i<n;i++){
                if(S & (1<<i)) sumA+=atk[i];
                else sumB+=atk[i];
            }
            diff = min(diff,abs(sumA-sumB));
        }
 
        printf("%dn",diff);
    }
}

