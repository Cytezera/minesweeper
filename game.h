#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <vector>
using namespace std; 
class Game : public QWidget{
	Q_OBJECT
public :
	Game(QWidget *parent = nullptr); 
private slots:
	void handleButtonClick(int row, int col );
private:
	QPushButton* buttons[8][8];
	QLabel* statusLabel; 
	int flag = 10;
	vector<vector<int>> grid = vector<vector<int>>(8,vector<int>(8,1)); 
	vector<pair<int,int>> bomb;
	int bombs; 
	void checkGame(int val);
	void placeBombs();
	void resetGame();	
	void setTiles();
};
#endif
