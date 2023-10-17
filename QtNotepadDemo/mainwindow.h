#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "terminalui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionAbout_Notepad_triggered();

    void on_actionExit_triggered();

//    void on_actionCompile_triggered();

    void on_actionFont_triggered();

    void on_actionColor_Select_triggered();

    void on_actionBackground_Color_triggered();

    void on_actionBg_Color_WIndow_triggered();

    void on_actionPrint_triggered();

private:
    Ui::MainWindow *ui;
    QString filepath; // save the file path
    TerminalUI *terminal; // second window for terminal
};
#endif // MAINWINDOW_H