// ExpressionCalculator.cpp
#include "ExpressionCalculator.h"
#include <QDebug>
#include <stdexcept>

ExpressionCalculator::ExpressionCalculator()
{
}

int ExpressionCalculator::calculate(const QString& expression)
{
    if (expression.isEmpty()) {
        throw std::runtime_error("表达式为空");
    }

    QString postfix = infixToPostfix(expression);
    return evaluatePostfix(postfix);
}

QString ExpressionCalculator::infixToPostfix(const QString& expr)
{
    QString postfix;
    QStack<QChar> ops;

    for (int i = 0; i < expr.length(); ++i) {
        QChar c = expr[i];

        // 跳过空格
        if (c.isSpace()) continue;

        // 数字：直接输出
        if (c.isDigit()) {
            while (i < expr.length() && expr[i].isDigit()) {
                postfix += expr[i];
                ++i;
            }
            postfix += ' ';  // 分隔符
            --i;
        }
        // 左括号：压栈
        else if (c == '(') {
            ops.push(c);
        }
        // 右括号：弹出直到左括号
        else if (c == ')') {
            while (!ops.isEmpty() && ops.top() != '(') {
                postfix += ops.top();
                postfix += ' ';
                ops.pop();
            }
            if (!ops.isEmpty()) ops.pop(); // 弹出 '('
        }
        // 运算符 + - × ÷
        else if (isOperator(c)) {
            while (!ops.isEmpty() && ops.top() != '(' && priority(ops.top()) >= priority(c)) {
                postfix += ops.top();
                postfix += ' ';
                ops.pop();
            }
            ops.push(c);
        }
    }

    // 弹出剩余运算符
    while (!ops.isEmpty()) {
        postfix += ops.top();
        postfix += ' ';
        ops.pop();
    }

    return postfix;
}

int ExpressionCalculator::evaluatePostfix(const QString& postfix)
{
    QStack<int> nums;

    for (int i = 0; i < postfix.length(); ++i) {
        QChar c = postfix[i];

        if (c.isDigit()) {
            // 解析多位数字
            int num = 0;
            while (i < postfix.length() && postfix[i].isDigit()) {
                num = num * 10 + (postfix[i].toLatin1() - '0');
                ++i;
            }
            nums.push(num);
            --i;
        }
        else if (isOperator(c)) {
            if (nums.size() < 2) {
                throw std::runtime_error("表达式错误：操作数不足");
            }
            int b = nums.pop();
            int a = nums.pop();
            int result = applyOperator(a, b, c);
            nums.push(result);
        }
    }

    if (nums.size() != 1) {
        throw std::runtime_error("表达式错误：最终结果数异常");
    }
    return nums.pop();
}

bool ExpressionCalculator::isOperator(const QChar& c)
{
    return (c == '+' || c == '-' || c == QChar(0x00D7) || c == QChar(0x00F7)); // Unicode字符0x00D7表示×
}

int ExpressionCalculator::priority(const QChar& op)
{
    if (op == '+' || op == '-') return 1;
    if (op == QChar(0x00D7) || op == QChar(0x00F7)) return 2;
    return 0;
}

int ExpressionCalculator::applyOperator(int a, int b, const QChar& op)
{
    switch (op.unicode()) {
    case 0x002B: return a + b;
    case 0x002D: return a - b;
    case 0x00D7: return a * b;
    case 0x00F7:
        if (b == 0) {
            qDebug() << "除数不能为0\n";
            throw std::runtime_error("除数不能为0");
        }
        return a / b;
    default:
        qDebug() << (op.toLatin1() == QChar(0x00d7)) << "未知运算符\n";
        throw std::runtime_error("未知运算符");
    }
}