#include "gamedialog.h"
#include "ui_gamedialog.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QDebug>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>


#define N 9

bool isSafe(int grid[N][N], int row, int col, int num);
bool solveSudoku(int grid[N][N], int row, int col);
int countSolutions(int grid[N][N], int row, int col);
void removeDigits(int grid[N][N], int n);
bool isUnique(int grid[N][N]);

void disableAll();

GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{


    this->setFixedSize(500, 600);
    ui->setupUi(this);
    initColors();
    //setNumberAt(4, 3, "2");
    //qInfo() << getNumberAt(4,3);
    //qInfo() << getNumberAt(4,2);



    if(solveSudoku(grid, 0,0)){
        //removeDigitsFromGui(grid, 30);


    for (int i = 0; i < N; i++) {
             for (int j = 0; j < N; j++){
            // qInfo() << grid[i][j] << " ";
                 setNumberAt(i, j, QString::number(grid[i][j]));
        }
       // qInfo() << Qt::endl;
    }


    removeDigitsFromGui(grid, 80); // <---- Schwierigkeitsgrad
    connectEditListener();
    //disableAll();
    qInfo() << countSolutions(grid, 0,0);
}



   // for(int i = 0; i<8; i++){
       // qInfo() << ui->gridLayout->itemAt(i);
    //}

}

GameDialog::~GameDialog()
{
    delete ui;
}



void connectListeners(){

}

// Checks if a number can be placed at grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check the column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check the box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool solveSudoku(int grid[N][N], int row, int col){
    if(row == N - 1 && col == N)
        return true;
    if(col == N){
        row++;
        col = 0;
    }
    if(grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);
    for(int num = 1; num <= N; num++){
        if(isSafe(grid, row, col, num)){
            grid[row][col] = num;
            if(solveSudoku(grid, row, col + 1))
                return true;
        }
        grid[row][col] = 0;
    }
    return false;
}
int countSolutions(int grid[N][N], int row = 0, int col = 0) {
    // If the last cell in the grid has been processed, return 1
    if (row == N - 1 && col == N)
        return 1;

    if (col == N) {
        row++;
        col = 0;
    }

    if (grid[row][col] > 0)
        return countSolutions(grid, row, col + 1);

    int count = 0;

    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            count += countSolutions(grid, row, col + 1);
        }

        grid[row][col] = 0;
    }
    return count;
}

bool isUnique(int grid[N][N]) {
    return countSolutions(grid) == 1;
}


void GameDialog::removeDigits(int grid[N][N], int n){
    srand(time(0));
    for(int i = 0; i < n; i++){
        int cellId = rand()%81;
        int row = cellId/9, col = cellId%9;
        grid[row][col] = 0;
    }
}
void GameDialog::removeDigitsFromGui(int grid[N][N], int n) {
    srand(time(0));
    std::vector<int> positions(81);
    std::iota(positions.begin(), positions.end(), 0); // fill with numbers from 0 to 80
    std::shuffle(positions.begin(), positions.end(), std::mt19937{std::random_device{}()}); // shuffle the positions
    int count = 0;
    for (int position : positions) {
        int row = position / 9, col = position % 9;
        int temp = grid[row][col];
        grid[row][col] = 0;
        // if the Sudoku puzzle is still unique after removing the number, keep it removed
        if (isUnique(grid)) {
            setNumberAt(row, col, "");
            count++;
            if (count == n) {
                break;
            }
        } else {
            // else, add it back
            grid[row][col] = temp;
        }
    }
}


void GameDialog::initColors(){

    int coloredGrids[4][2] = {
        {0,1},
        {1,0},
        {1,2},
        {2,1}
    };
    for(int i = 0; i<4; i++){
        QLayoutItem *layoutItem = ui->gridLayout->itemAtPosition(coloredGrids[i][0], coloredGrids[i][1]);
        QGridLayout *subGrid = qobject_cast<QGridLayout*>(layoutItem->layout());

        if(subGrid){
            for(int x=0; x<9; x++){
                QLayoutItem *subLayoutItem = subGrid->itemAt(x);
                QLineEdit *lineEdit = qobject_cast<QLineEdit*>(subLayoutItem->widget());
                lineEdit->setStyleSheet("QLineEdit { background-color : #d4e1ff; color : black; }"
                                        "QLineEdit:disabled { background-color : #cccccc; color : #7d7d7d; }");
            }
        }
    }
}

void GameDialog::disableAll(QLineEdit *editedLineEdit){

    for(int i = 0; i < ui->gridLayout->count(); i++){
        QLayoutItem *layoutItem = ui->gridLayout->itemAt(i);
        QGridLayout *subGrid = qobject_cast<QGridLayout*>(layoutItem->layout());

        if(subGrid){
            for(int x=0; x<subGrid->count(); x++){
                QLayoutItem *subLayoutItem = subGrid->itemAt(x);
                QLineEdit *lineEdit = qobject_cast<QLineEdit*>(subLayoutItem->widget());
                if(lineEdit != editedLineEdit){ // check if it's not the edited line edit
                    lineEdit->setDisabled(true);
                }
            }
        }

    }

}

void GameDialog::enableAll(){

    for(int i = 0; i < ui->gridLayout->count(); i++){
        QLayoutItem *layoutItem = ui->gridLayout->itemAt(i);
        QGridLayout *subGrid = qobject_cast<QGridLayout*>(layoutItem->layout());

        if(subGrid){
            for(int x=0; x<subGrid->count(); x++){
                QLayoutItem *subLayoutItem = subGrid->itemAt(x);
                QLineEdit *lineEdit = qobject_cast<QLineEdit*>(subLayoutItem->widget());
                if(lineEdit){
                    lineEdit->setEnabled(true);
                }
            }
        }
    }
}



void GameDialog::connectEditListener(){

    for(int i = 0; i < ui->gridLayout->count(); i++){
        QLayoutItem *layoutItem = ui->gridLayout->itemAt(i);
        QGridLayout *subGrid = qobject_cast<QGridLayout*>(layoutItem->layout());

        if(subGrid){
            for(int x=0; x<subGrid->count(); x++){
                QLayoutItem *subLayoutItem = subGrid->itemAt(x);
                QLineEdit *lineEdit = qobject_cast<QLineEdit*>(subLayoutItem->widget());

                if(lineEdit){
                    connect(lineEdit, &QLineEdit::textEdited, this, [=](const QString &newText){
                        if(newText.isEmpty()){
                            enableAll();
                        }else{
                            disableAll(lineEdit);

                            int mainRow, mainCol, dummy;
                            ui->gridLayout->getItemPosition(i, &mainRow, &mainCol, &dummy, &dummy);

                            int subRow, subCol, dummy2;
                            subGrid->getItemPosition(x, &subRow, &subCol, &dummy2, &dummy2);

                            // Assuming that each sub-grid is 3x3
                            lastModified[0][0] = mainRow * 3 + subRow;
                            lastModified[0][1] = mainCol * 3 + subCol;
                        }
                    });
                }
            }
        }
    }
}




void GameDialog::setNumberAt(int row, int column, const QString& number){

    int subGridRow = row / 3;
    int subGridCol = column / 3;


        int innerRow = row % 3;
        int innerCol = column % 3;

        //qInfo() << "row:" <<subGridRow;
        //qInfo() << "Col:" <<subGridCol;

        // Get the sub-grid
        QLayoutItem *layoutItem = ui->gridLayout->itemAtPosition(subGridRow, subGridCol);
        //qInfo() << ui->gridLayout->count();
        if(layoutItem) {
            //qInfo() << "MainGrid:" << layoutItem;
            QGridLayout *subGrid = qobject_cast<QGridLayout*>(layoutItem->layout());
            //qInfo() << "SubGrid:" << subGrid;
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

int GameDialog::getNumberAt(int row, int column){
        int subGridRow = row / 3;
        int subGridCol = column / 3;


        int innerRow = row % 3;
        int innerCol = column % 3;

        //qInfo() << "row:" <<subGridRow;
        //qInfo() << "Col:" <<subGridCol;

        // Get the sub-grid
        QLayoutItem *layoutItem = ui->gridLayout->itemAtPosition(subGridRow, subGridCol);
       // qInfo() << ui->gridLayout->count();
        if(layoutItem) {
            //qInfo() << "MainGrid:" << layoutItem;
            QGridLayout *subGrid = qobject_cast<QGridLayout*>(layoutItem->layout());
            //qInfo() << "SubGrid:" << subGrid;
            if(subGrid) {
                // Get the QLineEdit from the sub-grid
                QLayoutItem *subLayoutItem = subGrid->itemAtPosition(innerRow, innerCol);
                if(subLayoutItem) {
                    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(subLayoutItem->widget());
                    if(lineEdit) {
                        // Set the number
                        return lineEdit->text().toInt() ? lineEdit->text().toInt() : -1;
                    }
                }
            }
        }
}




void GameDialog::on_lineEdit_5_textEdited(const QString &arg1)
{

}


void GameDialog::on_checkButton_clicked()
{
        int lastInput = getNumberAt(lastModified[0][0], lastModified[0][1]);
        int correct = grid[lastModified[0][0]][lastModified[0][1]];
        qInfo() << "lastInput:" << lastInput << "expected:" << correct;
        if(lastInput == correct){
            qInfo() << "Success";
            enableAll();
            ui->statusLabel->setText("richtig");
            lastModified[0][0] = -1;
        }else if(lastModified[0][0] == -1){
            ui->statusLabel->setText("Keine Eingabe");
        }
        else{
            ui->statusLabel->setText("falsch");
        }

}

