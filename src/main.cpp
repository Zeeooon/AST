//#define default {"# tri a b{* a|b{* a|0.5{] a","v op","v num1","v num2","< \"What operation would you like to do?\n","> op","< \"What is the first number?\n","> num1","< \"What is the second number?\n","> num2","= op|+ + num1|num2","= op|- - num1|num2","= op|* * num1|num2","= op|/ / num1|num2","= op|square * num1|num1","= op|rect * num1|num2","= op|tri r tri num1 num2","< \"Your number is |num1"};
#include "includes.h"
#include "func.h"
#include "io.h"

std::unordered_map<string, string> usemap;
std::vector<string> lines;

int main(int argc, char* argv[])
{
    if (argv[1] != NULL)
        pull(argv[1], lines);    
    for (int i = 0; i < lines.size(); i++)
    {
        run(lines[i], usemap);
    }
}