#include <qapplication.h>
#include "ChessWindow.hpp"

int main(int argc, char* argv[]){
	QApplication echecs(argc, argv);

	ChessWindow chess_board;
	chess_board.setWindowTitle("Projet Echecs");
	chess_board.show();

	return echecs.exec();
}