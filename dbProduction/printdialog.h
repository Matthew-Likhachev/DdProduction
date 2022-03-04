#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QSqlQuery>

namespace Ui {
class PrintDialog;
}

class PrintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrintDialog(QWidget *parent = nullptr);
    ~PrintDialog();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::PrintDialog *ui;
};

#endif // PRINTDIALOG_H
