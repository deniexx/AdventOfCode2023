#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, int> bagConfiguration =
{
    {"red", 12 },
    {"green", 13},
    {"blue", 14}
};

bool isValidGame(std::string line, std::unordered_map<std::string, int>& fewest)
{
    bool ret = true;
	while (!line.empty())
	{
		std::size_t end = line.find(';');
		end = end == 0 ? line.length() : end;
		std::string substr = line.substr(0, end);
		line.erase(0, substr.length() + 1);

		while (!substr.empty())
		{
			std::string s = substr.substr(0, substr.find(','));
			std::string col;
			std::vector<int> nums;
			for (char c : s)
			{
				if (isdigit(c))
				{
					nums.push_back(c - '0');
				}
				else if (isalpha(c))
				{
					col += c;
				}
			}
			int res = 0;
			int size = nums.size();
			for (int i = 0; i < size; ++i)
			{
				res += nums[i] * pow(10, size - i - 1);
			}
			substr.erase(0, s.length() + 1);

            if (fewest[col] < res)
            {
                fewest[col] = res;
            }
			
            if (bagConfiguration.find(col) != bagConfiguration.end())
            {
                if (bagConfiguration[col] < res)
                {
                    ret = false;
                }
            }
		}
	}

	return ret;
}

int main()
{
	std::ifstream file("input.txt");

	int result = 0;
    int power = 0;
	std::string line;
	while (getline(file, line))
	{
        std::unordered_map<std::string, int> fewest = 
        {
            {"red", 0},
            {"green", 0},
            {"blue", 0} 
        };

		line.erase(0, 5);
		std::vector<int> gameIdDigits;
		char c = line[0];
		while (isdigit(c))
		{
			gameIdDigits.push_back(c - '0');
			line.erase(0, 1);
			c = line[0];
		}

		if (isValidGame(line, fewest))
		{
            int gameId = 0;
            int size = gameIdDigits.size();
            for (int i = 0; i < size; ++i)
            {
                gameId += gameIdDigits[i] * pow(10, size - i - 1);
            }
            result += gameId;
		}

        power += fewest["red"] * fewest["green"] * fewest["blue"];
	}

    std::cout << "Result: " << result << '\n';
    std::cout << "Power: " << power << '\n';

	return 0;
}