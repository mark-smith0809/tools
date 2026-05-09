#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QPalette>
#include <QLabel>
#include <QRegularExpression>

#include "mechanismConstant.h"
#include "mechanismbase.h"
#include "InputStatus.h"

class Calculator : public QMainWindow
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);

    static std::vector<QString> getMechanismTextStr();

signals:

public slots:
    void ButtonClicked(int index);

private:
    QLayout* GenerateTopLayout();
    QLayout* GenerateMiddleLayout();
    QLayout* GenerateBottomLayout();
    QLayout* CreateMechanismLine(const QString &name, const QString &text);
    // 改变进制显示
    void SetMechanism(const Mechanism &mechanism);
    // 初始化键盘布局
    void InitKeyBoardStyle();
    // 改变不同进制对应按键布局
    void SetKeyBoardArea(const Mechanism &mechanism);
    // 十进制键盘布局
    void SetDecKeyBoard();
    // 显示值，更新所有进制的状态栏
    void ShowValue();
    // 依据当前进制，将string转化为int
    int ConvertStringToInt(const QString &type);
    QString ConvertIntToString(const int& value);

    Mechanism mechanismType {Mechanism::DEC};

    static const std::vector<std::vector<QString>> buttonNameOfCoder;

    QLabel* expressionLabel{};
    QLabel* resultLabel{};

    std::vector<MechanismBase*> mechanismVec{}; // 进制状态栏
    std::vector<QPushButton*> buttons{}; // 按钮

    InputStatus inputStatus;
};

#endif // CALCULATOR_H
