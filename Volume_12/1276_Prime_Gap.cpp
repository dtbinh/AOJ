
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
 
bool isPrime[1299709+1];
 
int main(){
 
    memset(isPrime,-1,sizeof(isPrime));
    isPrime[0] = false;
    isPrime[1] = false;
 
    vector<int> prime;
    for(int i=2;i<=1299709;i++){
        if(isPrime[i]){
            prime.push_back(i);
            for(int j=i+i;j<=1299709;j+=i){
                isPrime[j] = false;
            }
        }
    }
    int n;
 
    while(~scanf("%d",&n)){
        if(n==0) break;
        if(isPrime[n]){
            printf("%d\n",0);
        }
 
        else{
            vector<int>::iterator it = lower_bound(prime.begin(),prime.end(),n);
            printf("%d\n",*it - *(it-1));
        }
    }
}

