#ifndef TANK_INCLUDED
#define TANK_INCLUDED

class Screen;

class Tank
{
	int m_width;
	int m_height;
	char bigPic[19][12];	// This returns what is actually in the tank.
public:
	Tank(int width, int height);
	~Tank();
	void clearTank(); // clear the content in the tank
	int width() { return m_width; }
	int height() { return m_height; }
	void display(Screen& screen, int x, int y);
	char seePic(int x, int y) const { return bigPic[y][x]; }
	void changePic(int x, int y, char c) { bigPic[y][x] = c; }
	int rowsFilled(); // Returns how many rows are filled.
};

#endif // TANK_INCLUDED
