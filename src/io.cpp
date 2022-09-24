#include "includes.h"
#include "stringops.h"

void pull(string file, std::vector<string> &lines)
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
}

void out(string line, std::unordered_map<string, string>& map)
{
    line = parse(line);
    std::vector<string> words = split(line, '|');
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i][0] == '"')
            std::cout << words[i].erase(0, 1);
        else
            std::cout << map.find(words[i])->second;
    }
}

void in(string line, std::unordered_map<string, string>& map)
{
    std::getline(std::cin, map[map.find(line)->first]);
}