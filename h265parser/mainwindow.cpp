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

    ui->infoText->setVisible(false);

    ui->pathLine->setText("E:/work/media/Earth_TR2_1080.265");

    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(parseFile()));

    mListMode = new QStringListModel(this);

    ui->listView->setModel(mListMode);


//    mListMode->setColumnCount(3);

//    QStringList heads;
//    heads += "Name";
//    heads += "Type";


//    mListMode->setHorizontalHeaderLabels(heads);
//    mListMode->setHorizontalHeaderItem(0, new QStandardItem("Name"));

//    QList<QStandardItem*> cols;

//    cols.append(new QStandardItem("Name"));
//    cols.append(new QStandardItem("Type"));
//    cols.append(new QStandardItem("Length"));

//    mListMode->appendColumn(cols);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parseFile()
{
    H265Parser *parser = new H265Parser(ui->pathLine->text().toLatin1().data());
    QList<H265NAL_t> nals = parser->getH265Nals();



//    QString info;
    QStringList slist;
    for(int i = 0; i < nals.size(); i++){
        QString str;

        str.sprintf("[%s] nal_type=%d  %d\n", getNaltypeDesc(nals[i].nal_type), nals[i].nal_type, nals[i].size);

//        info += str;

//        mListMode->appendRow(new QStandardItem(str));

        slist += str;
    }

    mListMode->setStringList(slist);


//    ui->infoText->setText(info);




    delete parser;
}
