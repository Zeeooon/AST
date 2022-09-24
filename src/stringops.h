#pragma once
#include <string>
#include <unordered_map>
using std::string;

std::vector<string> split(string str, char chr);
string parse(string s);
void getops(string& op1, string& op2, string line, std::unordered_map<string, string>& map);
void convert(string sop1, string sop2, double& op1, double& op2);