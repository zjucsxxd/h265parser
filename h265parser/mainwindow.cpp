#include <QDebug>
#include <QList>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "h265parser.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pathLine->setText("E:/media/Earth_TR2_1080.265");

    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(parseFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parseFile()
{
    H265Parser *parser = new H265Parser(ui->pathLine->text().toLatin1().data());
    QList<H265NAL_t> nals = parser->getH265Nals();

    QString info;
    for(int i = 0; i < nals.size(); i++){
        QString str;

        str.sprintf("nal_type=%d  %d\n", nals[i].nal_type, nals[i].size);

        info += str;
    }

    ui->infoText->setText(info);


    delete parser;
}
