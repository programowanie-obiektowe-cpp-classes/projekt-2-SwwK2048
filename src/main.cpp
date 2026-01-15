#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// biblioteka zewnętrzna
#include <fmt/core.h>

using namespace std;

class AuntSue
{
public:
    AuntSue(int id, const string& description) : ID(id) { parseDescription(description); }

    bool matches(const unordered_map< string, int >& reference, int zadanie) const
    {
        return all_of(properties.begin(), properties.end(), [&](const auto& p) {
            auto it = reference.find(p.first);
            if (it == reference.end())
                return true;
            if (zadanie == 2)
            {
                if (p.first == "cats" || p.first == "trees")
                    return p.second > it->second;

                if (p.first == "pomeranians" || p.first == "goldfish")
                    return p.second < it->second;
            }
            return p.second == it->second;
        });
    }

    int getID() const { return ID; }

private:
    int                          ID;
    unordered_map< string, int > properties;

    void parseDescription(const string& desc)
    {
        static const vector< string > keys = {"children",
                                              "cats",
                                              "samoyeds",
                                              "pomeranians",
                                              "akitas",
                                              "vizslas",
                                              "goldfish",
                                              "trees",
                                              "cars",
                                              "perfumes"};

        for (const auto& key : keys)
        {
            auto pos = desc.find(key + ":");
            if (pos != string::npos)
            {
                try
                {
                    properties[key] = stoi(desc.substr(pos + key.size() + 1));
                }
                catch (const exception&)
                {
                    throw runtime_error("Blad parsowania danych wejsciowych");
                }
            }
        }
    }
};

int main()
{
    try
    {
        vector< unique_ptr< AuntSue > > aunts;
        ifstream                        file("../../../data/500_Sue_aunts.txt");

        if (!file)
            throw runtime_error("Nie można otworzyć pliku");

        string line;
        int    id = 1;

        while (getline(file, line))
            aunts.push_back(make_unique< AuntSue >(id++, line));

        unordered_map< string, int > reference = {{"children", 3},
                                                  {"cats", 7},
                                                  {"samoyeds", 2},
                                                  {"pomeranians", 3},
                                                  {"akitas", 0},
                                                  {"vizslas", 0},
                                                  {"goldfish", 5},
                                                  {"trees", 3},
                                                  {"cars", 2},
                                                  {"perfumes", 1}};

        auto it = find_if(aunts.begin(), aunts.end(), [&](const auto& a) { return a->matches(reference,2); });

        if (it != aunts.end())
            fmt::print(" To jest ciocia, ktora przyslala prezent: {}\n", (*it)->getID());
        else
            fmt::print(" Nie znaleziono pasujacej cioci\n");
    }
    catch (const exception& e)
    {
        cerr << "Blad: " << e.what() << endl;
    }

    return 0;
}
