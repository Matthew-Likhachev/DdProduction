#include "modifydialog.h"
#include "ui_modifydialog.h"
#include <QSqlQuery>

int GlobID;

ModifyDialog::ModifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyDialog)
{
    ui->setupUi(this);
}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}

void ModifyDialog::on_pushButton_2_clicked()
{
    close();
}


void ModifyDialog::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE Production SET prodName = :Name, prodCost = :cost WHERE prodID = :ID");

    query->bindValue(":ID", GlobID);
    query->bindValue(":Name", ui->lineEdit->text());
    query->bindValue(":cost", ui->lineEdit_2->text());

    if (query->exec())
    {
        close();
    }
}


void ModifyDialog::sendingID(int aa)
{
    GlobID = aa;
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT prodName, prodCost FROM Production WHERE prodID = :ID");
    query->bindValue(":ID", GlobID);

    if (query->exec())
    {
        query->next();
        ui->lineEdit->setText(query->value(0).toString());
        ui->lineEdit_2->setText(query->value(1).toString());
    }
}
