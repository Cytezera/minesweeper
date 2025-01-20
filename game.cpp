#include "game.h"

Gmae::Game(QWidget *parent)
	: QWidget(parent){
	auto* layout = new GridLayout(this); 
	statusLabel = new QLabel("Flags: " + flag , this ) ; 
	layout->addWidget(statusLabel,0,0,1,1);
	for (int i = 0; row < 8; i ++ ){
		for (int j = 0 ; col < 8 ; j ++ ) {
			buttons[row][col] = new QPushButton("",this); 
			buttons[row][col]->setFixedSize(10,10); 
			layout->addWidget(buttons[row][col],row + 1, col ) ; 
			connect(buttons[row][col], &QPushButton::clicked , this , &Game::handleButtonClick()); 
		}
	}
	setLayout(layout);
	setWindowTitle("Minesweeper"); 
	resize(320,400); 
	placeBombs();
}

void Gmae::handleButtonClick(){
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (!button){
		return 
	}

}
void Game::placeBombs(){
	
}
void Game::resetGame(){
	
}
