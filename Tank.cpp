#include "Tank.h"
#include "UserInterface.h"
#include <vector>

Tank::Tank(int width, int height)
:m_width(width), m_height(height)
{
	int r, c;
	for (r = 0, c = 0; r <= height; r++)
		bigPic[r][c] = '@';
	for (r = height, c = 1; c <= width; c++)
		bigPic[r][c] = '@';
	for (r = 0, c = 11; r <= height; r++)
		bigPic[r][c] = '@';

	for (r = 0; r < height; r++)
	for (c = 1; c <= width; c++)
		bigPic[r][c] = ' ';
}

Tank::~Tank()
{}

void Tank::clearTank()
{
	for (int r = 0; r < m_height; r++)
	for (int c = 1; c <= m_width; c++)
		bigPic[r][c] = ' ';
}

void Tank::display(Screen& screen, int x, int y)
{
	for (int r = y; r <= m_height; r++)
	for (int c = x; c <= m_width + 1; c++)
	{
		screen.gotoXY(c, r);
		screen.printChar(bigPic[r][c]);
	}
}

int Tank::rowsFilled()
{
	int x, y, count = 0;
	std::vector<int> rows;
	for (y = 17; y >= 0; y--)
	{
		for (x = 1; x <= 10; x++)
		{
			if (seePic(x, y) == ' ')
				break;
		}
		if (x == 11) // This value indicates that the row is filled.
		{
			count++;
			rows.push_back(y);
		}
	}
	
	while (rows.size() > 0)
	{
		int r = rows.back();
		rows.pop_back();
		for (; r >= 1; r--)
		for (x = 1; x <= 10; x++)
			changePic(x, r, seePic(x, r - 1));

		for (x = 1; x <= 10; x++) // The top row will always be empty after erasing a filled row.
			changePic(x, 0, ' ');
	}

	return count;
}