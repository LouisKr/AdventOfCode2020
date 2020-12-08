#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

struct Group
{
    std::vector<std::string> Answers;

    int GetAllYes()
    {
        std::map<char, int> Counter;

        for (const auto Person : Answers)
        {
            for (const auto Yes : Person)
            {
                Counter[Yes]++;
            }
        }
        return Counter.size();
    }
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


std::vector<Group> GetGroups()
{
    std::vector<Group> Groups;
    Group Current;

    std::vector<std::string> Data = GetData();
    for (const auto Line : Data)
    {
        if (Line == "")
        {
            Groups.push_back(Current);
            Current = Group();
        }
        else
            Current.Answers.push_back(Line);
    }
    Groups.push_back(Current);
    return Groups;
}

int main()
{
    std::vector<Group> Groups = GetGroups();

    int sum = 0;
    for (size_t i = 0; i < Groups.size(); i++)
    {
        sum += Groups[i].GetAllYes();
    }
    std::cout << sum;
}