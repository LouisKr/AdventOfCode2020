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


long long int GetSmallest(std::vector<long long int> contiguous)
{
    long long int smallst = 9223372036854775807;
    for (size_t i = 0; i < contiguous.size(); i++)
    {
        if (contiguous[i] < smallst)
            smallst = contiguous[i];
    }
    return smallst;
}

long long int GetBiggest(std::vector<long long int> contiguous)
{
    long long int biggest = 0;
    for (size_t i = 0; i < contiguous.size(); i++)
    {
        if (contiguous[i] > biggest)
            biggest = contiguous[i];
    }
    return biggest;
}

void TestForWeakness(int index, const std::vector<long long int> &Data, long long int InValidNum)
{
    long long int Add = 0;
    for (size_t i = index; i < Data.size(); i++)
    {
        Add += Data[i];

        if (Add == InValidNum)
        {
            std::vector<long long int> contiguous;

            for (size_t p = index; p < Data.size(); p++)
            {
                if (p <= i)
                {
                    contiguous.push_back(Data[p]);
                }
                else
                    break;
            }

            if (contiguous.size() > 1)
            {
                std::cout << "Found: \n";
                for (size_t p = 0; p < contiguous.size(); p++)
                {
                    std::cout << contiguous[p] << "\n";
                }
                std::cout << "\n";
            }

            long long int add = GetSmallest(contiguous) + GetBiggest(contiguous);
            std::cout << add << "\n";
        }
        else if (Add > InValidNum)
        {
            break;
        }
    }
}

void FindWeakness(int InValidNum)
{
    std::vector<long long int> Data = GetDataAsNum();

    for (size_t i = 0; i < Data.size(); i++)
    {
        TestForWeakness(i, Data, InValidNum);
    }
}

int main()
{
    int InValidNum = GetInValidNum(25);
    FindWeakness(InValidNum);
}