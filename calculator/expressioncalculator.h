// ExpressionCalculator.h
#ifndef EXPRESSIONCALCULATOR_H
#define EXPRESSIONCALCULATOR_H

#include <QString>
#include <QStack>

class ExpressionCalculator
{
public:
    ExpressionCalculator();

    // 主计算函数
    static int calculate(const QString& expression);

private:
    // 中缀转后缀
    static QString infixToPostfix(const QString& expr);

    // 计算后缀表达式
    static int evaluatePostfix(const QString& postfix);

    // 判断是否为运算符
    static bool isOperator(const QChar& c);

    // 获取优先级
    static int priority(const QChar& op);

    // 执行运算
    static int applyOperator(int a, int b, const QChar& op);
};

#endif