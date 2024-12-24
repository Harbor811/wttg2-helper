#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>

using namespace std;

struct Input
{
    std::string raw;
    std::string command;
    int val = -1;
    std::vector<char> flags = {};

    Input(string input)
    {
        if (input.empty()) { raw = " "; command = " "; return;}
        raw = input;
        
        char curChar;

        // Convert (string) input into Input (the object) lol
        for (int i = 0; i < input.length(); i++)
        {
            curChar = tolower(input[i]);
            
            if (curChar != ' ')
            {
                if (command.empty())
                {
                    while (curChar != ' ' && i < input.length())
                    {
                        command.push_back(curChar);
                        i++;
                        curChar = tolower(input[i]);
                    }
                }
                else if (curChar == '-')
                {
                    i++;
                    curChar = tolower(input[i]);
                    flags.push_back(curChar);
                } // ADD MULTI DIGIT READS FOR VAL
                else if (val == -1 && SafeStoi(string(1, curChar)) != -1)
                {
                    string valNum = "";
                    for ( ; i < input.length() && curChar >= '0' && curChar <= '9'; i++)
                    {   // 1 - r38257329085
                        curChar = tolower(input[i]);
                        valNum.push_back(curChar);
                    }

                    val = SafeStoi(valNum);
                }
                // else
                // {
                //     // Subcommand perhaps
                //     cout << "\tSubcommands are not yet supported.\n";
                //     cout << "\n\tText \"" << input.substr(i) << "\" truncated.\n";
                //     return;
                // }
            }
        }

        // Check if it was all spaces
        if (command == "")
        {
            raw = " "; command = " "; return;
        }
    }

private:
    int SafeStoi(string input)
    {
        int curChar;
        for (int i = 0; i < input.length(); i++)
        {
            curChar = input[i] - '0';
        
            if (curChar < 0 || curChar > 9)
            {
                return -1;
            }
        }

        bool stoiGood = false;
        while (!stoiGood)
        {
            try
            {
                return stoi(input);
            }
            catch (out_of_range const &e)
            {
                input = input.substr(0, input.length() - 1);
                if (input.length() == 0)
                {
                    return -1;
                }
            }
        }
        cout << "How did we get here?\n";
        return -1;
    }
};

#endif