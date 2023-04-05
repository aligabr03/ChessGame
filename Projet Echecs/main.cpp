#include <qapplication.h>
#include "FenetreEchecs.hpp"

int main(int argc, char* argv[]){
	QApplication echecs(argc, argv);

	FenetreEchecs chess_board;
	chess_board.show();

	return echecs.exec();
}