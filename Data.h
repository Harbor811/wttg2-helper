#ifndef Data_H
#define Data_H

// STATIC CLASS that will manage data
#include <vector>
#include <map>
#include <string>

#include "Site.h"
#include "Code.h"

using namespace std;

class Data
{
private:
    static vector<Site*> sites;
    static vector<Code*> codes;
    static vector<string> notes;
    static map<string, bool> settings;

public:
    // Emplace map vals, set codes, etc
    static void Compile();

    static void ResetCodes();

    // Getters && Setters
    static bool GetSetting(string key);
    static void ToggleSetting(string key);
    static vector<Site*> GetSites();
    static vector<Code*> GetCodes();
    static vector<string> GetNotes();
};

#endif