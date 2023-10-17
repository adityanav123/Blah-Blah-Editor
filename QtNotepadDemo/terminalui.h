#ifndef TERMINALUI_H
#define TERMINALUI_H

#include <QDialog>

namespace Ui {
class TerminalUI;
}

class TerminalUI : public QDialog
{
    Q_OBJECT

public:
    explicit TerminalUI(QWidget *parent = nullptr);
    ~TerminalUI();
    void executeAndShowOutput(QString filepath, QVector<QString> fileInfo);

private slots:
//    void on_pushButton_clicked();

private:
    Ui::TerminalUI *ui;
    QVector<QString> executedCommands;
    QVector<QString> executedOutputs;
    QString errorFile = "Erros_.txt";

};

#endif // TERMINALUI_H
