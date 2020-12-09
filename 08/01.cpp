#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>

struct Instruction
{
    std::string Order;
    int Value;
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

std::vector<Instruction> GetInstructions()
{
    std::vector<Instruction> Instructions;

    std::vector<std::string> Data = GetData();

    Instruction CurrentInstruction;
    for (const auto Line : Data)
    {
        CurrentInstruction.Order = Line.substr(0, Line.find(' '));
        CurrentInstruction.Value = std::stoi(Line.substr(Line.find(' '), Line.size() - 1));
        Instructions.push_back(CurrentInstruction);
    }

    return Instructions;
}

bool AllreadyProccesd(const std::vector<int> &IndexCounter, int i)
{
    for (const auto index : IndexCounter)
    {
        if (i == index)
            return true;
    }
    return false;
}

int GetAcc()
{
    std::vector<Instruction> Instructions = GetInstructions();
    std::vector<int> IndexCounter;
    int NextIndex = 0;

    int Acc = 0;
    while (!AllreadyProccesd(IndexCounter, NextIndex))
    {
        IndexCounter.push_back(NextIndex);
        Instruction instruction = Instructions[NextIndex];
        if (instruction.Order == "acc")
        {
            Acc += instruction.Value;
            NextIndex++;
        }
        else if (instruction.Order == "jmp")
        {
            NextIndex += instruction.Value;
        }
        else if (instruction.Order == "nop")
        {
            NextIndex++;
        }
    }
    return Acc;
}

int main()
{
    std::cout << GetAcc();
}