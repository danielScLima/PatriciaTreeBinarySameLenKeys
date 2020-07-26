#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    patriciaTreeBinarySameLenKeys =
            new PatriciaTreeBinarySameLenKeys(ui->spinBox->value());

    reloadDraw();
}

void MainWindow::reloadDraw()
{
    updateDotFile();
    updateImage();
    renderImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDotFile()
{
    std::ofstream myFile;
    QDir::setCurrent(QCoreApplication::applicationFilePath());
    myFile.open
    (
        "file.dot"
    );

    std::string textToFile = patriciaTreeBinarySameLenKeys->getGraphvizDraw();

    myFile << textToFile;
    myFile.close();
}

void MainWindow::updateImage()
{
    std::string message =
                "dot -Tpng file.dot > file.png";
    QDir::setCurrent(QCoreApplication::applicationFilePath());
    system(message.c_str());
}

void MainWindow::renderImage()
{
    QDir::setCurrent(QCoreApplication::applicationFilePath());
    QPixmap image("file.png");
    ui->labelOfImage->setPixmap(image);
    ui->labelOfImage->show();
}

void MainWindow::on_pushButtonOfInsert_clicked()
{
    QString toInsert = ui->lineEditOfInsert->text();

    bool ret = patriciaTreeBinarySameLenKeys->insert(toInsert.toStdString());

    QMessageBox msgBox;
    if (ret)
    {
        msgBox.setText("The word was inserted");
        reloadDraw();
    }
    else
    {
        msgBox.setText("Insert a binary word with the correct length");
    }
    msgBox.exec();
}

void MainWindow::on_pushButtonOfSearch_clicked()
{
    QString toInsert = ui->lineEditOfSearch->text();
    NodeOfPatriciaTreeBinarySameLenKeys* node =
            patriciaTreeBinarySameLenKeys->search(toInsert.toStdString());

    QMessageBox msgBox;
    if (node != nullptr)
        msgBox.setText("This word exists in the tree");
    else
        msgBox.setText("This word dos not exist in the tree");
    msgBox.exec();
}

void MainWindow::on_pushButtonOfRemove_clicked()
{
    QString toIntoRemovesert = ui->lineEditOfRemove->text();
    NodeOfPatriciaTreeBinarySameLenKeys* node =
            patriciaTreeBinarySameLenKeys->remove(toIntoRemovesert.toStdString());

    QMessageBox msgBox;
    if (node != nullptr)
    {
        msgBox.setText("The word was removed");
        reloadDraw();
        delete node;
    }
    else
        msgBox.setText("This word dos not exist in the tree");
    msgBox.exec();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    patriciaTreeBinarySameLenKeys =
            new PatriciaTreeBinarySameLenKeys(arg1);

    reloadDraw();
}
