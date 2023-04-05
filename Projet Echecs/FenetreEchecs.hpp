#include <qmainwindow>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qtwidgets>
#include <qlabel.h>


class FenetreEchecs : public QMainWindow {
    Q_OBJECT
public:
    FenetreEchecs() {
        QWidget* central_widget = new QWidget();
        setCentralWidget(central_widget);


        QGridLayout* grid_layout = new QGridLayout(central_widget);

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                QPushButton* button = new QPushButton();
                button->setFixedSize(50, 50);
                if ((row + col) % 2 == 0) {
                    button->setStyleSheet("background-color: white");
                }
                else {
                    button->setStyleSheet("background-color: gray");
                }
                grid_layout->addWidget(button, row, col);
            }
        }
        setFixedSize(400, 400);
    }
};