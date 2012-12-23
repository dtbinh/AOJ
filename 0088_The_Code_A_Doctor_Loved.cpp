
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
#include <deque>

using namespace std;

typedef long long ll;

int main(){
	string str;

	map<string,string> encode;
	map<string,string> decode;

	encode[" "] = "101";
	encode["'"] = "000000";
	encode[","] = "000011";
	encode["-"] = "10010001";
	encode["."] = "010001";

	encode["?"] = "000001";
	encode["A"] = "100101";
	encode["B"] = "10011010";
	encode["C"] = "0101";
	encode["D"] = "0001";
	encode["E"] = "110";
	encode["F"] = "01001";
	encode["G"] = "10011011";

	encode["H"] = "010000";
	encode["I"] = "0111";
	encode["J"] = "10011000";
	encode["K"] = "0110";
	encode["L"] = "00100";
	encode["M"] = "10011001";
	encode["N"] = "10011110";

	encode["O"] = "00101";
	encode["P"] = "111";
	encode["Q"] = "10011111";
	encode["R"] = "1000";
	encode["S"] = "00110";
	encode["T"] = "00111";
	encode["U"] = "10011100";

	encode["V"] = "10011101";
	encode["W"] = "000010";
	encode["X"] = "10010010";
	encode["Y"] = "10010011";
	encode["Z"] = "10010000";

	decode["00000"] = "A";
	decode["00001"] = "B";
	decode["00010"] = "C";
	decode["00011"] = "D";
	decode["00100"] = "E";
	decode["00101"] = "F";
	decode["00110"] = "G";

	decode["00111"] = "H";
	decode["01000"] = "I";
	decode["01001"] = "J";
	decode["01010"] = "K";
	decode["01011"] = "L";
	decode["01100"] = "M";
	decode["01101"] = "N";

	decode["01110"] = "O";
	decode["01111"] = "P";
	decode["10000"] = "Q";
	decode["10001"] = "R";
	decode["10010"] = "S";
	decode["10011"] = "T";
	decode["10100"] = "U";

	decode["10101"] = "V";
	decode["10110"] = "W";
	decode["10111"] = "X";
	decode["11000"] = "Y";
	decode["11001"] = "Z";

	decode["11010"] = " ";
	decode["11011"] = ".";
	decode["11100"] = ",";
	decode["11101"] = "-";
	decode["11110"] = "'";
	decode["11111"] = "?";

	while(getline(cin,str)){

		string enc="";
		for(int i=0;i<str.size();i++){
			enc+=encode[str.substr(i,1)];
		}

		enc+="0000";

		string dec="";
		for(int i=0;i+5<=enc.size();i+=5){
			dec+=decode[enc.substr(i,5)];
		}

		cout << dec << endl;
	}

}

