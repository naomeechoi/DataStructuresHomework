#pragma once
#include <string>
#include <vector>
#include <iostream>

class Item
{
public:
	Item() = default;

	bool ParseItemInfo(const std::string& infoStr)
	{
		if (infoStr.empty())
		{
			std::cout << infoStr << "Infomation is empty\n";
			return false;
		}

		std::vector<std::string> row;
		int left = 0;
		for (int i = 0; i < infoStr.size(); i++)
		{
			if (infoStr[i] == ',')
			{
				row.emplace_back(infoStr.substr(left, i - left));
				left = i + 1;
			}
		}
		row.emplace_back(infoStr.substr(left, infoStr.size() - left));

		if (row.size() < ATTRIBUTE_SIZE)
		{
			std::cout << infoStr << " Doesn't have full Infomation to parse\n";
			return false;
		}

		id = std::stoi(row[0]);
		name = std::move(row[1]);
		type = std::move(row[2]);
		cost = std::stoi(row[3]);
		rarity = std::stoi(row[4]);
		return true;
	}

	void PrintInfo()
	{
		std::cout << "id: " << id << "\n";
		std::cout << "name: " << name << "\n";
		std::cout << "type: " << type << "\n";
		std::cout << "cost: " << cost << "\n";
		std::cout << "rarity: " << rarity << "\n";
		std::cout << "\n";
	}

	inline const std::string& GetName() const { return name; }

private:
	static const int ATTRIBUTE_SIZE = 5;

	int id = 0;
	std::string name;
	std::string type;
	int cost = 0;
	int rarity = 0;
};