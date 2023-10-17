#include "terminalui.h"
#include "ui_terminalui.h"
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

TerminalUI::TerminalUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TerminalUI)
{
    ui->setupUi(this);
    this->setWindowTitle("Blah Blah Terminal");
}

TerminalUI::~TerminalUI()
{
    delete ui;
}

//void TerminalUI::on_pushButton_clicked()
//{
//    /* send data to terminal and get back output */

//    // fetch command
////    QString command = ui->terminalCommandLineEdit->text();
//    QString command = "g++ --version";

//    // store in prev commands
//    executedCommands.append(command);

//    // send to terminal
//    ui->terminalOutput->clear(); // clear terminal output

//    // init process to run the command
//    QProcess process;
//    // Merge standard output and error channels
//    process.setProcessChannelMode(QProcess::MergedChannels);
//    // Execute the command start
//    process.start(command);


//    // wait for execution
//    process.waitForFinished();

//    if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0)
//    {
//        QMessageBox::information(this, "Permission Check", "Permissions are there.");
//    }
//    else
//    {
//        QMessageBox::warning(this, "Permission Check", "Permissions are not there.");
//    }



////    // wait for execution
////    if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0)
////    {

////        QString output = process.readAll();
////        QMessageBox::information(this, "terminal says.", "Command Started Executing : \t" + command + "\nresult : " + output);


////        QTextCursor cursor(ui->terminalOutput->document());
////        cursor.movePosition(QTextCursor::End);
////        cursor.insertText(output);
////    }
////    else
////    {
////        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
////        // error
////        QString errorString = process.errorString();
////        ui->terminalOutput->appendPlainText("Command Failed to execute!, Try again. Error : " + errorString + "\nenv : ");
////        foreach (QString var, env.toStringList()) {
////            qDebug() << var << "\n";
////        }
////    }


//    // print output of terminal
////    process.close();
//}

void TerminalUI::executeAndShowOutput(QString filepath, QVector<QString> fileInfo)
{
    // parsing file information
    QString fileType = fileInfo[0];
    //    QString fileDirPath = fileInfo[1]; // for future use.

    QString fileToExecute = (fileType == "cpp") ? "compile_cpp_file.sh" : (fileType == "py") ? "execute_python_file.sh" : "";

    if (fileToExecute == "")
        return;

    QString command = "sudo ./" + fileToExecute + " " + filepath + " 2> " + errorFile;

    executedCommands.append(command); // store history [just in case]

    // clearing terminal output
    ui->terminalOutput->clear();

    ui->terminalOutput->appendPlainText("Command to be executed : " + command);


    // start a process for execution
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);

    // start execution
//    process.start(command);
//    process.start("/usr/bin echo 2");
    process.start("whoami");

    // Get the current user's username.
    QString username = QString::fromLocal8Bit(getenv("USER"));

    // waiting for execution
    process.waitForFinished();

    // output
//    if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0)
//    {
//        QMessageBox::information(this, "Permission Check", "Permissions are there.");
//    }
//    else
//    {
//        QMessageBox::warning(this, "Permission Check", "Permissions are not there.");
//        QString errorOutput = process.readAll();
//        ui->terminalOutput->appendPlainText("Error Output: " + errorOutput);
//        qDebug() << process.exitCode() << "\n" << process.exitStatus();
//    }


    // Get the output of the process.
    QString output = process.readAll();

    qDebug() << "username "  << username << "\n";

    // Check if the output of the process matches the current user's username.
    if (output == username + "\n") {
        qDebug() << "The Qt application is running as the current user.";
    } else {
        qDebug() << "The Qt application is running as the user " << output;
    }
}

