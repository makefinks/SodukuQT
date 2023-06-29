#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "gamedialog.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_addPlayer_Button_clicked();

    void on_startGame_Button_clicked();

private:
    Ui::MenuWindow *ui;
    GameDialog *threexthreedialog;
};
#endif // MENUWINDOW_H
