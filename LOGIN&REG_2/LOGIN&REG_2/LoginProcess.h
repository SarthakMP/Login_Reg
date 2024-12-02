#pragma once
#include<fstream>
#include<iomanip>
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

struct DATA1
{
	string username, password;
};

void writeitfile(string& filename, vector<DATA1>&d1) {
	std::ofstream file(filename,std::ios::app);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open the file for writing.\n";
		return;
	}
	if (file.tellp()) {
		file << left << setw(10) << "Username"
			<< setw(20) << "Password" << '\n';
	}
	for (const auto& item : d1) {
		
		file << left << setw(10) << item.username
			<< setw(20) << item.password << '\n';
	}
	file.close();
	d1.clear();
}

string searchinfile(string& filename, unordered_map<string,string>& d1,string u,string p) {
	size_t tmp;
	std::ofstream file(filename);
	tmp = filename.find(u);
	cout << tmp;
	return u;
}
