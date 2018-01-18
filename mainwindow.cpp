#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
//TODO save as
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    this->isSaved = false;
    this->isUpdated = false;
    setWindowTitle("New File - Cutepad");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    workFileName = "";
    ui->textEdit->setPlainText("");
    setWindowTitle("New File - Cutepad");
    isSaved = false;
    isUpdated = false;
}

void MainWindow::on_actionOpen_triggered()
{
    this->workFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr ("Text Files(*.*)"));
    if (workFileName.isEmpty()) return;
    else
    {
        workingFile = new QFile(workFileName);
        if(!workingFile->open(QIODevice::ReadOnly| QIODevice::Text)){
            qDebug() << "Could not open file";
            return;
        } else {
            QTextStream in (workingFile);
            ui->textEdit->setText(in.readAll());
            workingFile->close();
            isSaved = true;
            setWindowTitle(workFileName);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(!isSaved && isUpdated){
        this->workFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "Text.txt", tr("Text Files(*.*)"));
        if(workFileName.isEmpty()) return;
        else{
            workingFile = new QFile(workFileName);
            if(!workingFile->open(QIODevice::Text| QIODevice::Truncate|QIODevice::WriteOnly)){
                qDebug() << "Could not save file";
                return;
            }
            else{
            QTextStream out(workingFile);
            out << ui->textEdit->toPlainText();
            workingFile->close();
            isSaved = true;
            isUpdated = false;
            setWindowTitle(workFileName + " - Cutepad");
            }
        }
    }
    else if(isSaved && isUpdated){
        if(!workingFile->open(QIODevice::Text| QIODevice::Truncate|QIODevice::WriteOnly)){
            qDebug () << "Could not save file";
            return;
        } else {

        QTextStream out(workingFile);
        out << ui->textEdit->toPlainText();
        workingFile->close();
        isUpdated = false;
        }
    }
}
void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save As"),
    "/home/ston1x/untitled.txt",
    tr("Text File(*.*)"));

    if(fileName.isEmpty()) return;
    else {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly| QIODevice::Text| QIODevice::Truncate))	{
            qDebug() << "Could not save file";
            return;
        } else {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.flush();
            file.close();
            setWindowTitle(fileName + " - Cutepad");
        }
    }

}
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_textEdit_textChanged()
{
    this->isUpdated = true;
}

void MainWindow::on_actionAbout_triggered()
{
    About about;
    about.setModal(true);
    about.exec();

}
