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
 
int Matsuzaki(int N,int P){
    vector<int> prime;
    for(int i=N+1;i<=N+100000;i++){
        if(isPrime[i]){
            prime.push_back(i);
            if(prime.size() >= 100) break;
        }
    }
 
    vector<int> compo;
    for(int i=0;i<prime.size();i++){
        for(int j=i;j<prime.size();j++){
            compo.push_back(prime[i]+prime[j]);
        }
    }
 
    sort(compo.begin(),compo.end());
    //unique(compo.begin(),compo.end());
 
    return compo[P-1];
}
 
int main(){
    int N,P;
    memset(isPrime,-1,sizeof(isPrime));
 
    isPrime[0] = false;
    isPrime[1] = false;
 
    for(int i=2;i<MAX_N;i++){
        if(!isPrime[i]) continue;
 
        for(int j=i+i;j<MAX_N;j+=i){
            isPrime[j] = false;
        }
    }
 
    while(~scanf("%d %d",&N,&P)){
        if(N==-1) break;
        printf("%d\n",Matsuzaki(N,P));
    }
}
