#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>

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

std::vector<int> GetIntData()
{
    std::vector<int> IntData;

    std::vector<std::string> Data = GetData();

    for (const auto Line : Data)
    {
        IntData.push_back(std::stoi(Line));
    }

    return IntData;
}

int GetBiggest(const std::vector<int> &Data)
{
    int Biggest = 0;
    for (const auto Num : Data)
    {
        if (Num > Biggest)
            Biggest = Num;
    }
    return Biggest;
}

int GetJoltDifferences()
{
    std::vector<int> Data = GetIntData();

    int JoltOne = 0;
    int JoltThree = 0;
    int CurrentJolt = 0;

    int BiggestJolt = GetBiggest(Data);

    Data.push_back(BiggestJolt);

    while (CurrentJolt != BiggestJolt)
    {
        bool Found = false;
        for (const auto Jolt : Data)
        {
            if (Jolt - 1 == CurrentJolt)
            {
                JoltOne++;
                CurrentJolt = Jolt;
                Found = true;
                break;
            }
        }
        if (Found == true)
            continue;

        for (const auto Jolt : Data)
        {
            if (Jolt - 3 == CurrentJolt)
            {
                JoltThree++;
                CurrentJolt = Jolt;
                break;
            }
        }
    }
    JoltThree++;

    std::cout << JoltOne << "\n";
    std::cout << JoltThree << "\n";

    return JoltOne * JoltThree;
}

std::vector<int> GetReihenFolge()
{
    std::vector<int> ReihenFolge;

    std::vector<int> Data = GetIntData();

    int CurrentJolt = 0;
    int BiggestJolt = GetBiggest(Data);

    Data.push_back(BiggestJolt);

    ReihenFolge.push_back(0);
    while (CurrentJolt != BiggestJolt)
    {
        bool Found = false;
        for (const auto Jolt : Data)
        {
            if (Jolt - 1 == CurrentJolt)
            {
                ReihenFolge.push_back(Jolt);
                CurrentJolt = Jolt;
                Found = true;
                break;
            }
        }
        if (Found == true)
            continue;

        for (const auto Jolt : Data)
        {
            if (Jolt - 3 == CurrentJolt)
            {
                ReihenFolge.push_back(Jolt);
                CurrentJolt = Jolt;
                break;
            }
        }
    }
    ReihenFolge.push_back(BiggestJolt + 3);

    return ReihenFolge;
}

int64_t GetDistinctWays()
{
    std::vector<int> ReihenFolge = GetReihenFolge();
    std::vector<int> All;

    int Biggest = GetBiggest(ReihenFolge);
   
    for (size_t i = 0; i <= Biggest; i++)
    {
        bool found = false;
        for (const auto Num : ReihenFolge)
        {
            if (i == Num)
            {
                All.push_back(1);
                found = true;
                break;
            }
        }
        if (!found)
        {
            All.push_back(0);
        }
    }

    std::vector<int64_t> Add = {1};
    for (size_t i = 1; i < All.size(); i++)
    {
        if (i > 2)
        {
            Add.push_back((Add[i - 1] + Add[i - 2] + Add[i - 3]) * All[i]);
        }
        else
        {
            int tempAdd = 0;
            for (size_t p = 1; p <= i; p++)
            {
                tempAdd += Add[i - p];
            }
            Add.push_back(tempAdd * All[i]);
        }
    }
    return Add[Add.size() - 1];
}

int main()
{
    int64_t Answer = GetDistinctWays();

    std::cout << GetDistinctWays();

}