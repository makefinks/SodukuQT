#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#define N 9

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameDialog(QWidget *parent = nullptr);
    ~GameDialog();
    void setNumberAt(int row, int column, const QString& number);
    int getNumberAt(int row, int column);
    void initColors();
    void removeDigitsFromGui(int grid[N][N], int n);
    void removeDigits(int grid[N][N], int n);
    void disableAll(QLineEdit *editedLineEdit);
    void enableAll();
    void connectEditListener();

private slots:
    void on_lineEdit_5_textEdited(const QString &arg1);

    void on_checkButton_clicked();

private:
    Ui::GameDialog *ui;
    int lastModified[1][2] = {-1};
    int grid[N][N] = {0};
};

#endif // GAMEDIALOG_H
