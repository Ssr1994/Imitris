#ifndef PIECE_H
#define PIECE_H
#include "randPieceType.h"
#include "UserInterface.h"
#include "Tank.h"

class Piece
{
protected:
	Piece();
	int m_orientation;
	int m_x;
	int m_y;

public:
	bool changeOri(Tank& tank); // Rotation.
	bool putInTank(Tank& tank) const;
	void draw(Screen& screen) const; // Used only for drawing the next piece.
	virtual void reside(Tank& tank) const;	// Used when the falling piece stops.
	bool downShift(Tank& tank);
	virtual bool leftShift(Tank& tank);
	virtual bool rightShift(Tank& tank);
	virtual char seePiece(int ori, int r, int c) const = 0; // See what the piece looks like.
};

class Piece_I :public Piece
{
	static char ori_0[4][4];
	static char ori_1[4][4];
public:
	Piece_I() {};
	virtual char seePiece(int ori, int r, int c) const;
};

class Piece_L :public Piece
{
	static char ori_0[4][4];
	static char ori_1[4][4];
	static char ori_2[4][4];
	static char ori_3[4][4];
public:
	Piece_L() {};
	virtual char seePiece(int ori, int r, int c) const;
}; 

class Piece_J :public Piece
{
	static char ori_0[4][4];
	static char ori_1[4][4];
	static char ori_2[4][4];
	static char ori_3[4][4];
public:
	Piece_J() {};
	virtual char seePiece(int ori, int r, int c) const;
}; 

class Piece_T :public Piece
{
	static char ori_0[4][4];
	static char ori_1[4][4];
	static char ori_2[4][4];
	static char ori_3[4][4];
public:
	Piece_T() {};
	virtual char seePiece(int ori, int r, int c) const;
}; 

class Piece_O :public Piece
{
	static char ori_0[4][4];
public:
	Piece_O() {};
	virtual char seePiece(int ori, int r, int c) const;
}; 

class Piece_S :public Piece
{
	static char ori_0[4][4];
	static char ori_1[4][4];
public:
	Piece_S() {};
	virtual char seePiece(int ori, int r, int c) const;
}; 

class Piece_Z :public Piece
{
	static char ori_0[4][4];
	static char ori_1[4][4];
public:
	Piece_Z() {};
	virtual char seePiece(int ori, int r, int c) const;
}; 

class Piece_Vapor :public Piece
{
	static char ori_0[4][4];
public:
	Piece_Vapor() {};
	virtual char seePiece(int ori, int r, int c) const;
	virtual void reside(Tank& tank) const; // Erasion.
}; 

class Piece_Foam :public Piece
{
	static char ori_0[4][4];
public:
	Piece_Foam() {};
	virtual char seePiece(int ori, int r, int c) const;
	virtual void reside(Tank& tank) const;
	void explode(Tank& tank, int x, int y) const; // A helper function.
}; 

class Piece_Crazy :public Piece
{
	static char ori_0[4][4];
	static char ori_1[4][4];
	static char ori_2[4][4];
	static char ori_3[4][4];
public:
	Piece_Crazy() {};
	virtual char seePiece(int ori, int r, int c) const;
	virtual bool leftShift(Tank& tank);
	virtual bool rightShift(Tank& tank);
};


#endif