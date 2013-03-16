
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
 
 
bool isPrime[10001];
 
int main(){
 
    memset(isPrime,1,sizeof(isPrime));
 
    isPrime[0] = false;
    isPrime[1] = false;
    for(int i=2;i*i<=10000;i++){
        if(isPrime[i]){
            for(int j=i+i;j<=10000;j+=i){
                isPrime[j] = false;
            }
        }
    }
 
    int N;
    while(~scanf("%d",&N)){
        int res=0;
        for(int i=1,j=N;i<=N;i++,j--){
            if(isPrime[i] && isPrime[j]) res++;
        }
 
        printf("%dn",res);
    }
}

