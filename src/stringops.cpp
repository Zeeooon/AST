#include "stringops.h"
#include "includes.h"


std::vector<string> split(string str, char chr)
{
    string word;
    std::vector<string> words;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == chr)
        {
            words.push_back(word);
            word = "";
        }
        else
        {
            word += str[i];
        }
    }
    words.push_back(word);
    return(words);
}

string parse(string s) {
    string s2;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '\\') {
            switch (s[i + 1]) {
            case 'a': s2 += '\a'; ++i; break;
            case 'b': s2 += '\b'; ++i; break;
            case 't': s2 += '\t'; ++i; break;
            case 'n': s2 += '\n'; ++i; break;
            case 'v': s2 += '\v'; ++i; break;
            case 'f': s2 += '\f'; ++i; break;
            case 'r': s2 += '\r'; ++i; break;
            case '\"': s2 += '\"'; ++i; break;
            }
        }
        else s2 += s[i];
    }
    return s2;
}

void getops(string& op1, string& op2, string line, std::unordered_map<string, string>& map)
{
    if (map.find(line.substr(0, line.find('|'))) != map.end())
        op1 = map.find(line.substr(0, line.find('|')))->second;
    else
        op1 = line.substr(0, line.find('|'));
    if (map.find(line.substr(line.find('|') + 1, line.size())) != map.end())
        op2 = map.find(line.substr(line.find('|') + 1, line.size()))->second;
    else
        op2 = line.substr(line.find('|') + 1, line.size());
}
void convert(string sop1, string sop2, double& op1, double& op2)
{
    op1 = std::stod(sop1);
    op2 = std::stod(sop2);
}