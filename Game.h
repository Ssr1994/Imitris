#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Tank.h"
#include "UserInterface.h"
#include <string>
#include <sstream>
#include "Piece.h"
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
	~Game();
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
	std::string printNum(int num);	// Generate a string from the number in right-justified fashion.
	void choosePiece(Piece*& p);	// Choose a random piece.
    // [Add other members as necessary.]

  private:
    Tank    m_tank;
    Screen  m_screen;
    int     m_level;
	int		m_score;
	int		m_rowsLeft;
	Piece*	m_currentPiece;
	Piece*	m_nextPiece;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
