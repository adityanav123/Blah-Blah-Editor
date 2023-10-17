#include "mainwindow.h"
#include <QColor>
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QFont>
#include <QFontDialog>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextStream>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);
    this->setWindowTitle("Blah Blah Editor");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    filepath = "Untitled*"; // reset the file path
    ui->textEdit->setText("");
    this->setWindowTitle(filepath + ": Blah Blah Editor");
}


void MainWindow::on_actionOpen_triggered()
{
    // file dialog
    QString openFilePath = QFileDialog::getOpenFileName(this, "Opening File");
    QFile file(openFilePath);
    filepath = openFilePath;

    // check if file is open
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        // file not open
        QMessageBox::warning(this, "Open File Error", "File Not Open");
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    ui->textEdit->setText(fileContent); // setting text to file

    file.close();
    this->setWindowTitle(filepath + ": Blah Blah Editor");
}


void MainWindow::on_actionSave_triggered()
{
    // file dialog not needed.
    QFile file(filepath);

    // check if file is open
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        // file not open
        QMessageBox::warning(this, "Save File Error", "No File opened, Use Save As to save a new File");
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText(); // store to editor

    file.flush();
    file.close();
    this->setWindowTitle(filepath + ": Blah Blah Editor");
}


void MainWindow::on_actionSave_As_triggered()
{
    QString saveFilePath = QFileDialog::getSaveFileName(this, "Saving File");
    QFile file(saveFilePath);
    filepath = saveFilePath;

    // check if file is open
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        // file not open
        QMessageBox::warning(this, "Save File Error", "File Not Open");
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText(); // store to editor

    file.flush();
    file.close();
    this->setWindowTitle(filepath + ": Blah Blah Editor");
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionAbout_Notepad_triggered()
{
    QString aboutMessage;
    aboutMessage += "Written in C++, Qt.\n";
    aboutMessage += "Author : Aditya Navphule\n";
    aboutMessage += "Github : adityanav123\n";
    aboutMessage += QChar(0x00AE);
    aboutMessage += "Blah Blah Notepad";
    QMessageBox::about(this, "About", aboutMessage);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

// try inlining it
QVector<QString> getFileInfo(QString _filepath)
{
    QString type = "";
    // find first . from the right
    int i = _filepath.size() - 1;
    while (i) {
        if (_filepath[i] == '.')
        {
            break;
        }
        type.push_front(_filepath[i]);
        --i;
    }

    // find path further
    QString fileDirectory = "";
    while(i--) {
        if (_filepath[i] == '/') break;
    }

    while(i--) {
        fileDirectory.push_front(_filepath[i]);
    }

    return {type, fileDirectory};
}

// IGNORE.
//void MainWindow::on_actionCompile_triggered()
//{
//    // Compile the CPP Code
//    QMessageBox::information(this, "Compile", "Compiling the C++ Code.");
//    terminal = new TerminalUI(this);

//    // execute code
//    qDebug() << filepath << "\n";

//    // if no file is open
//    if (filepath == "")
//        return;

//    terminal->show();

//    QVector<QString> fileInfo = getFileInfo(filepath);
//    QString fileType = fileInfo[0];

//    qDebug() << "File Type : " << fileType << "\n";

//    if (fileType.compare("cpp") == 0)
//    {
//        // execute the file compile_cpp_file.sh
//        QMessageBox::information(terminal, "Execution file type", "Its a C++ file");
//    }

//    else if (fileType.compare("py") == 0)
//    {
//        QMessageBox::information(terminal, "Execution file type", "Its a Python file");
//    }
//    else
//    {
//        // support for more languages
//        return;
//    }

//    terminal->executeAndShowOutput(filepath, fileInfo);

//}




void MainWindow::on_actionFont_triggered()
{
    bool ok;

    // create a font dialog
    QFont font = QFontDialog::getFont(&ok, this);

    if (ok)
    {
        // font selected. --> set the font
        ui->textEdit->setFont(font);
    }
    else
        return;
}


void MainWindow::on_actionColor_Select_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid())
        ui->textEdit->setTextColor(color); // will change the color of selected text
}


void MainWindow::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid())
        ui->textEdit->setTextBackgroundColor(color);
}


void MainWindow::on_actionBg_Color_WIndow_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    qDebug() << "Color Selected : " << color << "\n";

    if (color.isValid())
    {
        QPalette palette = ui->textEdit->viewport()->palette();
        palette.setColor(QPalette::Base, color);
        ui->textEdit->viewport()->setPalette(palette);
    }
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("HP LaserJet MP1050"); // set you printer name
    QPrintDialog dialog(&printer, this);

    if (dialog.exec() == QDialog::Rejected)
        return;

    ui->textEdit->print(&printer);
}
