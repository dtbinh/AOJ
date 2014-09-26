#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
#include <assert.h>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;

class Deal {
public:
  string _dealer_name;
  string _type;
  string _commodity_name;
  int _price;
  int _id;
  Deal(string dealer_name,string type,string commodity_name,int price,int id) 
    : _dealer_name(dealer_name), _type(type), _commodity_name(commodity_name), _price(price), _id(id) {}
};

class DealerResult {
public:
  int _paid;
  int _received;
  DealerResult() : _paid(0),_received(0) {}
};

class CommodityResult {
public:
  int _lowest;
  int _mean;
  int _highest;
  vector<int> _purchase_history;
  void init(){
    if(_purchase_history.size() > 0){
      sort(_purchase_history.begin(),_purchase_history.end());
      _highest = *(_purchase_history.end()-1);
      _lowest = *(_purchase_history.begin());
      
      int sum = 0;
      for(int i=0;i<_purchase_history.size();i++){
	sum += _purchase_history[i];
      }
      _mean = sum / _purchase_history.size();
    }
  }
  CommodityResult() : _lowest(0), _mean(0), _highest(0) {}
};

int main(){
  int total_dealers;
  while(~scanf("%d",&total_dealers)){
    if(total_dealers == 0) break;

    vector<Deal> deals;
    for(int dealer_i = 0; dealer_i < total_dealers; dealer_i++){
      string dealer_name,type,commodity_name;
      int price;
      cin >> dealer_name >> type >> commodity_name >> price;
      deals.push_back(Deal(dealer_name,type,commodity_name,price,dealer_i));
    }

    bool used[1001];
    memset(used,false,sizeof(used));

    map<string,CommodityResult> commodity_result;
    map<string,DealerResult> dealer_result;

    for(int dealer_i = 0; dealer_i < total_dealers; dealer_i++){
      dealer_result[deals[dealer_i]._dealer_name] = DealerResult();
    }

    for(int dealer_i = 0; dealer_i < total_dealers; dealer_i++){
      if(used[dealer_i]) continue;
      int current_sell_price = INF; // lowest
      int current_buy_price = -INF; // highest
      int target_id = -1;

      for(int dealer_j = 0; dealer_j < total_dealers; dealer_j++){
	if(dealer_i == dealer_j) continue;
	if(used[dealer_j]) continue;
	if(deals[dealer_i]._type == deals[dealer_j]._type) continue;
	if(deals[dealer_i]._dealer_name == deals[dealer_j]._dealer_name) continue;
	if(deals[dealer_i]._commodity_name != deals[dealer_j]._commodity_name) continue;

	if(deals[dealer_i]._type == "BUY"){
	  if(deals[dealer_j]._price <= deals[dealer_i]._price){
	    if(current_sell_price > deals[dealer_j]._price){
	      current_sell_price = deals[dealer_j]._price;
	      target_id = dealer_j;
	    }
	  }
	}
	else if(deals[dealer_i]._type == "SELL"){
	  if(deals[dealer_j]._price >= deals[dealer_i]._price){
	    if(current_buy_price < deals[dealer_j]._price){
	      current_buy_price = deals[dealer_j]._price;
	      target_id = dealer_j;
	    }
	  }
	}
      }

      if(target_id != -1){
	if(deals[dealer_i]._type == "BUY"){
	  dealer_result[deals[dealer_i]._dealer_name]._paid += (current_sell_price + deals[dealer_i]._price) / 2;
	  dealer_result[deals[target_id]._dealer_name]._received += (current_sell_price + deals[dealer_i]._price) / 2;
	  commodity_result[deals[dealer_i]._commodity_name]._purchase_history
	    .push_back((current_sell_price + deals[dealer_i]._price) / 2);
	}

	if(deals[dealer_i]._type == "SELL"){
	  dealer_result[deals[dealer_i]._dealer_name]._received += (current_buy_price + deals[dealer_i]._price) / 2;
	  dealer_result[deals[target_id]._dealer_name]._paid += (current_buy_price + deals[dealer_i]._price) / 2;
	  commodity_result[deals[dealer_i]._commodity_name]._purchase_history
	    .push_back((current_buy_price + deals[dealer_i]._price) / 2);
	}
	
	used[dealer_i] = true;
	used[target_id] = true;
      }
    }

    for(map<string,CommodityResult>::iterator it = commodity_result.begin();
	it != commodity_result.end();
	it++){
      it->second.init();
      printf("%s %d %d %d\n",it->first.c_str(),it->second._lowest,it->second._mean,it->second._highest);
    }

    printf("--\n");
    for(map<string,DealerResult>::iterator it = dealer_result.begin();
	it != dealer_result.end();
	it++){

      printf("%s %d %d\n",it->first.c_str(),it->second._paid,it->second._received);
    }
    printf("----------\n");
  }
}
