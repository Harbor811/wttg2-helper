#include <vector>
#include <map>
#include <string>

#include "Data.h"
#include "Site.h"
#include "Code.h"

using namespace std;

vector<Site*> Data::sites;
vector<Code*> Data::codes = {new Code(), new Code(), new Code(), new Code(), new Code(), new Code(), new Code(), new Code()};
vector<string> Data::notes;
map<string, bool> settings;

void Data::Compile()
{
    // Settings
    settings.emplace("debug_mode", false);
    settings.emplace("ignore_wikis", true);

    // Codes
    for (int i = 0; i < 8; i++)
    {
        codes.at(i)->hash = "|#" + to_string(i + 1) + "_MISSING|";
        codes.at(i)->wiki = -1;
    }

    // Sites
    // Always open
    sites.push_back(new Site("Bug Friendly", "Always Open\n Pages: -index -store -faq -noid -join"));
    sites.push_back(new Site("Cleaning Services", "Always Open\n Pages: -index -burial -freezing"));
    sites.push_back(new Site("Cry Bitch", "Always Open\n Pages: -index -login"));
    sites.push_back(new Site("Drone Spy", "Always Open\n Pages: -index -videos -spyforme"));
    sites.push_back(new Site("EnCrave", "Always Open\n Pages: -index -gateopen"));
    sites.push_back(new Site("Evidence Locker", "Always Open\n Pages: -index -leaked -confiscated -contribute -purchase"));
    sites.push_back(new Site("Evil Collection", "Always Open\n Pages: -index -pics -creepypics -randompics -memes -link -ab -ab2 -baby -chat"));
    sites.push_back(new Site("Eye", "Always Open\n Pages: -index"));
    sites.push_back(new Site("Foot Doctor", "Always Open\n Pages: -index -myfavoritefeet -homemade -sendmepics"));
    sites.push_back(new Site("Forgive Me", "Always Open\n Pages: -index -confess"));
    sites.push_back(new Site("Heirloom", "Always Open\n Pages: -index -quality -specials -containers -order -pgpkey -walletid -error"));
    sites.push_back(new Site("Hidden Pleasures", "Always Open\n Pages: -index -requestsale -range1 -range2 -range3 -range4 -range5 -message -buy -signin(broken)"));
    sites.push_back(new Site("I Love Cats", "Always Open\n Pages: -index -mycats -contact"));
    sites.push_back(new Site("Keep Sake", "Always Open\n Pages: -index"));
    sites.push_back(new Site("Milk Supply", "Always Open\n Pages: -index -milkpictures"));
    sites.push_back(new Site("Mortal Masks", "Always Open\n Pages: -index -order -how"));
    sites.push_back(new Site("Mutilation", "Always Open\n Pages: -index -login -join -nowallet"));
    sites.push_back(new Site("My Gut", "Always Open\n Pages: -index -shop -buy -special -contact"));
    sites.push_back(new Site("Myriad", "Always Open\n Pages: -index"));
    sites.push_back(new Site("Oneless", "Always Open\n Pages: -index"));
    sites.push_back(new Site("Order Of Nine", "Always Open\n Pages: -index -join"));
    sites.push_back(new Site("Panty Sales", "Always Open\n Pages: -index"));
    sites.push_back(new Site("Share Your Genitals", "Always Open\n Pages: -index"));
    sites.push_back(new Site("St Louis Arch", "Always Open\n Pages: -index -arch -aliens -whydie"));
    sites.push_back(new Site("Thanks For Visiting", "Always Open\n Pages: -index -donttalktome -slide -babyshrimp -posture -bar -evilmonster -slide2 -creepy -face -fakemain -black -numbers"));
    sites.push_back(new Site("The Black Waves", "Always Open\n Pages: -index"));
    sites.push_back(new Site("The Doll Maker", "Always Open\n - Triggers The Doll Maker\n Pages: -index -enter"));
    sites.push_back(new Site("The End Of NY", "Always Open\n Pages: -index"));
    sites.push_back(new Site("The Granddaddy", "Always Open\n Pages: -index -contact -gallery -error"));
    sites.push_back(new Site("The Grey", "Always Open\n Pages: -index -interius -latus -centrum -inanis"));
    sites.push_back(new Site("The Hall", "Always Open\n Pages: -index"));
    sites.push_back(new Site("The Light Within", "Always Open\n Pages: -index -saved"));
    sites.push_back(new Site("THE MAGISTRI", "Always Open\n Pages: -index -enter -join -walk"));
    sites.push_back(new Site("The Rule Of Three", "Always Open\n - Contains Wiki link III\n Pages: -index"));
    sites.push_back(new Site("Vacation", "Always Open\n Pages: -index"));
    sites.push_back(new Site("We Rock", "Always Open\n Pages: -index"));
    sites.push_back(new Site("Father Donald", "Always Open\n Pages: -index "));
    sites.push_back(new Site("Grandmas Fantasy", "Always Open\n Pages: -index -older"));
    sites.push_back(new Site("Is Evil", "Always Open\n Pages: -index"));
    sites.push_back(new Site("Kill For Me", "Always Open\n Pages: -index -targets -instructions"));
    sites.push_back(new Site("Pay To Rape", "Always Open\n Pages: -index -faq -pay"));
    sites.push_back(new Site("Scream Bitch", "Always Open\n Pages: -index -join"));
    sites.push_back(new Site("The Bombmaker", "Always Open\n Pages: -index"));
    sites.push_back(new Site("The Loogaroo", "Always Open\n Pages: -index"));
    sites.push_back(new Site("The Prey", "Always Open\n Pages: -index"));
    sites.push_back(new Site("Warehouse 33", "Always Open\n Pages: -index -warehouse1 -warehouse2 -warehouse4"));

    // Timed Sites
    // 00 - 14
    sites.push_back(new Site("IAMHERE", "Open XX:00 - XX:14\n Pages: -index"));
    // 00 - 29
    sites.push_back(new Site("Borrow My Daughter", "Open XX:00 - XX:29\n Pages: -index"));
    sites.push_back(new Site("Deep Journal", "Open XX:00 - XX:29\n Pages: -index -page2 -page3"));
    sites.push_back(new Site("Don't Waste It", "Open XX:00 - XX:29\n Pages: -index -no -yes"));
    sites.push_back(new Site("YOU THERE?", "Open XX:00 - XX:29\n Pages: -index"));
    // 30 - 44
    sites.push_back(new Site("Ave Satan", "Open XX:30 - XX:44\n Pages: -index"));
    sites.push_back(new Site("Fifty Seven", "Open XX:30 - XX:44\n Pages: -index"));
    sites.push_back(new Site("Number Station", "Open XX:30 - XX:44\n Pages: -index"));
    sites.push_back(new Site("Your Data", "Open XX:30 - XX:44\n Pages: -index"));
    // 45 - 59
    sites.push_back(new Site("Fortune Cookie", "Open XX:45 - XX:59\n Pages: -index"));
    sites.push_back(new Site("Little Friends", "Open XX:45 - XX:59\n Pages: -index -error"));
    sites.push_back(new Site("THANATOS", "Open XX:45 - XX:59\n Pages: -index"));
    // 30 - 59
    sites.push_back(new Site("Brutal Underground", "Open XX:30 - XX:59\n Pages: -index -signup"));
    sites.push_back(new Site("Red Triangle", "Open XX:30 - XX:59\n Pages: -index"));

    // Fake Sites
    sites.push_back(new Site("BathRoom Cams", "Fake site"));
    sites.push_back(new Site("Black Market", "Fake site"));
    sites.push_back(new Site("Burned At The Stake", "Fake site"));
    sites.push_back(new Site("Cheap Surgery", "Fake site"));
    sites.push_back(new Site("Chosen Awake", "Fake site"));
    sites.push_back(new Site("Corpses for Sell", "Fake site"));
    sites.push_back(new Site("Cotton Road", "Fake site"));
    sites.push_back(new Site("DeDo", "Fake site"));
    sites.push_back(new Site("DEEPDOTWEB", "Fake site"));
    sites.push_back(new Site("Dream Place", "Fake site"));
    sites.push_back(new Site("Family Drug Shop", "Fake site"));
    sites.push_back(new Site("Flame", "Fake site"));
    sites.push_back(new Site("Flesh Trade", "Fake site"));
    sites.push_back(new Site("Fuck You!", "Fake site"));
    sites.push_back(new Site("GAME CAT", "Fake site"));
    sites.push_back(new Site("Hackers4Hire", "Fake site"));
    sites.push_back(new Site("Hail Satan", "Fake site"));
    sites.push_back(new Site("Happy Family", "Fake site"));
    sites.push_back(new Site("Hot Burners", "Fake site"));
    sites.push_back(new Site("Illuminati", "Fake site"));
    sites.push_back(new Site("Legion", "Fake site"));
    sites.push_back(new Site("Passports R US", "Fake site"));
    sites.push_back(new Site("Roses Destruction", "Fake site"));
    sites.push_back(new Site("Secure Drop", "Fake site"));
    sites.push_back(new Site("SKYWEB", "Fake site"));
    sites.push_back(new Site("Snuff Portal", "Fake site"));
    sites.push_back(new Site("Tango Down", "Fake site"));
    sites.push_back(new Site("The 8th Sin", "Fake site"));
    sites.push_back(new Site("The Butcher", "Fake site"));
    sites.push_back(new Site("DeepVape", "Fake site"));
}

bool Data::Save()
{
    
}

bool Data::Load()
{
    // Check if Data.txt exists first
}


// Getters and setters
bool Data::GetSetting(string key)
{
    return settings.at(key);
}

void Data::ToggleSetting(string key)
{
    settings.at(key) = !settings.at(key);
}
