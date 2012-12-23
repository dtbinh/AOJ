
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
typedef pair <int,P> PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
class Data{
public:
    string term;
    int freq;
    Data (string _term, int _freq){
        term = _term;
        freq = _freq;
    }
    bool operator<(const Data& d) const{
        if(freq == d.freq) return term < d.term;
        else{
            return freq > d.freq;
        }
    }
};
 
vector<string> split(string delim,string str){
    vector<string> res;
    str += delim;
    for(int i=0;i<str.size();i++){
        for(int j=1;i+j<=str.size();j++){
            if(str.substr(i,j).find(delim) != string::npos){
                if(str.substr(i,j-1).size() > 0 ) res.push_back(str.substr(i,j-1));
                i+=j-1;
                break;
            }
        }
    }
 
    return res;
}
 
int main(){
    ios::sync_with_stdio(false);
 
    int n;
    string str;
 
    while(cin>>n,n){
        //n=str[0]-'0';
        //if(n==0) break;
        cin.ignore();
 
        map<string,int> freq;
        map<char,vector<string> > dict;
 
        for(int i=0;i<n;i++){
            getline(cin,str);
            stringstream ss(str);
 
            string s;
            while(ss >> s){
                freq[s]++;
            }       
        }
 
        getline(cin,str);
 
        vector<Data> data;
        for(map<string,int>::iterator it = freq.begin(); it != freq.end(); it++){
            if(it->first[0] == str[0]) data.push_back(Data(it->first,it->second));
        }
 
        if(data.size()==0){
            cout << "NA" << "\n";
        }
 
        else{
            sort(data.begin(),data.end());
 
            for(int i=0;i<data.size() && i < 5;i++){
                if(i!=0) cout << " ";
                cout << data[i].term;
            }
            cout << "\n";
        }
    }
}

