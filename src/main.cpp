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