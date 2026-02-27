#include "Vector.h"
#include "Card.h"
#include <fstream>
#include <conio.h>

#define ESC_KEY 27
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ARROW 224

void LoadCards(Vector<Card*>& cardVec, const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
		return;

	std::string line;
	while (getline(file, line))
	{
		Card* newCard = new Card();
		if (!newCard)
			continue;

		if (!newCard->ParseCardInfo(line))
		{
			delete newCard;
			newCard = nullptr;
			continue;
		}
		else
		{
			cardVec.Add(newCard);
		}
	}
}

int main()
{
	Vector<Card*> cardVec;
	LoadCards(cardVec, "data.csv");
	int n = cardVec.Size();
	int idx = -1;

	std::cout << "You have " << n << " cards. Use the left and right arrow keys to view them.\nPress ESC to exit.\n\n";

	while (true)
	{
		int ch = _getch();
		if (ch == ESC_KEY)
		{
			std::cout << "End the program\n";
			break;
		}

		if (ch == ARROW)
		{
			int ch = _getch();
			if (ch == LEFT_ARROW)
			{
				idx--;
				if (idx < 0)
					idx = n - 1;
			}
			else if (ch == RIGHT_ARROW)
			{
				idx++;
				if (idx >= n)
					idx = 0;
			}
		}

		if(cardVec[idx])
			cardVec[idx]->PrintInfo();
	}

	for (int i = 0; i < n; i++)
	{
		if (!cardVec[i])
			continue;

		delete cardVec[i];
		cardVec[i] = nullptr;
	}
}