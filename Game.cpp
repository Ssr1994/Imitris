#include "Game.h"
#include "Tank.h"
#include "UserInterface.h"
#include <string>
#include <cmath>
using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int TANK_X = 0;
const int TANK_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_rowsLeft(5), m_score(0),
m_tank(width, height)
{}

Game::~Game()
{
	delete m_currentPiece;
	delete m_nextPiece;
}

void Game::play()
{
	m_tank.display(m_screen, TANK_X, TANK_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Imitris!");
    waitForEnter();  // [in UserInterface.h]
	m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
	m_screen.printString("Next piece:");
	choosePiece(m_currentPiece);
    for(;;)
    {
		choosePiece(m_nextPiece);
		m_nextPiece->draw(m_screen);
		if (!m_currentPiece->putInTank(m_tank))
		{
			m_tank.display(m_screen, TANK_X, TANK_Y);
			break; // Game over.
		}

		for (;;)
		{
			m_tank.display(m_screen, TANK_X, TANK_Y);
			int endTime = getMsecSinceStart()+ fmax(1000 - (100 * (m_level - 1)), 100);
			while (getMsecSinceStart() < endTime)
			{
				char ch;
				if (getCharIfAny(ch))
				{
					switch (ch)
					{
					case ' ':
						for (;;)
						{
							if (!m_currentPiece->downShift(m_tank))
							{
								endTime = 0;
								break;
							}
						}
						break;
					case 'q':
					case 'Q':
						displayPrompt("Game Over!  Press the Enter key to exit!");
						waitForEnter();
						return;
					case ARROW_LEFT:
						if (m_currentPiece->leftShift(m_tank))
							m_tank.display(m_screen, TANK_X, TANK_Y);
						break;
					case ARROW_RIGHT:
						if (m_currentPiece->rightShift(m_tank))
							m_tank.display(m_screen, TANK_X, TANK_Y);
						break;
					case ARROW_UP:
						if (m_currentPiece->changeOri(m_tank))
							m_tank.display(m_screen, TANK_X, TANK_Y);
						break;
					case ARROW_DOWN:
						if (m_currentPiece->downShift(m_tank))
						{
							endTime = getMsecSinceStart() + fmax(1000 - (100 * (m_level - 1)), 100);
							m_tank.display(m_screen, TANK_X, TANK_Y);
						}
						break;
					default:
						;
					}
				}
			}
			discardPendingKeys();

			if (!m_currentPiece->downShift(m_tank))
			{
				m_currentPiece->reside(m_tank);
				switch (m_tank.rowsFilled())
				{
				case 1:
					m_score += 100;
					m_rowsLeft--;
					break;
				case 2:
					m_score += 200;
					m_rowsLeft -= 2;
					break;
				case 3:
					m_score += 400;
					m_rowsLeft -= 3;
					break;
				case 4:
					m_score += 800;
					m_rowsLeft -= 4;
					break;
				case 5:
					m_score += 1600;
					m_rowsLeft -= 5;
					break;
				default:
					;
				}
				m_tank.display(m_screen, TANK_X, TANK_Y);
				displayStatus();
				delete m_currentPiece;
				m_currentPiece = m_nextPiece;
				break;
			}	
		}

        if ( ! playOneLevel())
            continue;
		m_level++;
		m_rowsLeft = 5 * m_level;
		m_score = 0;
		m_tank.clearTank();
		delete m_nextPiece;
		choosePiece(m_nextPiece);
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
		displayStatus();
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{	
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printString("Score:     " + printNum(m_score));
	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printString("Rows left: " + printNum(m_rowsLeft));
	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	m_screen.printString("Level:     " + printNum(m_level));
}

bool Game::playOneLevel()
{
    return m_rowsLeft <= 0;
}

string Game::printNum(int num)
{
	if (num < 0)
		num = 0;
	ostringstream convert;
	convert << num;
	string temp = convert.str();
	string spaces;
	for (int i = 0; i < 7 - temp.size(); i++)
		spaces += " ";
	return spaces + temp;
}

void Game::choosePiece(Piece*& p)
{
	switch (randPieceType())
	{
	case PIECE_I:
		p = new Piece_I;
		break;
	case PIECE_L:
		p = new Piece_L;
		break;
	case PIECE_J:
		p = new Piece_J;
		break;
	case PIECE_T:
		p = new Piece_T;
		break;
	case PIECE_O:
		p = new Piece_O;
		break;
	case PIECE_S:
		p = new Piece_S;
		break;
	case PIECE_Z:
		p = new Piece_Z;
		break;
	case PIECE_VAPOR:
		p = new Piece_Vapor;
		break;
	case PIECE_FOAM:
		p = new Piece_Foam;
		break;
	case PIECE_CRAZY:
		p = new Piece_Crazy;
		break;
	default:
		exit(1);
	}
}