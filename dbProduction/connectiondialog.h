#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ConnectionDialog *ui;
    QSqlDatabase db;
    QMessageBox *msg;
};

#endif // CONNECTIONDIALOG_H
