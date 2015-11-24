#include "Piece.h"
#include <cmath>
#include <stack>

Piece::Piece()
:m_orientation(0), m_x(3), m_y(0)
{}

bool Piece::changeOri(Tank& tank)
{
	int ori = m_orientation;
	if (ori < 3)
		ori++;
	else
		ori = 0;

	int r, c;
	for (r = 0; r < 4; r++)
	for (c = 0; c < 4; c++)
	{
		if (seePiece(ori, r, c) == '#' && tank.seePic(m_x + 1 + c, m_y + r) != ' ' 
			&& tank.seePic(m_x + 1 + c, m_y + r) != '#')
			return false;
	}
	for (r = 0; r < 4; r++)
	for (c = 0; c < 4; c++)
	{
		if (tank.seePic(m_x + 1 + c, m_y + r) == '#')
			tank.changePic(m_x + 1 + c, m_y + r, ' ');
		if (seePiece(ori, r, c) == '#')
			tank.changePic(m_x + 1 + c, m_y + r, seePiece(ori, r, c));
	}
	m_orientation = ori;
	return true;
}

bool Piece::putInTank(Tank& tank) const
{
	bool success = true;
	for (int r = 0; r < 4; r++)
	for (int c = 0; c < 4; c++)
	{
		if (seePiece(0, r, c) == '#')
		{
			if (tank.seePic(4 + c, r) != ' ')
				success = false;

			tank.changePic(4 + c, r, '#');
		}
	}
	return success;
}

void Piece::draw(Screen& screen) const
{
	for (int r = 0; r < 4; r++)
	for (int c = 0; c < 4; c++)
	{
		screen.gotoXY(16 + c, 4 + r);
		screen.printChar(seePiece(0, r, c));
	}
}

bool Piece::downShift(Tank& tank)
{
	int r, c;
	for (r = 3; r >= 0; r--)
	for (c = 0; c < 4; c++)
	{
		if (m_y + r > 18)	// in case that it is out of the tank.
			continue;
		if (tank.seePic(m_x + 1 + c, m_y + r) == '#' && (m_y + r + 1 >= 18 || tank.seePic(m_x + 1 + c,
			m_y + r + 1) == '$' || tank.seePic(m_x + 1 + c, m_y + r + 1) == '*'))
			return false;
	}

	for (r = 3; r >= 0; r--)
	for (c = 0; c < 4; c++)
	{
		if (tank.seePic(m_x + 1 + c, m_y + r) == '#')
		{
			tank.changePic(m_x + 1 + c, m_y + r, ' ');
			tank.changePic(m_x + 1 + c, m_y + r + 1, '#');
		}
	}
	m_y++;
	return true;
}

bool Piece::leftShift(Tank& tank)
{
	int r, c;
	for (c = 0; c < 4;c++)
	for (r = 0; r < 4; r++)
	{
		if (m_x + 1 + c < 0)
			continue;
		if (tank.seePic(m_x + 1 + c, m_y + r) == '#' && (m_x + c <= 0 || tank.seePic(m_x + c, m_y + r) == '$'
			|| tank.seePic(m_x + c, m_y + r) == '*'))
			return false;
	}

	for (c = 0; c < 4; c++)
	for (r = 0; r < 4; r++)
	{
		if (tank.seePic(m_x + 1 + c, m_y + r) == '#')
		{
			tank.changePic(m_x + 1 + c, m_y + r, ' ');
			tank.changePic(m_x + c, m_y + r, '#');
		}
	}
	m_x--;
	return true;
}

bool Piece::rightShift(Tank& tank)
{
	int r, c;
	for (c = 3; c >= 0; c--)
	for (r = 0; r < 4; r++)
	{
		if (m_x + 1 + c > 11)
			continue;
		if (tank.seePic(m_x + 1 + c, m_y + r) == '#' && (m_x + c + 2 >= 11 || tank.seePic(m_x + c + 2, m_y + r) 
			== '$' || tank.seePic(m_x + c + 2, m_y + r) == '*'))
			return false;
	}

	for (c = 3; c >= 0; c--)
	for (r = 0; r < 4; r++)
	{
		if (tank.seePic(m_x + 1 + c, m_y + r) == '#')
		{
			tank.changePic(m_x + 1 + c, m_y + r, ' ');
			tank.changePic(m_x + c + 2, m_y + r, '#');
		}
	}
	m_x++;
	return true;
}

void Piece::reside(Tank& tank) const
{
	for (int y = m_y; y < m_y + 4;y++)
	for (int x = m_x + 1; x < m_x + 5; x++)
	{
		if (tank.seePic(x, y) == '#')
			tank.changePic(x, y, '$');
	}
}

char Piece_I::ori_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ '#', '#', '#', '#' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_I::ori_1[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' }
};

char Piece_I::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
	case 2:
		return ori_0[r][c];
	case 1:
	case 3:
		return ori_1[r][c];
	}
	exit(1);
}

char Piece_L::ori_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ '#', '#', '#', ' ' },
	{ '#', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_L::ori_1[4][4] = {
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_L::ori_2[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ '#', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_L::ori_3[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', '#', ' ' }
};

char Piece_L::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
		return ori_0[r][c];
	case 1:
		return ori_1[r][c];
	case 2:
		return ori_2[r][c];
	case 3:
		return ori_3[r][c];
	}
	exit(1);
}

char Piece_J::ori_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', '#', '#' },
	{ ' ', ' ', ' ', '#' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_J::ori_1[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', '#', '#', ' ' }
};
char Piece_J::ori_2[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', '#', '#' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_J::ori_3[4][4] = {
	{ ' ', '#', '#', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};

char Piece_J::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
		return ori_0[r][c];
	case 1:
		return ori_1[r][c];
	case 2:
		return ori_2[r][c];
	case 3:
		return ori_3[r][c];
	}
	exit(1);
}

char Piece_T::ori_0[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ '#', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_T::ori_1[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_T::ori_2[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ '#', '#', '#', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_T::ori_3[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ '#', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};

char Piece_T::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
		return ori_0[r][c];
	case 1:
		return ori_1[r][c];
	case 2:
		return ori_2[r][c];
	case 3:
		return ori_3[r][c];
	}
	exit(1);
}

char Piece_O::ori_0[4][4] = {
	{ '#', '#', ' ', ' ' },
	{ '#', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};

char Piece_O::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return ori_0[r][c];
	}
	exit(1);
}

char Piece_S::ori_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ '#', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_S::ori_1[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', ' ', ' ' }
};

char Piece_S::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
	case 2:
		return ori_0[r][c];
	case 1:
	case 3:
		return ori_1[r][c];
	}
	exit(1);
}

char Piece_Z::ori_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ '#', '#', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_Z::ori_1[4][4] = {
	{ ' ', ' ', '#', ' ' },
	{ ' ', '#', '#', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};

char Piece_Z::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
	case 2:
		return ori_0[r][c];
	case 1:
	case 3:
		return ori_1[r][c];
	}
	exit(1);
}

char Piece_Vapor::ori_0[4][4] = {
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};

char Piece_Vapor::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return ori_0[r][c];
	}
	exit(1);
}

void Piece_Vapor::reside(Tank& tank) const
{
	for (int x = m_x + 2; x <= m_x + 3; x++)
	for (int y = fmax(m_y - 2, 0); y <= fmin(m_y + 2, 17); y++)
		tank.changePic(x, y, ' ');
}

char Piece_Foam::ori_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};

char Piece_Foam::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return ori_0[r][c];
	}
	exit(1);
}

void Piece_Foam::reside(Tank& tank) const
{
	int r, c;
	// draw the boundary of explosion
	if (m_y - 2 >= 0)
	{
		for (c = fmax(m_x - 1, 1); c < fmin(m_x + 6, 11); c++)
		if (tank.seePic(c, m_y - 2) == ' ')
			tank.changePic(c, m_y - 2, 'b');
	}
	if (m_y + 4 < 18)
	{
		for (c = fmax(m_x - 1, 1); c < fmin(m_x + 6, 11); c++)
		if (tank.seePic(c, m_y + 4) == ' ')
			tank.changePic(c, m_y + 4, 'b');
	}
	if (m_x - 1 > 0)
	{
		for (r = fmax(m_y - 1, 0); r < fmin(m_y + 4, 18); r++)
		if (tank.seePic(m_x - 1, r) == ' ')
			tank.changePic(m_x - 1, r, 'b');
	}
	if (m_x + 5 < 11)
	{
		for (r = fmax(m_y - 1, 0); r < fmin(m_y + 4, 18); r++)
		if (tank.seePic(m_x + 5, r) == ' ')
			tank.changePic(m_x + 5, r, 'b');
	}

	tank.changePic(m_x + 2, m_y + 1, ' '); // Set '#' to ' ' for convenience.
	explode(tank, m_x + 2, m_y + 1);

	// erase the boundary of explosion
	for (r = 0; r < 18; r++)
	for (c = 1; c < 11; c++)
	{
		if (tank.seePic(c, r) == 'b')
			tank.changePic(c, r, ' ');
	}
}

void Piece_Foam::explode(Tank& tank, int x, int y) const
{
	if (tank.seePic(x, y) != ' ')
		return;
	else
	{
		tank.changePic(x, y, '*');
		explode(tank, x + 1, y);
		explode(tank, x - 1, y);
		explode(tank, x, y + 1);
		explode(tank, x, y - 1);
	}
}

char Piece_Crazy::ori_0[4][4] = {
	{ '#', ' ', ' ', '#' },
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' }
};
char Piece_Crazy::ori_1[4][4] = {
	{ ' ', ' ', ' ', '#' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', ' ', '#' }
};
char Piece_Crazy::ori_2[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ '#', ' ', ' ', '#' }
};
char Piece_Crazy::ori_3[4][4] = {
	{ '#', ' ', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ '#', ' ', ' ', ' ' }
};

char Piece_Crazy::seePiece(int ori, int r, int c) const
{
	switch (ori)
	{
	case 0:
		return ori_0[r][c];
	case 1:
		return ori_1[r][c];
	case 2:
		return ori_2[r][c];
	case 3:
		return ori_3[r][c];
	}
	exit(1);
}

bool Piece_Crazy::leftShift(Tank& tank)
{
	return Piece::rightShift(tank);
}

bool Piece_Crazy::rightShift(Tank& tank)
{
	return Piece::leftShift(tank);
}