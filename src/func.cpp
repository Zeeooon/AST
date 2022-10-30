#include "includes.h"
#include "maths.h"
#include "stringops.h"
#include "conditional.h"
#include "io.h"

void ret(string line, std::unordered_map<string, string>& map);
void loop(string line, std::unordered_map<string, string>& map);
void func(string line, std::unordered_map<string, string>& map);
void inc(string line);

std::unordered_map<string, string> vars;
std::unordered_map<string, string> funcmap;
//map of every command in function
std::unordered_map<string, string> tempmap;

string retvar;
bool retur;

void var(string line, std::unordered_map<string, string>& map)
{
    string name = line.substr(0, line.find(' '));
    line.erase(0, line.find(' ') + 1);
    if (line.length() == 0)
        line = "!";
    else
    {
        map[name] = line;
    }
}

void run(string line, std::unordered_map<string, string>& map)
{
    switch (line[0])
    {
    case 'v': var(line.erase(0, 2), map); break;
    case '#': inc(line.erase(0, 2)); break;
    case '<': out(line.erase(0, 2), map); break;
    case '>': in(line.erase(0, 2), map); break;
    case '=': iff(line.erase(0, 2), map); break;
    case '!': notf(line.erase(0, 2), map); break;
    case 'g': gre(line.erase(0, 2), map); break;
    case 'l': les(line.erase(0, 2), map); break;
    case '+': add(line.erase(0, 2), map); break;
    case '-': sub(line.erase(0, 2), map); break;
    case '*': mul(line.erase(0, 2), map); break;
    case '/': div(line.erase(0, 2), map); break;
    case 'e': loop(line.erase(0, 2), map); break;
    case 'r': func(line.erase(0, 2), map); break;
    case ']': ret(line.erase(0, 2), map); break;
    }
}

void loop(string line, std::unordered_map<string, string>& map)
{

    if (line.substr(0, line.find(' ')) == "~")
        while (true)
            run(line.substr(line.find(' ') + 1, line.size()),map);
    else
    {
        int amount = 0;
        if (map.find(line.substr(0, line.find(' '))) == map.end())
            amount = std::stoi(line.substr(0, line.find(' ')));
        else
            amount = std::stoi(map.find(line.substr(0, line.find(' ')))->second);
        line.erase(0, line.find(' '));
        for (int i = 0; i < amount; i++)
        {
            run(line.substr(line.find(' ') + 1, line.size()),map);
        }
    }
}
void func(string line, std::unordered_map<string, string>& map)
{
    for (auto x : map)
    {
        vars[x.first] = x.second;
    }
    retur = true;
    //actual function code
    string func = funcmap.find(line.substr(0, line.find(' ')))->second;
    //variables to be inputted into the program
    std::vector<string> ivars = split(line.substr(line.find(' ') + 1, line.size()), ' ');
    retvar = ivars[0];
    //pulls function into seperate lines
    //pulls parameters from to be used into function
    std::vector<string> params = split(func.substr(0, func.find('{')), ' ');
    for (int i = 0; i < params.size(); i++)
    {
        tempmap[params[i]] = map[ivars[i]];
    }
    map.clear();

    for (auto x : tempmap)
    {
        map[x.first] = x.second;
    }
    func.erase(0, func.find('{') + 1);
    //single line
    std::vector<string> nfunc = split(func, '{');
    for (int i = 0; i < nfunc.size() && retur == true; i++)
    {
        run(nfunc[i], map);
    }
    retur = false;
    map.clear();
    for (auto x : vars)
    {
        map[x.first] = x.second;
    }
}

void inc(string line)
{
    string name, loc;
    name = line.substr(0, line.find(' '));
    loc = line.substr(line.find(' ') + 1, line.length());
    funcmap[name] = loc;
}

void ret(string line, std::unordered_map<string, string>& map)
{
    vars[retvar] = map.find(line)->second;
    retur = false; 
    for (auto x : vars)
    {
        map[x.first] = x.second;
    }  
}