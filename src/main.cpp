#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

using std::string;

std::unordered_map<string, string> vars;
std::unordered_map<string, string> funcmap;
std::unordered_map<string, string> tempmap;
std::unordered_map<string, string> usemap;
std::vector<string> lines;
string retvar;
bool retur;

void error(string error, int code)
{
    std::cout << "[" << code << "] " << error << "\n";
    exit(code);
}

std::vector<string> split(string str, char chr);
void run(string line);

void var(string line);
void inc(string line);
void out(string line);
void in(string line);
void add(string line);
void sub(string line);
void mul(string line);
void div(string line);
void loop(string line);
void iff(string line);
void notf(string line);
void gre(string line);
void les(string line);
void func(string line);
void ret(string line);
void pull(string file);

int main(int argc, char* argv[])
{
    if (argv[1] != NULL)
        pull(argv[1]);
    for (int i = 0; i < lines.size(); i++)
    {
        run(lines[i]);
    }
}

void pull(string file)
{
    string line;
    std::ifstream myfile(file);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines.push_back(line);
        }
        myfile.close();
    }
    else
        error("Unable to open file" + file, 2);
}

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

void run(string line)
{
    switch (line[0])
    {
    case 'v': var(line.erase(0, 2));break;
    case '#': inc(line.erase(0, 2));break;
    case '<': out(line.erase(0, 2));break;
    case '>': in(line.erase(0, 2));break;
    case '=': iff(line.erase(0, 2));break;
    case '!': notf(line.erase(0, 2));break;
    case 'g': gre(line.erase(0, 2));break;
    case 'l': les(line.erase(0, 2));break;
    case '+': add(line.erase(0, 2));break;
    case '-': sub(line.erase(0, 2));break;
    case '*': mul(line.erase(0, 2));break;
    case '/': div(line.erase(0, 2));break;
    case 'e': loop(line.erase(0, 2));break;
    case 'r': func(line.erase(0, 2));break;
    case ']': ret(line.erase(0, 2));break;
    }
}

void var(string line)
{
    string name = line.substr(0, line.find(' '));
    line.erase(0, line.find(' ') + 1);
    if (line.length() == 0)
        line = "!";
    else
    {
        usemap[name] = line;
    }
}
void out(string line)
{
    line = parse(line);
    std::vector<string> words = split(line, '|');
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i][0] == '"')
            std::cout << words[i].erase(0, 1);
        else
            std::cout << usemap.find(words[i])->second;
    }
}
void in(string line)
{
        std::getline(std::cin, usemap[usemap.find(line)->first]);
}
void getops(string &op1, string &op2, string line)
{
    if (usemap.find(line.substr(0, line.find('|'))) != usemap.end())
        op1 = usemap.find(line.substr(0, line.find('|')))->second;
    else
        op1 = line.substr(0, line.find('|'));
    if (usemap.find(line.substr(line.find('|') + 1, line.size())) != usemap.end())
        op2 = usemap.find(line.substr(line.find('|') + 1, line.size()))->second;
    else
        op2 = line.substr(line.find('|') + 1, line.size());
}
void convert(string sop1, string sop2, double &op1, double &op2)
{
    op1 = std::stod(sop1);
    op2 = std::stod(sop2);
}
void iff(string line)
{
    string cmd = line.substr(line.find(' ') + 1, line.size());
    string op1, op2;
    getops(op1, op2, line.substr(0, line.find(' ')));
    if (op1 == op2)
        run(cmd);
}
void notf(string line)
{
    string cmd = line.substr(line.find(' ') + 1, line.size());
    string op1, op2;
    getops(op1, op2, line);
    if (op1 != op2)
        run(cmd);
}
void gre(string line)
{
    string sop1, sop2;
    string cmd = line.substr(line.find(' ') + 1, line.size());
    getops(sop1, sop2, line);
    double op1, op2;
    convert(sop1, sop2, op1, op2);
    if (op1 > op2)
        run(cmd);
}
void les(string line)
{
    string sop1, sop2;
    string cmd = line.substr(line.find(' ') + 1, line.size());
    getops(sop1, sop2, line);
    double op1, op2;
    convert(sop1, sop2, op1, op2);
    if (op1 < op2)
        run(cmd);
}
void add(string line)
{
    string sop1, sop2;
    getops(sop1, sop2, line);
    double num1, num2;
    convert(sop1, sop2, num1, num2);
    usemap[line.substr(0, line.find('|'))] = std::to_string(num1 + num2);
}
void sub(string line)
{
    string sop1, sop2;
    getops(sop1, sop2, line);
    double num1, num2;
    convert(sop1, sop2, num1, num2);
    usemap[line.substr(0, line.find('|'))] = std::to_string(num1 - num2);
}
void mul(string line)
{
    string sop1, sop2;
    getops(sop1, sop2, line);
    double num1, num2;
    convert(sop1, sop2, num1, num2);
    usemap[line.substr(0, line.find('|'))] = std::to_string(num1 * num2);
}
void div(string line)
{
    string sop1, sop2;
    getops(sop1, sop2, line);
    double num1, num2;
    convert(sop1, sop2, num1, num2);
    usemap[line.substr(0, line.find('|'))] = std::to_string(num1 / num2);
}
void loop(string line)
{
    
    if (line.substr(0, line.find(' ')) == "~")
        while (true)
            run(line.substr(line.find(' ') + 1, line.size()));
    else 
    {
        int amount = 0;
        if (usemap.find(line.substr(0, line.find(' '))) == usemap.end())
            amount = std::stoi(line.substr(0, line.find(' ')));
        else
            amount = std::stoi(usemap.find(line.substr(0, line.find(' ')))->second);
        line.erase(0, line.find(' '));
        for (int i = 0; i < amount; i++)
        {
            run(line.substr(line.find(' ') + 1, line.size()));
        }
    }
}
void func(string line)
{
    retur = true;
    //actual function code
    string func = funcmap.find(line.substr(0, line.find(' ')))->second;
    //variables to be inputted into the program
    std::vector<string> ivars = split(line.substr(line.find(' ') + 1, line.size()), ' ');
    retvar = ivars[0];
    //pulls function into seperate words
    std::vector<string> params = split(func.substr(0, func.find('{')), ' ');
    for (int i = 0; i < params.size(); i++)
    {
        tempmap[params[i]] = usemap[ivars[i]];
    }
    usemap.clear();
    for (auto x : tempmap)
    {
        usemap[x.first] = x.second;
    }
    func.erase(0, func.find('{')+1);
    //single line
    std::vector<string> nfunc = split(func, '{');
    for (int i = 0; i < nfunc.size() && retur == true; i++)
    {
        run(nfunc[i]);
    }
    retur = false;
    usemap.clear();
    for (auto x : vars)
    {
        usemap[x.first] = x.second;
    }
}

void inc(string line)
{
    string name, loc;
    name = line.substr(0, line.find(' '));
    loc = line.substr(line.find(' ') + 1, line.length());
    funcmap[name] = loc;
}

void ret(string line)
{
    vars[retvar] = usemap.find(line)->second;
    retur = false;
}