#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>

struct Bag
{
    std::string Name;
    //                     Anzahl, BagName  
    std::vector<std::pair<int, std::string>> Contains;
};

std::vector<std::string> GetData()
{
    std::vector<std::string> Data;

    std::string line;
    std::ifstream myfile("Data.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            Data.push_back(line);
        }
        myfile.close();
    }

    return Data;
}

Bag GetBag(std::string Line)
{
    Bag bag;

    std::stringstream stream = std::stringstream(Line);
    std::string Word;
    std::vector<std::string> Words;
    while (std::getline(stream, Word, ' '))
    {
        Words.push_back(Word);
    }

    bag.Name = Words[0] + " " + Words[1];

    for (size_t i = 4; i < Words.size(); i+=4)
    {
        std::pair<int, std::string> Pair;
        if (Words[i] == "no")
        {
            bag.Contains.push_back(Pair);
            continue;
        }
        Pair.first = std::stoi(Words[i]);
        Pair.second = Words[i + 1] + " " + Words[i + 2];
        bag.Contains.push_back(Pair);
    }

    return bag;
}

std::vector<Bag> GetBags()
{
    std::vector<Bag> Bags;

    std::vector<std::string> Data = GetData();

    for (const auto Line : Data)
    {
        Bags.push_back(GetBag(Line));
    }

    return Bags;
}

Bag getBagByName(const std::vector<Bag> &Bags, std::string bag)
{
    for (const auto Current : Bags)
    {
        if (Current.Name == bag)
            return Current;
    }
    return Bag();
}

bool CheckIfBagContainsBag(const std::vector<Bag> &Bags, Bag bag, std::string BagName)
{
    bool Contains = false;
    for (const auto Pair : bag.Contains)
    {
        if (Pair.second == BagName)
            return true;
        else
        {
            if (Contains == false)
            {
                if (CheckIfBagContainsBag(Bags, getBagByName(Bags, Pair.second), BagName) == true)
                    Contains = true;
            }
        }
    }
    return Contains;
}

int CanContain(const std::vector<Bag> &Bags, std::string BagName)
{
    int Contain = 0;
    for (const auto Bag : Bags)
    {
        Contain += CheckIfBagContainsBag(Bags, Bag, BagName);
    }
    return Contain;
}

int main()
{
    std::vector<Bag> Bags = GetBags();
    std::cout << CanContain(Bags, "shiny gold");
}