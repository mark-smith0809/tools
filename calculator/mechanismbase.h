#ifndef MECHANISMBASE_H
#define MECHANISMBASE_H
#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QObject>

#include "mechanismConstant.h"
#include "KeyBoardStyle.h"

/*
 * 进制控制的基类
 */

class MechanismBase
{
public:
    static const std::vector<QString> mechanismTextStr;
    static const std::vector<QString> mechanismNameStr;

    MechanismBase() = default;

    // 设置左边竖线颜色以表示进制是否被使用
    void SetEnable(bool isEnable);
    // 生成进制对应的行
    QLayout* GenerateLayout(const Mechanism &type);
    // 修改值
    void ShowValue(const int& value);
    Mechanism type{0};
    QFrame *vline{nullptr};
    QPushButton *button{nullptr};

private:
    void ShowHexValue(const int& value);
    void ShowDecValue(const int& value);
    void ShowOctValue(const int& value);
    void ShowBinValue(const int& value);
};

#endif // MECHANISMBASE_H
