#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>

int main()
{
    std::ifstream file("input.txt");

    std::unordered_map<std::string, int> digitsMap = {
        { "one", 1 },
        { "two", 2 },
        { "three", 3 },
        { "four", 4 },
        { "five", 5 },
        { "six", 6 },
        { "seven", 7 },
        { "eight", 8 },
        { "nine", 9 },
    };

    int result = 0;
    std::string line;

    std::vector<int> lineValues;
    while (getline(file, line))
    {
        std::vector<int> digits;
        std::string digitStr;
        for (int i = 0; i < line.size(); ++i)
        {
            char c = line[i];
            if (isdigit(c))
            {
                digits.push_back(c - '0');
            }
            else if (isalpha(c))
            {
                digitStr += tolower(c);
                
                for (auto& dStr : digitsMap)
                {
                    std::string str = dStr.first;
                    
                    if (line.size() >= i + str.size())
                    {
                        if (line.substr(i, str.size()) == str)
                        {
                            digits.push_back(dStr.second);
                        }
                    }
                }
            }
        }

        if (!digits.empty())
        {
            int num = (digits[0] * 10) + digits[digits.size() - 1];
            result += num;
            lineValues.push_back(num);
        }
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}
