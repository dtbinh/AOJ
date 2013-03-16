
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
 
int dp[10001];
bool isPrime[10001];
 
int main(){
    memset(isPrime,-1,sizeof(isPrime));
    isPrime[0] = false;
    isPrime[1] = false;
    for(int i=2;i*i<=10000;i++){
        if(isPrime[i]){
            for(int j=i+i;j<=10000;j+=i){
                isPrime[j]=false;
            }
        }
    }
 
    vector<int> prime;
    for(int i=2;i<=10000;i++){
        if(isPrime[i]){
            prime.push_back(i);
        }
    }
 
    int n;
 
    while(~scanf("%d",&n)){
        if(n==0) break;
 
        memset(dp,0,sizeof(dp));
 
        for(int i=0;i<prime.size();i++){
            if(prime[i] > n) break;
            for(int j=i;j<prime.size();j++){
                int sum = 0;
                for(int k=i;k<j;k++){
                    sum += prime[k];
                }
                if(sum > n) break;
                dp[sum]++;
            }
        }
 
        printf("%d\n",dp[n]);
    }
}

