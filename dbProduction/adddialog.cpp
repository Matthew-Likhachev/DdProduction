#include "adddialog.h"
#include "ui_adddialog.h"
#include <QSqlQuery>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_pushButton_2_clicked()
{
    close();
}


void AddDialog::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();

    query->prepare("INSERT INTO Production(prodName, prodCost) VALUES (:Name, :cost)");
    query->bindValue(":Name", ui->lineEdit->text());
    query->bindValue(":cost", ui->lineEdit_2->text());
    if (query->exec())
    {
        close();
    }

}

