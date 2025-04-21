// Реальзуйте класс главного окна.
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pb_zero_clicked()
{
    if(digit_cb_) {
        digit_cb_(0);
    }
}


void MainWindow::on_pb_dellete_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::BACKSPACE);
    }
}


void MainWindow::on_pb_one_clicked()
{
    if(digit_cb_) {
        digit_cb_(1);
    }
}


void MainWindow::on_pb_two_clicked()
{
    if(digit_cb_) {
        digit_cb_(2);
    }
}


void MainWindow::on_pb_three_clicked()
{
    if(digit_cb_) {
        digit_cb_(3);
    }
}


void MainWindow::on_pb_four_clicked()
{
    if(digit_cb_) {
        digit_cb_(4);
    }
}


void MainWindow::on_pb_five_clicked()
{
    if(digit_cb_) {
        digit_cb_(5);
    }
}


void MainWindow::on_pb_six_clicked()
{
    if(digit_cb_) {
        digit_cb_(6);
    }
}


void MainWindow::on_pb_seven_clicked()
{
    if(digit_cb_) {
        digit_cb_(7);
    }
}


void MainWindow::on_pb_eight_clicked()
{
    if(digit_cb_) {
        digit_cb_(8);
    }
}


void MainWindow::on_pb_nine_clicked()
{
    if(digit_cb_) {
        digit_cb_(9);
    }
}


void MainWindow::on_pb_null_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::CLEAR);
    }
}


void MainWindow::on_pb_plusminus_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::PLUS_MINUS);
    }
}


void MainWindow::on_pb_MC_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::MEM_CLEAR);
    }
}


void MainWindow::on_pb_MR_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::MEM_LOAD);
    }
}


void MainWindow::on_pb_MS_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::MEM_SAVE);
    }
}


void MainWindow::on_pb_res_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::EQUALS);
    }
}


void MainWindow::SetInputText(const std::string &text)
{
    input_number_ = QString::fromStdString(text);
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(input_number_);
}


void MainWindow::SetErrorText(const std::string &text)
{
    QString error = QString::fromStdString(text);
    ui->l_result->setStyleSheet("color: red");
    ui->l_result->setText(error);
}


void MainWindow::SetFormulaText(const std::string &text)
{
    QString formula  = QString::fromStdString(text);
    ui->l_formula->setText(formula);
}


void MainWindow::SetMemText(const std::string &text)
{
    QString mem_text = QString::fromStdString(text);
    ui->l_memory->setText(mem_text);
}


void MainWindow::SetExtraKey(const std::optional<std::string> &key)
{
    if (key == std::nullopt) {
        ui->tb_extra->hide();
    }
    else {
        ui->tb_extra->show();
        ui->tb_extra->setText(QString::fromStdString(*key));
    }
}


void MainWindow::SetDigitKeyCallback(std::function<void (int)> cb)
{
    digit_cb_ = cb;
}


void MainWindow::SetProcessOperationKeyCallback(std::function<void (Operation)> cb)
{
    operation_cb_ = cb;
}


void MainWindow::SetProcessControlKeyCallback(std::function<void (ControlKey)> cb)
{
    control_cb_ = cb;
}


void MainWindow::SetControllerCallback(std::function<void (ControllerType)> cb)
{
    controller_cb_ = cb;
}


void MainWindow::on_pb_add_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::ADDITION);
    }
}


void MainWindow::on_pb_sub_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::SUBTRACTION);
    }
}


void MainWindow::on_pb_mult_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::MULTIPLICATION);
    }
}


void MainWindow::on_pb_div_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::DIVISION);
    }
}


void MainWindow::on_pb_degr_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::POWER);
    }
}

void MainWindow::on_cmb_controller_currentIndexChanged(int index)
{
    switch(index) {
    case(0):
        if (controller_cb_) {
            controller_cb_(ControllerType::DOUBLE);
        }
        break;
    case(1):
        if (controller_cb_) {
            controller_cb_(ControllerType::FLOAT);
        }
        break;
    case(2):
        if (controller_cb_) {
            controller_cb_(ControllerType::UINT8_T);
        }
        break;
    case(3):
        if (controller_cb_) {
            controller_cb_(ControllerType::INT);
        }
        break;
    case(4):
        if (controller_cb_) {
            controller_cb_(ControllerType::INT64_T);
        }
        break;
    case(5):
        if (controller_cb_) {
            controller_cb_(ControllerType::SIZE_T);
        }
        break;
    case(6):
        if (controller_cb_) {
            controller_cb_(ControllerType::RATIONAL);
        }
        break;
    }

}


void MainWindow::on_tb_extra_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::EXTRA_KEY);
    }
}

