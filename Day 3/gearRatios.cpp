#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int getSum(std::vector<int>& digits)
{
    int res = 0;
    int size = digits.size();
    for (int i = 0; i < size; ++i)
    {
        res += digits[i] * pow(10, size - i - 1);
    }

    return res;
}

int main()
{
    std::vector<std::vector<char>> input;

    std::ifstream file("input.txt");

    std::string line;
    while (getline(file, line))
    {
        std::vector<char> cv;
        for (char c : line)
            cv.push_back(c);

        input.push_back(cv);
    }

    int result = 0;
    for (int i = 0; i < input.size(); ++i)
    {
        std::vector<int> digits;
        for (int j = 0; j < input[i].size(); ++j)
        {
            if (isdigit(input[i][j]))
            {
                digits.push_back(input[i][j] - '0');
                if (j + 1 >= input[i].size())
                    input[i].push_back('.');
            }
            else if (!digits.empty())
            {
                bool symbol = false;
                int front = j - digits.size() - 1;
                if (front >= 0 && input[i][front] != '.' && !isdigit(input[i][front]))
                {
                    symbol = true;
                }
                if (input[i][j]  != '.' && !isdigit(input[i][j]))
                {
                    symbol = true;
                }
                if (i - 1 >= 0)
                {
                    for (int k = front; k <= j; ++k)
                    {
                        if (k >= 0 && k < input[i-1].size() && input[i-1][k] != '.' && !isdigit(input[i-1][k]))
                        {
                            symbol = true;
                            break;
                        }
                    }
                }
                if (i + 1 < input.size())
                {
                    for (int k = front; k <= j; ++k)
                    {
                        if (k >= 0 && k < input[i+1].size() && input[i+1][k] != '.' && !isdigit(input[i+1][k]))
                        {
                            symbol = true;
                            break;
                        }
                    }
                }

                if (symbol)
                {
                    result += getSum(digits);
                }

                digits.clear();
            }
        }
    }

    std::cout << result << '\n';

    return 0;
}