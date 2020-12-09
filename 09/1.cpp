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

std::vector<long long int> GetDataAsNum()
{
    std::vector<long long int> NumData;
    std::vector<std::string> Data = GetData();
    for (size_t i = 0; i < Data.size(); i++)
    {
        NumData.push_back(std::stoll(Data[i]));
    }
    return NumData;
}

bool IsValid(int Num, const std::vector<long long int> &Last5)
{
    for (const auto x : Last5)
    {
        for (const auto y : Last5)
        {
            if (x + y == Num)
                return true;
        }
    }
    return false;
}

int GetInValidNum(int preamble)
{
    std::vector<long long int> Data = GetDataAsNum();
    
    for (size_t i = preamble; i < Data.size(); i++)
    {
        std::vector<long long int> Last5;
        for (size_t p = preamble; p > 0; p--)
        {
            Last5.push_back(Data[i - p]);
        }

        if (IsValid(Data[i], Last5) == false)
            return Data[i];
    }

    return 0;
}

int main()
{
    std::cout << GetInValidNum(25);
}