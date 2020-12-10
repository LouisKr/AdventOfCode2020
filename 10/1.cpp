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

int main()
{
    std::cout << GetJoltDifferences();
}