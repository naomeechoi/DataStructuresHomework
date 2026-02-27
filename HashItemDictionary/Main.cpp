#include "HashTable.h"
#include "Item.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void LoadItems(HashTable<Item*>& itemHash, const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
		return;

	std::string line;
	while (getline(file, line))
	{
		Item* newItem = new Item();

		if (!newItem->ParseItemInfo(line))
		{
			delete newItem;
			continue;
		}
		else
		{
            if (!itemHash.Add(newItem->GetName(), newItem))
            {
                delete newItem;
            }
		}
	}
}

int main()
{
	HashTable<Item*> itemHash;
	LoadItems(itemHash, "data.csv");
	int n = itemHash.Size();

	std::cout << "You have " << n << " cards. Use the left and right arrow keys to view them.\nPress ESC to exit.\n\n";
	std::cout << "Type 'Find itemName' to find the item\n";
	std::cout << "Type 'Remove itemName' to remove the item\n";
	std::cout << "Type 'List' to see the item list\n";
	std::cout << "Type 'Size' to see the item list size\n";
	std::cout << "Press ESC to exit.\n\n";

    std::string line;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string command;
        iss >> command;

        // 1) 명령어를 소문자로 변환
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        // 2) 아이템 이름 한 줄 전체 읽기
        std::string itemName;
        std::getline(iss, itemName);
        if (!itemName.empty() && itemName[0] == ' ')
            itemName.erase(0, 1); // 앞 공백 제거

        if (command == "find")
        {
            std::vector<std::pair<std::string, Item*>>::iterator finding;
            if (itemHash.Find(itemName, finding))
            {
                std::cout << "Found ITEM: " << itemName << "\n\n";
                if ((*finding).second)
                {
                    (*finding).second->PrintInfo();
                }
            }
            else
            {
                std::cout << "CANNOT FIND ITEM: " << itemName << "\n\n";
            }
        }
        else if (command == "remove")
        {
            if (itemHash.Delete(itemName))
            {
                std::cout << "DELETE SUCCESS, NOW YOU HAVE " << itemHash.Size() << " items. \n\n";
                continue;
            }
            else
            {
                std::cout << "CANNOT DELETE: " << itemName << "\n\n";
            }
        }
        else if (command == "list")
        {
            itemHash.ForEach([](Item*& p) {
                if (p)
                {
                    p->PrintInfo();
                }
            });
        }
        else if (command == "size")
        {
            std::cout << "YOU HAVE " << itemHash.Size() << " items. \n\n";
            continue;
        }
        else if (command == "exit" || command == "esc")
        {
            break;
        }
    }

	itemHash.ForEach([](Item*& p) {
        if (p)
        {
            delete p;
            p = nullptr;
        }
	});
}