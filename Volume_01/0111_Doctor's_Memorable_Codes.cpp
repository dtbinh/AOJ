
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

int main(){
	map<string,string> encode_old;
	map<string,string> decode_old;

	decode_old["00000"] = "A";
	decode_old["00001"] = "B";
	decode_old["00010"] = "C";
	decode_old["00011"] = "D";
	decode_old["00100"] = "E";
	decode_old["00101"] = "F";
	decode_old["00110"] = "G";

	decode_old["00111"] = "H";
	decode_old["01000"] = "I";
	decode_old["01001"] = "J";
	decode_old["01010"] = "K";
	decode_old["01011"] = "L";
	decode_old["01100"] = "M";
	decode_old["01101"] = "N";

	decode_old["01110"] = "O";
	decode_old["01111"] = "P";
	decode_old["10000"] = "Q";
	decode_old["10001"] = "R";
	decode_old["10010"] = "S";
	decode_old["10011"] = "T";
	decode_old["10100"] = "U";

	decode_old["10101"] = "V";
	decode_old["10110"] = "W";
	decode_old["10111"] = "X";
	decode_old["11000"] = "Y";
	decode_old["11001"] = "Z";

	decode_old["11010"] = " ";
	decode_old["11011"] = ".";
	decode_old["11100"] = ",";
	decode_old["11101"] = "-";
	decode_old["11110"] = "'";
	decode_old["11111"] = "?";


	encode_old[" "] = "101";
	encode_old["'"] = "000000";
	encode_old[","] = "000011";
	encode_old["-"] = "10010001";
	encode_old["."] = "010001";

	encode_old["?"] = "000001";
	encode_old["A"] = "100101";
	encode_old["B"] = "10011010";
	encode_old["C"] = "0101";
	encode_old["D"] = "0001";
	encode_old["E"] = "110";
	encode_old["F"] = "01001";
	encode_old["G"] = "10011011";

	encode_old["H"] = "010000";
	encode_old["I"] = "0111";
	encode_old["J"] = "10011000";
	encode_old["K"] = "0110";
	encode_old["L"] = "00100";
	encode_old["M"] = "10011001";
	encode_old["N"] = "10011110";

	encode_old["O"] = "00101";
	encode_old["P"] = "111";
	encode_old["Q"] = "10011111";
	encode_old["R"] = "1000";
	encode_old["S"] = "00110";
	encode_old["T"] = "00111";
	encode_old["U"] = "10011100";

	encode_old["V"] = "10011101";
	encode_old["W"] = "000010";
	encode_old["X"] = "10010010";
	encode_old["Y"] = "10010011";
	encode_old["Z"] = "10010000";

	map<string,string> encode;
	map<string,string> decode;
	for(map<string,string>::iterator it = encode_old.begin(); it != encode_old.end(); it++){
		encode[it->second] = it->first;
	}

	for(map<string,string>::iterator it = decode_old.begin(); it != decode_old.end(); it++){
		decode[it->second] = it->first;
	}

	string str;
	while(getline(cin,str)){

		string decoded="";
		for(int i=0;i<str.size();i++){
			decoded += decode[str.substr(i,1)];
		}

		string encoded="";
		for(int i=0;i<decoded.size();i++){
			for(int len=1;len<=decoded.size()-i;len++){
				if(!encode[decoded.substr(i,len)].empty()){
					encoded+=encode[decoded.substr(i,len)];
					i+=len-1;
					break;
				}
			}
		}

		cout << encoded << endl;

	}
}

