#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Range
{
    double Lowest;
    double Highest;
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

Range GetHalf(Range range, char split)
{
    if (split == 'F' or split == 'L')
        return { range.Lowest, range.Lowest + (int)((range.Highest - range.Lowest) / 2) };
    else if (split == 'B' or split == 'R')
        return { range.Lowest + std::round((range.Highest - range.Lowest) / 2), range.Highest };
    else
        return range;
}

int GetRow(std::string partitioning)
{
    Range Row = { 0, 127 };
    for (size_t i = 0; i < 8; i++)
    {
        Row = GetHalf(Row, partitioning[i]);
    }
    if (partitioning[6] == 'F')
        return std::round(Row.Lowest);
    else if (partitioning[6] == 'B')
        return std::round(Row.Highest);
}

int GetColumn(std::string partitioning)
{
    Range Column{ 0, 7 };
    for (size_t i = 7; i < partitioning.size(); i++)
    {
        Column = GetHalf(Column, partitioning[i]);
    }
    if (partitioning[9] == 'L')
        return std::round(Column.Lowest);
    else if (partitioning[9] == 'R')
        return std::round(Column.Highest);
}

int GetSeatID(std::string partitioning)
{
    int Row = GetRow(partitioning);

    int Column = GetColumn(partitioning);

    return (Row * 8) + Column;
}

void HasNabor(std::vector<int> Ids, int Id)
{
    if (std::find(Ids.begin(), Ids.end(), Id + 1) == Ids.end())
    {
        std::cout << Id + 1 << "\n";
    }

    if (std::find(Ids.begin(), Ids.end(), Id - 1) == Ids.end())
    {
        std::cout << Id - 1 << "\n";
    }
}

int main()
{
    std::vector<std::string> Data = GetData();
    std::string t = Data[Data.size() - 1];

    std::vector<int> Ids;
    for (size_t i = 0; i < Data.size(); i++)
    {
        Ids.push_back(GetSeatID(Data[i]));
    }
    for (size_t i = 0; i < Ids.size(); i++)
    {
        HasNabor(Ids, Ids[i]);
    }
}