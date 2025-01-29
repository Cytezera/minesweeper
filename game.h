#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <vector>
using namespace std; 

class Buttons : public QPushButton{
	Q_OBJECT 
public:
	Buttons( QWidget *parent = nullptr) 
		:QPushButton(parent){}

signals:
	void leftClicked(); 
	void rightClicked();
protected: 
	void mousePressEvent(QMouseEvent *event) override; 
private: 
};

class Game : public QWidget{
	Q_OBJECT
public :
	Game(QWidget *parent = nullptr); 
private slots:

	void handleLeftButtonClick(int row, int col );
	void handleRightButtonClick(int row, int col); 
private:
	QLabel* statusLabel; 
	QLabel* timer;
	Buttons* buttons[8][8];
	int flag = 10;
	int bombsInPlay = 10 ;
	vector<vector<int>> grid = vector<vector<int>>(8,vector<int>(8,0)); 
	vector<pair<int,int>> bomb;
	int bombs; 
	void checkGame(int val);
	void placeBombs();
	void resetGame();	
	void setTiles();
	void openPopUp();	
	void displayWin();

};

#endif
