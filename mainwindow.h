#pragma once

#include "calculator.h"
#include "enums.h"

#include <QMainWindow>
#include <QDebug>

using namespace std::literals;
using Number = double;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    //устанавливает вводимое число или результат вычисления в ui->l_result
    void SetInputText(const std::string& text);

    //устанавливает текст ошибки
    void SetErrorText(const std::string& text);

    // устанавливает текст формулы, отображаемой над вводом числа в ui->l_formula.
    void SetFormulaText(const std::string& text);

    // устанавливает индикатор памяти ui->l_memory.
    void SetMemText(const std::string& text);

    // устанавливает текст экстра-кнопки. Если передано nullopt, то нужно скрыть экстра-кнопку.
    void SetExtraKey(const std::optional<std::string>& key);

    //колбэк-функцию нужно вызывать при нажатии кнопки с цифрами от 0 до 9.
    void SetDigitKeyCallback(std::function<void(int key)> cb);

    //колбэк-функцию нужно вызывать при нажатии кнопки операции
    //(сложение, вычитание, умножение, деление, возведение в степень).
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);

    //колбэк-функцию нужно вызывать при нажатии других кнопок
    // Они перечислены в типе ControlKey в enums.h.
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);

    //колбэк-функцию нужно вызывать при изменении типа чисел.
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_zero_clicked();

    void on_pb_dellete_clicked();

    void on_pb_one_clicked();

    void on_pb_two_clicked();

    void on_pb_three_clicked();

    void on_pb_four_clicked();

    void on_pb_five_clicked();

    void on_pb_six_clicked();

    void on_pb_seven_clicked();

    void on_pb_eight_clicked();

    void on_pb_nine_clicked();

    void on_pb_null_clicked();

    void on_pb_plusminus_clicked();

    void on_pb_MC_clicked();

    void on_pb_MR_clicked();

    void on_pb_MS_clicked();

    void on_pb_res_clicked();

    void on_pb_add_clicked();

    void on_pb_sub_clicked();

    void on_pb_mult_clicked();

    void on_pb_div_clicked();

    void on_pb_degr_clicked();

    void on_cmb_controller_currentIndexChanged(int index);

    void on_tb_extra_clicked();

private:
    Ui::MainWindow* ui;
    Operation current_operation_;
    QString input_number_ = "";
    Calculator<double> calculator_;
    Number active_number_ = 0;

    std::function<void(Operation key)> operation_cb_;
    std::function<void(int key)> digit_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void(ControllerType controller)> controller_cb_;
};
