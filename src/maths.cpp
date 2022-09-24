#include <string>
#include <unordered_map>

#include "stringops.h"
using std::string;

void add(string line, std::unordered_map<string, string> &map)
{
    string sop1, sop2;
    getops(sop1, sop2, line, map);
    double num1, num2;
    convert(sop1, sop2, num1, num2);
    map[line.substr(0, line.find('|'))] = std::to_string(num1 + num2);
}
void sub(string line, std::unordered_map<string, string> &map)
{
    string sop1, sop2;
    getops(sop1, sop2, line, map);
    double num1, num2;
    convert(sop1, sop2, num1, num2);
    map[line.substr(0, line.find('|'))] = std::to_string(num1 - num2);
}
void mul(string line, std::unordered_map<string, string> &map)
{
    string sop1, sop2;
    getops(sop1, sop2, line, map);
    double num1, num2;
    convert(sop1, sop2, num1, num2);
    map[line.substr(0, line.find('|'))] = std::to_string(num1 * num2);
}
void div(string line, std::unordered_map<string, string> &map)
{
    string sop1, sop2;
    getops(sop1, sop2, line, map);
    double num1, num2;
    convert(sop1, sop2, num1, num2);
    map[line.substr(0, line.find('|'))] = std::to_string(num1 / num2);
}