#include "includes.h"
#include "stringops.h"
#include "func.h"

void iff(string line, std::unordered_map<string, string>& map)
{
    string cmd = line.substr(line.find(' ') + 1, line.size());
    string op1, op2;
    getops(op1, op2, line.substr(0, line.find(' ')), map);
    if (op1 == op2)
        run(cmd, map);
}
void notf(string line, std::unordered_map<string, string>& map)
{
    string cmd = line.substr(line.find(' ') + 1, line.size());
    string op1, op2;
    getops(op1, op2, line, map);
    if (op1 != op2)
        run(cmd, map);
}
void gre(string line, std::unordered_map<string, string>& map)
{
    string sop1, sop2;
    string cmd = line.substr(line.find(' ') + 1, line.size());
    getops(sop1, sop2, line, map);
    double op1, op2;
    convert(sop1, sop2, op1, op2);
    if (op1 > op2)
        run(cmd, map);
}
void les(string line, std::unordered_map<string, string>& map)
{
    string sop1, sop2;
    string cmd = line.substr(line.find(' ') + 1, line.size());
    getops(sop1, sop2, line, map);
    double op1, op2;
    convert(sop1, sop2, op1, op2);
    if (op1 < op2)
        run(cmd, map);
}