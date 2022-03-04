#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>

QSqlQuery *query;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Flag = false;
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customContextMenuReq(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    cdlg = new ConnectionDialog();
    cdlg->show();
}


void MainWindow::on_pushButton_clicked()
{
    qmodel = new QSqlQueryModel();
    qmodel->setQuery("SELECT * FROM Production");
    ui->tableView->setModel(qmodel);

    Flag = true;
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
}


void MainWindow::on_pushButton_2_clicked()
{
    adlg = new AddDialog();
    adlg->show();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    query = new QSqlQuery();
    int tempID;
    tempID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
    ui->lineEdit->setText(QString::number(tempID));

    query->prepare("SELECT prodName, prodCost FROM Production WHERE prodID = :ID");
    query->bindValue(":ID", ui->lineEdit->text());

   if (query->exec())
   {
       query->next();
       ui->lineEdit_2->setText(query->value(0).toString());
       ui->lineEdit_3->setText(query->value(1).toString());
   }

}

void MainWindow::on_pushButton_4_clicked()
{
    query->exec("DELETE FROM Production WHERE prodID =" + ui->lineEdit->text());
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");

    MainWindow::on_pushButton_clicked();
}


void MainWindow::on_pushButton_3_clicked()
{
    query->prepare("UPDATE Production SET prodName = :Name, prodCost = :cost WHERE prodID = :ID");

    query->bindValue(":ID", ui->lineEdit->text());
    query->bindValue(":Name", ui->lineEdit_2->text());
    query->bindValue(":cost", ui->lineEdit_3->text());

    if (query->exec())
    {
        MainWindow::on_pushButton_clicked();
    }
}

void MainWindow::customContextMenuReq(QPoint pos)
{
    if (Flag)
    {
        QModelIndex index = ui->tableView->indexAt(pos);
        GlobID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();

        //menu
        QMenu *menu = new QMenu(this);
        QAction *ModRec = new QAction("Изменить...", this);
        QAction *DelRec = new QAction("Удалить", this);

        connect(ModRec, SIGNAL(triggered()), this, SLOT(ModRecAction()));
        connect(DelRec, SIGNAL(triggered()), this, SLOT(DelRecAction()));

        menu->addAction(ModRec);
        menu->addAction(DelRec);

        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::DelRecAction()
{
    query->prepare("DELETE FROM Production WHERE prodID = :ID");
    query->bindValue(":ID", GlobID);
    query->exec();

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");

    MainWindow::on_pushButton_clicked();
}

void MainWindow::ModRecAction()
{
    mdlg = new ModifyDialog();
    connect(this, SIGNAL(sendID(int)), mdlg, SLOT(sendingID(int)));
    emit sendID(GlobID);
    mdlg->show();
    disconnect(this, SIGNAL(SendID(int)), mdlg, SLOT(sendingID(int)));
}

void MainWindow::on_action_2_triggered()
{
    pdlg = new PrintDialog();
    pdlg->show();
}


void MainWindow::on_toolButton_clicked()
{
    Image = QFileDialog::getOpenFileName(0,"Выберите файл",".\\","*jpg");
    ui->label_4->setPixmap(Image);
}

