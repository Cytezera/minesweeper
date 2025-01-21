#include "game.h"
#include <QGridLayout>
Game::Game(QWidget *parent)
	: QWidget(parent){
	bombs = 10 ;
	auto* layout = new GridLayout(this); 
	statusLabel = new QLabel("Flags: " + flag , this ) ; 
	layout->addWidget(statusLabel,0,0,1,1);
	for (int row = 0; row < 8; row ++ ){
		for (int col = 0 ; col < 8 ; col++ ) {
			buttons[row][col] = new QPushButton("",this); 
			buttons[row][col]->setFixedSize(10,10); 
			layout->addWidget(buttons[row][col],row + 1, col ) ; 
			connect(buttons[row][col], &QPushButton::clicked , this ,[=](){
				handleButtonClick(row,col);		
			}); 

		}
	}
	setLayout(layout);
	setWindowTitle("Minesweeper"); 
	resize(320,400); 
	placeBombs();
	setTiles();
}

void Gmae::handleButtonClick(int row, int col){
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (!button || !button->text().isEmpty()) {
		return; 
	}
	int val = grid[row][col]; 
	std::string str = std::to_string(val);
	button->setText(str); 	
	checkGame(val);
}
void Game::checkGame(int val){
	if (val != -1 ) return ; 
	statusLabel->setText("Game Over");
}
void Game::placeBombs(){
	for (int i = 0 ; i < bombs; i ++ ) {
		int bombX , bombY; 
		do{
			bombX = rand() % 8; 
			bombY = rand() % 8 ; 

		}while(find(bomb.begin(),bomb.end(),make_pair(bombX,bombY)) != bomb.end());	
		
		bomb.push_back(make_pair(bombX,bombY);
		grid[bombX][bombY] = -1; 
	}	
}
void Game::setTiles(){
	const vector<pair<int,int>> dir=  {
		{-1,-1},
		{-1,0},
		{-1,1},
		{0,1},
		{0,-1},
		{1,1},
		{1,-1},
		{1,0},
	};
	for (int i = 0 ; i < 8 ; i ++ ){
		for (int j = 0 ; j < 0 ; j ++ ) {
			if (grid[i][j] == -1 ) continue ;
			int count = 0 ; 
			for (auto& [row,col] : dir ){
				int newI = i + row ; 
				int newJ = j + col ; 
				if (newI >= 0  && newI < 8 && newJ >= 0 && newJ < 8){
					if (grid[newI][newJ] == -1 ) count ++ ; 
				}
			}
			grid[i][j] = count ;
		}
	}	
}
void Game::resetGame(){
	for (int i = 0 ; i < 8; i ++ ) {
		for (int j = 0 ; j < 0 ; j ++) {
			buttons[i][j]->setText(""); 	
		}
	}	
	placeBombs();
	setTiles();
}
