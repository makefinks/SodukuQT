#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVector>
#include "finalscore.h"
#define N 9

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameDialog(const QVector<QVector<QString>>& stringArray, QWidget *parent = nullptr);
    ~GameDialog();
    void setNumberAt(int row, int column, const QString& number);
    int getNumberAt(int row, int column);
    void initColors();
    void removeDigitsFromGui(int grid[N][N], int n);
    void removeDigits(int grid[N][N], int n);
    void disableAll(QLineEdit *editedLineEdit);
    void enableAll();
    void connectEditListener();
    void updateScore(int number);
    void updateAllowed();
    void checkFinished();

private slots:
    void on_lineEdit_5_textEdited(const QString &arg1);
    void on_checkButton_clicked();
    void on_pushButton_clicked();
    void openFinalScoreDialog();

private:
    int currentRound = 0;
    int currentTurnIndex = 0;
    std::vector<int> allowed = {1,2,3,4,5,6,7,8,9};
    Ui::GameDialog *ui;
    int lastModified[1][2] = {};
    int grid[N][N] = {0};
    QVector<QVector<QString>> playerArray;
    finalscore * finalScoreDialog;
};

#endif // GAMEDIALOG_H
