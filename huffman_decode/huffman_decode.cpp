// huffman_decode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>


using namespace std;

string decode(unordered_map<string, char> map, string bits) {


	string s = "";
	string result = "";
	for (int i = 0; i < bits.size(); i++) {
		s += bits[i];
		if (map.find(s) != map.end()) {
			int found = bits.find(s);
			//string temp = ""; temp = map[s];
			//bits.replace(found, s.length(), temp);
			result += map[s];
			s = "";
		}
	}
	return result;
}


size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

string printBinary(char c) {
	string result = "";
	for (int i = 7; i >= 0; --i) {
		result+= ((c & (1 << i)) ? '1' : '0');
	}
	return result;
}

int main()
{
	
	string freq = "";
	unordered_map <string, char> map;
	ifstream f("compress.txt");
	
	while (true) {

		char c;
		f.get(c);
		if (c == '*') {
			char cc;
			f.get(cc);
			if (cc == '*') {
				f.get(cc);
				break;
			}
			else
			{
				char ccc;
				f.get(ccc);
				while (ccc != '\n') {
					freq += ccc;
					f.get(ccc);
				}
				map[freq] = c;
				freq = "";
			}
		}
		else {
			char cc;
			f.get(cc);

			char ccc;
			f.get(ccc);

			while (ccc != '\n') {
				freq += ccc;
				f.get(ccc);
			}
			map[freq] = c;
			freq = "";
		}
	}

	char chaar;
	f.get(chaar);
	f.get(chaar);

	int mod = chaar - '0';
	string comp_str = "";
	while (f.get(chaar)) {
		if (chaar != '\n')
			comp_str += chaar;
	}

	cout << comp_str << endl;
	cout << mod << endl;

	string binary = "";
	for (int i = 0; i < comp_str.length(); i++) {
		binary += printBinary(comp_str[i]);
	}
	cout << binary<< endl;

	binary = binary.substr(0, binary.length() - (8 - mod));
	cout << binary<<endl;

	cout<<decode(map, binary);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
