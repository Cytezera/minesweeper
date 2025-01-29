#include <QApplication>
#include <algorithm>
#include "game.h"
#include <QGridLayout>
Game::Game(QWidget *parent)
	: QWidget(parent){
	bombs = 10 ;
	auto* layout = new QGridLayout(this); 
	statusLabel = new QLabel("", this ) ; 
	timer = new QLabel("",this);
	layout->addWidget(statusLabel,0,0,1,1);
	layout->addWidget(timer,0,4,1,1);
	for (int row = 0; row < 8; row ++ ){
		for (int col = 0 ; col < 8 ; col++ ) {
			buttons[row][col] = new Buttons(this); 
			buttons[row][col]->setFixedSize(50,50); 
			layout->addWidget(buttons[row][col],row + 1, col ) ; 
			connect(buttons[row][col],&Buttons::leftClicked , this, [=](){
				this->handleLeftButtonClick(row,col);	
			       });			
			connect(buttons[row][col],&Buttons::rightClicked, this , [=](){
				this->handleRightButtonClick(row,col);
			       });
		}
	}
	setLayout(layout);
	setWindowTitle("Minesweeper"); 
	resize(500,500); 
	statusLabel->setText("Flags: " + QString::number(flag));
	timer->setText("Test");
	placeBombs();
	setTiles();
}


void Buttons::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton){
		emit leftClicked();
	}else if (event->button() == Qt::RightButton){
		emit rightClicked();
	}
	QPushButton::mousePressEvent(event);
}
void Game::handleRightButtonClick(int row, int col){
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button->text() == (QString::fromUtf8("\xF0\x9F\x9A\xA9"))){
		button->setText("");	
		flag += 1 ;
		if (grid[row][col] == -1 ){
			bombsInPlay += 1 ; 
		}
	}else if (flag == 0 ) {
		return;	
	}
	else if (button->text().isEmpty()){
		QFont font = button->font();
		button->setText(QString::fromUtf8("\xF0\x9F\x9A\xA9"));		
		flag -= 1 ; 
		if (grid[row][col] == -1 ) {
			bombsInPlay -= 1 ;
		}
	}
	if (bombsInPlay == 0) {
		displayWin(); 
	}
	statusLabel->setText("Flags: " + QString::number(flag) + "Bombs left: " + QString::number(bombsInPlay));	
}
void Game::handleLeftButtonClick(int row, int col){
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (!button || !button->text().isEmpty()) {
		return; 
	}
	int val = grid[row][col]; 

	if (val == -1 ) {
		QFont font = button->font();
		font.setPointSize(12);
		button->setText(QString::fromUtf8("\xF0\x9F\x92\xA3"));
	}else {
		button->setText(QString::number(val)); 	

	}
	checkGame(val);
}
void Game::displayWin(){
	QMessageBox msgBox; 
	msgBox.setWindowTitle("Minesweeper"); 
	msgBox.setText("Congratulations! You win ! " ) ; 
	QPushButton *resetButton = msgBox.addButton("Reset Game" , QMessageBox::ActionRole); 
	QPushButton *quitButton = msgBox.addButton("Quit Game" , QMessageBox::ActionRole);
	msgBox.exec();
	if (msgBox.clickedButton() == resetButton){
		resetGame();
	}else if (msgBox.clickedButton() == quitButton){
		QApplication::quit();
	}
}
void Game::openPopUp(){
	QMessageBox messageBox; 
	messageBox.setWindowTitle("Game Over"); 
	messageBox.setText("You Lost! Your final score is :   \nWhat would you like to do?" );
	QPushButton *resetButton = messageBox.addButton("Reset Game", QMessageBox::ActionRole);
	QPushButton *quitButton = messageBox.addButton("Quit Game" , QMessageBox::ActionRole);
	messageBox.exec();
	if (messageBox.clickedButton() == resetButton){
		resetGame();
	}else if (messageBox.clickedButton() == quitButton) {
		QApplication::quit();
	}	
	
}
void Game::checkGame(int val){
	if (val != -1 ) return ; 
	statusLabel->setText("Game Over");
	openPopUp(); 
}
void Game::placeBombs(){
	for (int i = 0 ; i < bombs; i ++ ) {
		int bombX , bombY; 
		do{
			bombX = rand() % 8; 
			bombY = rand() % 8 ; 

		}while(std::find(bomb.begin(),bomb.end(),std::make_pair(bombX,bombY)) != bomb.end());	
		
		bomb.push_back(std::make_pair(bombX,bombY));
		grid[bombX][bombY] = -1; 
	}	
}
void Game::setTiles(){
	const std::vector<pair<int,int>> dir=  {
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
		for (int j = 0 ; j < 8 ; j ++ ) {
			if (grid[i][j] == -1 ) continue ;
			int count = 0 ; 
			for (auto& [row,col] : dir ){
				int newI = i + row ; 
				int newJ = j + col ; 
				if (newI >= 0  && newI < 8 && newJ >= 0 && newJ < 8){
					if (grid[newI][newJ] == -1 ) count ++ ; 
				}
			}
			grid[i][j] = count;
		}
	}	
}
void Game::resetGame(){
	for (int i = 0 ; i < 8; i ++ ) {
		for (int j = 0 ; j < 8 ; j ++) {
			buttons[i][j]->setText(""); 	
			grid[i][j] = 0 ;
		}
	}	
	placeBombs();
	setTiles();
	flag = 10 ;
	bombsInPlay = 10 ;
	statusLabel->setText("Flags: " + QString::number(flag));
}
