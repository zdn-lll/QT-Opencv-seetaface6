#include "selectwin.h"
#include "ui_selectwin.h"

SelectWin::SelectWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectWin)
{
    ui->setupUi(this);
    model = new QSqlTableModel();
}

SelectWin::~SelectWin()
{
    delete ui;
    delete  model;
}

void SelectWin::on_selectBt_clicked()
{
    if(ui->empRb->isChecked())
    {
        model->setTable("employee");
    }
    if(ui->attRb->isChecked())
    {
        model->setTable("attendance");
    }
    model->select();
    ui->tableView->setModel(model);
}
