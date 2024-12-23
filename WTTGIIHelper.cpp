#include <iostream>

#include <string>
#include <vector>
#include <Windows.h>
#include <map>

#include "Data.h"
#include "Site.h"
#include "Input.h"

using namespace std;

// Global vars

string version = "1.0.3";
string patchNotes = "\t- Fixed all string-related crashes\n\t- Removed list function in \\notes\n\t\t-- It now always displays user notes\n\t- Shortened remove command to rm\n\t- Added functionality to deny code insertion\n\t- Overhauled general input to be more versatile\n\t\t-- This was a bitch to implement btw\n\t\t-- Multi commands are not supported\n\t\t-- Whitespace is ignored\n\t- Added time yy search commaned to \\sites\n\t- Added Settings menu\n\t\t-- Debug Mode (off by default)\n\t\t-- Ignore Wiki (on by default)";

Input* GetInput(const string disp);
void Wait();
bool Warn(const string message);

// Console Loops
void CmdLine(int argNum, char* args[]);
void Menu();
void Sites();
void Notes();
void Settings();
void Debug();

bool CheckForLastCode(); // Returns true if all codes are input

string StrToLower(const string input);
int SafeStoi(const string input);
void ToClipboard(const string &s);

// ARGNUM :: # of arguments (always at least 1 for the .exe)
// ARGS[] :: each char* points to string of that arg
int main(int argNum, char* args[])
{
    // Compile Data
    Data::Compile();
    Data::Load();
    
    if (argNum > 1) // Command line
    {
        CmdLine(argNum, args);
    }
    else // Main Loop
    {   
        Menu();
    }

    return 0;
}

void Menu()
{
    system("cls");
    cout << "Welcome To The Game II Helper\n";
    Input* input = GetInput("\\menu");
    
    while (input->command != "exit")
    {
        if (input->command == "sites")
        {
            Sites();
        }
        else if (input->command == "notes")
        {
            Notes();
        }
        else if (input->command == "debug")
        {
            Debug();
        }
        else if (input->command == "settings")
        {
            Settings();
        }
        else if (input->command == "help")
        {
            cout << "\n\n- Command List -\n\n";
            
            cout << "\t\tsites\t\tTakes you to site directory\n\n";
            
            cout << "\t\tnotes\t\tTakes you to note directory\n\n";

            cout << "\t\tsettings\tTakes you to settings directory\n\n";
            
            cout << "\t\thelp\t\tPrints this screen\n\n";
            
            cout << "\t\tinfo\t\tPrint application info\n\n";
            
            cout << "\t\texit\t\tQuit the program\n";
        }
        else if (input->command == "info")
        {
            system("cls");
            cout << "Welcome to the Game 2 Helper\n";
            cout << "Version " << version << "\n\n-Patch Notes-\n";
            cout << patchNotes << "\n";
        }
        else if (input->command != "exit")
        {
            cout << "\tCommand " << input->command << " not recognized\n";
            cout << "\tType help for help\n";
        }

        delete input;
        input = GetInput("\\menu");
    }
}

void Sites()
{
    system("cls");

    cout << "Welcome To The Game II Helper";
    cout << " Site List\n";

    Input* input = GetInput("\\menu\\sites");
    
    while (input->command != "exit")
    {
        if (input->command == "list")
        {
            bool exA = false, exT = false, exF = false;

            // Get specific inputs, if applicable
            for (int i = 0; i < input->flags.size(); i++)
            {
                switch (input->flags.at(i))
                {
                    case 'a':
                        exA = true;
                        break;
                    case 't':
                        exT = true;
                        break;
                    case 'f':
                        exF = true;
                        break;
                    default:
                        // do nothing
                        break;
                }
            }

            // If there are no specific inputs
            if (!exA && !exT && !exF)
            {
                if (Warn("list command prints every single site in the database.\n This will be large!"))
                {
                    for (int i = 0; i < sites.size(); i++)
                    {
                        Site* curSite = sites.at(i);
                        cout << curSite->name << "\n";
                        cout << " " << curSite->info << "\n";
                    }
                }
            }
            else
            {
                for (int i = 0; i < sites.size(); i++)
                {
                    Site* curSite = sites.at(i);
                    if ( (curSite->info.find("Always Open") != -1 && !exA)
                    ||   (curSite->info.find("XX") != -1 && !exT)
                    ||   (curSite->info.find("Fake") != -1 && !exF) )
                    {
                        cout << curSite->name << endl;
                        cout << " " << curSite->info << endl;
                    }
                }
            }
        }
        else if (input->command == "time")
        {
            if (input->val == -1)
            {
                cout << "\tUnspecified time.\n\tType help for help\n";
            }
            else if (input->val >= 60)
            {
                cout << "\tInvalid time. Input a number between 00 - 59\n";
            }
            else
            {
                bool exA = false;
                Site* curSite = nullptr;

                for(int i = 0; i < input->flags.size(); i++)
                {
                    switch(input->flags.at(i))
                    {
                    case 'a':
                        exA = true;
                        break;
                    default:
                        break;
                    }
                }

                // "0pen XX:00 - XX:29\n Pages: -index"
                for(int i = 0 ; i < sites.size(); i++)
                {
                    if (sites.at(i)->info.find("XX") != -1 &&
                        SafeStoi(sites.at(i)->info.substr(8, 2)) <= input->val &&
                        SafeStoi(sites.at(i)->info.substr(16, 2)) >= input->val)
                    {
                        if (settings.at("debug_mode"))
                        {
                            cout << "COMPARISON:\n";
                            cout << sites.at(i)->info.substr(8, 2) << " <= " << input->val << "\n";
                            cout << sites.at(i)->info.substr(16, 2) << " >= " << input->val << "\n\n";
                        }
                        
                        curSite = sites.at(i);
                        cout << curSite->name << "\n";
                        cout << " " << curSite->info << "\n";
                    }
                }
                if (curSite == nullptr) { cout << "\tNo sites found.\n\n"; }
            }
        }
        else if (input->command == "help")
        {
            cout << "\n- Command List -\n";
            cout << "\t\tlist\tLists all websites & their info\n";
            cout << "\t\t -a\tExclude always-open sites\n";
            cout << "\t\t -t\tExclude timed sites\n";
            cout << "\t\t -f\tExclude fake sites\n\n";

            cout << "\t\ttime yy\tLists sites open at time XX:yy\n";
            cout << "\t\t -a\tExclude always-open sites\n\n";

            cout << "\t\t[NAME]\tList websites with NAME contained in its name\n\n";
            
            cout << "\t\thelp\tPrints this screen\n\n";
            
            cout << "\t\texit\tBack to \\menu\n";
        }
        else if (input->command != "exit") // Try to find website by name
        {
            Site* curSite = nullptr;
            string newInput = StrToLower(input->command);

            cout << "Listing sites...\n\n";
            for (int i = 0; i < sites.size(); i++)
            {
                if (StrToLower(sites.at(i)->name).find(newInput) != -1)
                {
                    curSite = sites.at(i);
                    cout << curSite->name << "\n";
                    cout << " " << curSite->info << "\n";
                }
            }
            if (curSite == nullptr) { cout << "No sites found\n\n";}
        }

        delete input;
        input = GetInput("\\menu\\sites");
    }
}

void Notes()
{
    Input* input = new Input(" ");
    system("cls");
    
    cout << "Welcome To The Game II Helper\n";
    cout << " Notes\n";
    
    while (input->command != "exit")
    {
        // Clear display and print all User notes
        delete input;
        system("cls");

        if (!notes.empty()) { cout << "User notes\n"; }
        for(int i = 1; i <= notes.size(); i++)
        {
            cout << " " << i << " | " << notes.at(i - 1) << endl;
        }

        input = GetInput("\\menu\\notes");
        
        if (input->command == "help") // Print all commands
        {
            cout << "\nPaste codes here and it will automatically interpret them, even with extra chars\n";
            
            cout << "\n\t- Additional Commands- \n\n";
            
            cout << "\t\tcodes\tDisplay all current codes in order\n";
            cout << "\t\t\tCommand  compile  will also do this, just less readable\n\n";
            
            cout << "\t\tmissing\tDisplays how many codes are missing from each Wiki\n";
            cout << "\t\t\tThis assumes that you have input the wikis correctly\n\n";

            cout << "\t\tcompile\tCompile the tunnel code with all 8 keys\n\n";
            
            cout << "\t\trm x\tRemove note at line x\n\n";

            cout << "\t\tclear\tRemove all current keys in database and remove all notes written\n\n";

            cout << "\t\thelp\tPrint this list\n\n";

            cout << "\t\texit\tBack to \\menu\n";

            Wait();
        }
        else if (input->command == "codes")
        {
            bool noCodes = true;
            for(int i = 0; i < codes.size(); i++)
            {
                if (codes.at(i)->hash.find("MISSING") == -1)
                {
                    noCodes = false;
                    cout << " " << i + 1 << " | " << codes.at(i)->hash << "\n";
                }
            }
            
            if (noCodes)
            {
                cout << "No codes have been found!\n";
            }

            Wait();
        }
        else if (input->command == "missing")
        {
            if (settings.at("ignore_wikis"))
            {
                cout << "\tIgnore Wiki is enabled\n\tWould you like to disable it?\n";
                if (Warn("Ignore Wiki being disabled means you will need to re-enter your code for accurate wiki tracking"))
                {
                    settings.at("ignore_wikis") = !settings.at("ignore_wikis");
                }
            }
            else
            {
                int numWiki1 = 0, numWiki2 = 0, numWiki3 = 0;
                
                for (int i = 0; i < 8; i++)
                {
                    numWiki1 += (codes.at(i)->wiki == 1);
                    numWiki2 += (codes.at(i)->wiki == 2);
                    numWiki3 += (codes.at(i)->wiki == 3);
                }
                
                cout << "\nRemaining Wiki 1 Codes: " << 2 - numWiki1 << "\n";
                cout << "\nRemaining Wiki 2 Codes: " << 3 - numWiki2 << "\n";
                cout << "\nRemaining Wiki 3 Codes: " << 3 - numWiki3 << "\n";

                Wait();
            }
        }
        else if (input->command == "compile") // Compile all codes
        {
            COMPILE:
            string compCode = "";
            cout << "Compiled code (PASTE INTO TUNNEL)\n";
            for (int i = 0; i < 8; i++)
            {
                compCode += codes.at(i)->hash;
            }
            cout << "------------------------------------------------------------------------------------------------\n";
            cout << compCode;
            cout << "\n------------------------------------------------------------------------------------------------\n";

            if (compCode.find("MISSING") == -1) // Code is complete!
            {
                ToClipboard(compCode);
                cout << "\n\tCompleted code copied to clipboard!\n\tSure would be a shame...\n";
            }

            Wait();
        }
        else if (input->command == "rm")
        {
            int index = input->val;
            if (index <= 0 || index > notes.size())
            {
                cout << index << " not in notes.\n";
                Wait();
            }
            else
            {
                notes.erase(notes.begin() + index - 1);
            }
        }
        else if (input->command == "clear")
        {
            if (Warn("This will erase all notes and codes."))
            {
                cout << "Clearing notes...\n";
                notes.clear();
                Sleep(5);
                cout << "Clearing codes...\n";
                ResetCodes();
                Sleep(5);
                cout << "All notes and codes cleared.\n";
                Wait();
            }
        }
        else if (input->command != " " && input->command != "exit")
        {
            // Check for code
            bool code = false;
            string rawInp = input->raw;
            for (int i = 0; i < rawInp.length(); i++)
            {
                //     ----- Check # is 0-8 -----           ----- Check " - " -----          -------- Ensure Hash Len ----------    ---------- Ensure Char # ------------
                if (settings.at("debug_mode"))
                {
                    cout << "COMPARISONS:: \n";
                    cout << rawInp[i] << " >= '0' : " << (rawInp[i] >= '0') << "\n";
                    cout << rawInp[i] << " <= '8' : " << (rawInp[i] <= '8') << "\n";
                    cout << rawInp.substr(i+1, 3) << " == \" - \" : " << (rawInp.substr(i+1, 3) == " - ") << "\n";
                    cout << rawInp.substr(i+4).length() << " >= 12 : " << (rawInp.substr(i+4).length() >= 12) << "\n";
                    cout << rawInp.substr(i+4, 12).find(' ') << " == -1 : " << (rawInp.substr(i+4, 12).find(' ') == -1) << "\n";
                }
                if (rawInp[i] >= '0' && rawInp[i] <= '8' && rawInp.substr(i+1, 3) == " - " && rawInp.substr(i+4).length() >= 12 && rawInp.substr(i+4, 12).find(' ') == -1)
                {   // This is a code
                    int codeNum = SafeStoi(string(1, rawInp[i]));
                    if (settings.at("debug_mode")) { cout << "CODENUM:: " << codeNum << "\n"; }
                    
                    string hash = rawInp.substr(i + 4, 12);
                    code = true;
                    i += 4;

                    if (!settings.at("ignore_wikis"))
                    {
                        cout << " Code detected! Please input Wiki #\n";

                        delete input;
                        input = GetInput("1/2/3");
                        while ((input->raw.empty() || SafeStoi(input->command) < -1 || SafeStoi(input->command) == 0 || SafeStoi(input->command) >= 4))
                        {
                            cout << " Invalid input.\n Input the Wiki you got the code from\n If this input is not a code, type -1\n";
                            delete input;
                            input = GetInput("1/2/3");
                        }

                        if (input->raw.substr(0,2) != "-1")
                        {
                            codes.at(codeNum - 1)->hash = hash;
                            codes.at(codeNum - 1)->wiki = SafeStoi(input->command);

                            if (CheckForLastCode())
                            {
                                cout << " CODE COMPLETE \n";
                                delete input;
                                goto COMPILE;
                            }
                        }
                        else
                        {
                            code = false;
                        }
                    }
                    else  // Ignore_Wikis == true
                    {
                        codes.at(codeNum - 1)->hash = hash;
                        codes.at(codeNum - 1)->wiki = -1;
                    }
                }
            }
            if (!code)
            {
                notes.push_back(input->raw);
            }
        }
    }
}

void Settings()
{
    Input* input = new Input(" ");

    while (input->command != "exit")
    {        
        system("cls");
        cout << "\tSettings\n\n";
        cout << "\t\t1 | Debug Mode\n";
        cout << "\t\t  Enabled: " << settings.at("debug_mode") << "\n\n";

        cout << "\t\t2 | Ignore Wikis\n";
        cout << "\t\t  Enabled: " << settings.at("ignore_wikis") << "\n";

        delete input;
        input = GetInput("\\menu\\settings");

        if (input->command == "debug" || input->command == "1")
        {
            settings.at("debug_mode") = !settings.at("debug_mode");
        }
        else if (input->command == "ignore" || input->command == "2")
        {
            settings.at("ignore_wikis") = !settings.at("ignore_wikis");
        }
        else if (input->command == "help")
        {
            cout << "\n\tInput setting # or shortened setting name to toggle it\n";
            Wait();
        }
    }

    delete input;
}

void Debug()
{
    Input* input = new Input(" ");
    string allChars = "0123456789abcdef";
    
    while (input->command != "exit")
    {
        if (input->command == "help")
        {
            cout << "- Commands -\n\n";
            cout << "\t\tgenerate x\t\tGenerates a fake code num x\n";
            cout << "\t\t -a\t\tGenerates all 9 codes instead of just 1\n";
        }
        if (input->command == "generate")
        {
            bool genAll = false;
            for (int i = 0; i < input->flags.size(); i++)
            {
                switch (input->flags.at(i))
                {
                case 'a':
                    genAll = true;
                    break;
                default:
                    break;
                }
            }

            if (!genAll)
            {
                if (input->val == -1)
                {
                    cout << "\nNo number specified.\n";
                }
                else
                {
                    cout << "generated code: ";
                    cout << input->val << " - ";
                    for (int i = 0; i < 12; i++)
                    {
                        cout << allChars.substr(rand() % allChars.length(), 1);
                    }
                    cout << "\n";
                }
            }
            else
            {
                cout << "generated codes:\n";
                for (int i = 1; i < 9; i++)
                {
                    cout << "\t" << i << " - ";
                    for (int j = 0; j < 12; j++)
                    {
                        cout << allChars.substr(rand() % allChars.length(), 1);
                    }
                    cout << "\n";
                }
            }
        }

        delete input;
        GetInput("\\menu\\debug");
    }

    delete input;
}

Input* GetInput(const string disp)
{    
    string input;
    cout << "\n " << disp << " > ";
    getline(cin, input);

    Input* userInput = new Input(input);
    
    if (settings.at("debug_mode"))
    {
        cout << " [CURRENT INPUT]\n";
        cout << "\tRAW: " << userInput->raw;
        cout << "\n\tCOMMAND: " << userInput->command;
        cout << "\n\tFLAGS: ";
        for (int i = 0; i < userInput->flags.size(); i++)
        {
            cout << "-" << userInput->flags.at(i);
            cout << " ";
        }
        cout << "\n\tVALUE: " << userInput->val;
        cout << endl;
    }
    
    return userInput;
}

void Wait()
{
    cout << "\n [ -- ENTER -- ]";
    string* str = new string();
    getline(cin, *str);
    delete str;
}

bool Warn(const string message)
{
    Input* input = new Input(" ");
    cout << " -- WARNING -- \n\n";
    cout << " " << message << "\n";
    cout << " Are you sure you want to continue?\n";

    while (input->command[0] != 'y' && input->command[0] != 'n')
    {
        delete input;
        input = GetInput("Y/N");

        if (input->command[0] == 'y')
        {
            delete input;
            return true;
        }
        else if (input->command[0] == 'n')
        {
            delete input;
            return false;
        }

        cout << " Input Y or N\n";
    }
    
    delete input;
    return false;
}

bool CheckForLastCode()
{
    for (int i = 0; i < codes.size(); i++)
    {
        if (codes.at(i)->wiki == -1 ||
            codes.at(i)->hash.find("MISSING") != -1)
        {
            return false;
        }
    }
    return true;
}

string StrToLower(const string input)
{
    string output;
    
    for(unsigned long long i = 0; i < input.length(); i++)
    {
        output.push_back(tolower(input[i]));
    }

    return output;
}

int SafeStoi(const string input)
{
    int curChar;
    for (unsigned long long i = 0; i < input.length(); i++)
    {
        curChar = input[i] - 48;
        
        if (curChar < 0 || curChar > 9)
        {
            return -1;
        }
    }
    return stoi(input);
}

void ToClipboard(const string& s)
{
    OpenClipboard(nullptr);
    EmptyClipboard();
    
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
    if (!hg)
    {
        CloseClipboard();
        return;
    }
    
    memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
    GlobalUnlock(hg);
    
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    
    GlobalFree(hg);
}

void CmdLine(int argNum, char* args[])
{
    
}
