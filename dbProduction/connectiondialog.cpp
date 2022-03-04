#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(".\\SQLEXPRESS");
    ui->lineEdit_2->setText("Production");
    ui->lineEdit_3->setText("Likhachev");
    ui->lineEdit_4->setText("parol");

}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_pushButton_2_clicked()
{
    db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("DRIVER={SQL Server};SERVER="+ui->lineEdit->text()+";DATABASE="+
                       ui->lineEdit_2->text() + ";");
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit_4->text());

    msg = new QMessageBox();

    if (db.open())
    {
        //msg->setText("Соединение установлено");
        msg->close();
    }
    else
    {
        msg->setText("Соединение не установлено. Причина: " + db.lastError().text());
        msg->show();
    }


}

