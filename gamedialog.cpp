#include "gamedialog.h"
#include "ui_gamedialog.h"
#include <QGridLayout>
#include <QLineEdit>
#include<QDebug>


GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{
    ui->setupUi(this);
    initColors();
    setNumberAt(4, 3, "2");

   // for(int i = 0; i<8; i++){
       // qInfo() << ui->gridLayout->itemAt(i);
    //}

}

GameDialog::~GameDialog()
{
    delete ui;
}

void GameDialog::initColors(){


    int coloredGrids[] = {1, 5, 7, 6, 0};
    for(int i = 0; i<5; i++){
        QLayoutItem *layoutItem = ui->gridLayout->itemAt(coloredGrids[i]);
        QGridLayout *subGrid = qobject_cast<QGridLayout*>(layoutItem->layout());

        for(int x=0; x<9; x++){
            QLayoutItem *subLayoutItem = subGrid->itemAt(x);
            QLineEdit *lineEdit = qobject_cast<QLineEdit*>(subLayoutItem->widget());
            lineEdit->setStyleSheet("QLineEdit { background-color : #d4e1ff; color : black; }");
        }
    }
}


void GameDialog::setNumberAt(int row, int column, const QString& number){

    int subGridRow = row / 3;
    int subGridCol = column / 3;


        int innerRow = row % 3;
        int innerCol = column % 3;

        qInfo() << "row:" <<subGridRow;
        qInfo() << "Col:" <<subGridCol;

        // Get the sub-grid
        QLayoutItem *layoutItem = ui->gridLayout->itemAtPosition(subGridRow, subGridCol);
        qInfo() << ui->gridLayout->count();
        if(layoutItem) {
            qInfo() << "MainGrid:" << layoutItem;
            QGridLayout *subGrid = qobject_cast<QGridLayout*>(layoutItem->layout());
            qInfo() << "SubGrid:" << subGrid;
            if(subGrid) {
                // Get the QLineEdit from the sub-grid
                QLayoutItem *subLayoutItem = subGrid->itemAtPosition(innerRow, innerCol);
                if(subLayoutItem) {
                    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(subLayoutItem->widget());
                    if(lineEdit) {
                        // Set the number
                        lineEdit->setText(number);
                    }
                }
            }
        }
    }



