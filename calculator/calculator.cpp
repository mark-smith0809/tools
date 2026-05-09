#include "calculator.h"
#include "KeyBoardStyle.h"
#include "expressioncalculator.h"

const std::vector<std::vector<QString>> Calculator::buttonNameOfCoder = {
    {"A","<<",">>","CE","Del"},
    {"B","(",")","%","÷"},
    {"C","7","8","9","×"},
    {"D","4","5","6","-"},
    {"E","1","2","3","+"},
    {"F","+/-","0",".","="}
};

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
{

    // 顶部先使用文字，右对齐
    QLayout *topLayout = GenerateTopLayout();

    // 中间使用文字，左对齐
    QLayout *middleLayout = GenerateMiddleLayout();

    // 下方放置网格按钮
    QLayout *bottomLayout = GenerateBottomLayout();


    // 主布局 使用QVBoxLayout
    QWidget *center = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(center);

    mainLayout->addLayout(topLayout, 2);
    mainLayout->addLayout(middleLayout, 2);
    mainLayout->addLayout(bottomLayout, 6);

    this->resize(400, 600);
    this->setCentralWidget(center);
    // 初始化键盘布局
    InitKeyBoardStyle();
    // 设置进制
    SetMechanism(Mechanism::DEC);
    // 设置键盘布局
    SetKeyBoardArea(Mechanism::DEC);
    // 显示值
    ShowValue();
    //状态设置
    inputStatus = InputStatus::WAITING_NEW_NUM;
}

// 按键事件(数字/符号)
void Calculator::ButtonClicked(int index)
{
    QString str = buttons[index]->text();
    if (str == "CE") {
        expressionLabel->setText("");
        resultLabel->setText("");
    } else if (str == "Del") {
        QString expression = resultLabel->text();
        expression = expression.left(expression.size() - 1);
        if (expression == "") expression = "0";
        resultLabel->setText(expression);
    } else if (str == ".") {
        // 小数点暂未实现
    } else if (str == "=") {
        int value = ExpressionCalculator::calculate(expressionLabel->text() + resultLabel->text());
        QString expression = expressionLabel->text() + resultLabel->text() + "=";
        expressionLabel->setText(expression);
        QString result = ConvertIntToString(value);
        resultLabel->setText(result);
        inputStatus = InputStatus::COMPLETE_INPUT;
        ShowValue();
    } else {
        // 运算符，括号，数字
        QRegularExpression num_Re(R"([0-9])");
        QRegularExpressionMatchIterator isFind = num_Re.globalMatch(str);
        if (isFind.hasNext()) { // 数字
            if (inputStatus == InputStatus::COMPLETE_INPUT) {
                expressionLabel->setText("");
                resultLabel->setText("");
                inputStatus = InputStatus::WAITING_NEW_NUM;
            } else if (inputStatus == InputStatus::CONTINUING_NUM) {
                QString result = resultLabel->text();
                result += str;
                resultLabel->setText(result);
            } else if (inputStatus == InputStatus::WAITING_NEW_NUM) {
                resultLabel->setText(str);
                inputStatus = InputStatus::CONTINUING_NUM;
            } else {
                qDebug() << __FILE__ << __LINE__ << "error status" << inputStatus << Qt::endl;
            }
            return;
        }
        QRegularExpression symbol_Re(R"([+\-×÷])");
        isFind = symbol_Re.globalMatch(str);
        if (isFind.hasNext()) { // 运算符
            if (inputStatus == InputStatus::COMPLETE_INPUT) {
                QString result = resultLabel->text();
                QString expression = result + str;
                expressionLabel->setText(expression);
                resultLabel->setText("");
                inputStatus = InputStatus::WAITING_NEW_NUM;
            } else if (inputStatus == InputStatus::WAITING_NEW_NUM) {
                qDebug() << "invalid input" << str << Qt::endl;
            } else if (inputStatus == InputStatus::CONTINUING_NUM) {
                QString expression = expressionLabel->text();
                QString result = resultLabel->text();
                expression = expression + result + str;
                expressionLabel->setText(expression);
                resultLabel->setText("");
                inputStatus = InputStatus::WAITING_NEW_NUM;
            }
            return;
        }
        qDebug() << __FILE__ << __LINE__ << "error input" << str << Qt::endl;
    }

    // QString expression = resultLabel->text();
    // if (expression == "0") {
    //     expression = str;
    // } else {
    //     expression += str;
    // }
    // resultLabel->setText(expression);
    // ShowValue();

}

QLayout* Calculator::GenerateTopLayout()
{
    expressionLabel = new QLabel;
    expressionLabel->setObjectName("EXPRESSION");
    expressionLabel->setText("");
    expressionLabel->setStyleSheet(R"(
        color: #888888;
        font-size: 24px;
    )");
    expressionLabel->setAlignment(Qt::AlignRight);

    resultLabel = new QLabel;
    resultLabel->setObjectName("RESULT");
    resultLabel->setText("0");
    resultLabel->setStyleSheet(R"(
        font-size: 30px;
        fpmt=weight: bold;
    )");
    resultLabel->setAlignment(Qt::AlignRight);

    QVBoxLayout *topLabelLayout = new QVBoxLayout;
    topLabelLayout->addWidget(expressionLabel);
    topLabelLayout->addWidget(resultLabel);

    return topLabelLayout;
}

QLayout *Calculator::GenerateMiddleLayout()
{
    QVBoxLayout *middleValueLayout = new QVBoxLayout;
    for (size_t i = 0; i < MechanismBase::mechanismNameStr.size(); i++) {
        MechanismBase *base = new MechanismBase();
        mechanismVec.push_back(base);
        QLayout *layout = base->GenerateLayout(static_cast<Mechanism>(i));
        middleValueLayout->addLayout(layout);
        connect(base->button, &QPushButton::clicked, this, [=](){
            SetMechanism(static_cast<Mechanism>(i));
        });
    }
    return middleValueLayout;
}

QLayout *Calculator::GenerateBottomLayout()
{
    QGridLayout *bottomButtonLayout = new QGridLayout;
    bottomButtonLayout->setObjectName("GRIDOFBUTTONS");
    for (size_t i = 0; i < Calculator::buttonNameOfCoder.size(); i++) {
        for (size_t j = 0; j < Calculator::buttonNameOfCoder[0].size(); j++) {
            QPushButton *qPushButton = new QPushButton(Calculator::buttonNameOfCoder[i][j]);
            QPalette palette = qPushButton->palette();
            qPushButton->setAutoFillBackground(false);
            qPushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            qPushButton->setMinimumSize(60, 30);
            connect(qPushButton, &QPushButton::clicked, this, [=](){
                ButtonClicked(i * Calculator::buttonNameOfCoder[0].size() + j);
            });

            buttons.push_back(qPushButton);
            bottomButtonLayout->addWidget(qPushButton, i, j);
        }
    }
    for (size_t row = 0; row < Calculator::buttonNameOfCoder.size(); row++) {
        bottomButtonLayout->setRowStretch(row, 1);
    }
    for (size_t col = 0; col < Calculator::buttonNameOfCoder[0].size(); col++) {
        bottomButtonLayout->setColumnStretch(col, 1);
    }
    bottomButtonLayout->setSpacing(1);

    return bottomButtonLayout;
}

void Calculator::SetMechanism(const Mechanism &mechanism)
{
    if (static_cast<uint32_t>(mechanism) > MechanismBase::mechanismNameStr.size()) {
        qDebug() << "file:" << __FILE__ << ",line:" << __LINE__ << "," << static_cast<uint32_t>(mechanism) << "out of vector range\n";
    }
    mechanismVec[static_cast<uint32_t>(mechanismType)]->SetEnable(false);
    QString valueStr = resultLabel->text();
    int value = ConvertStringToInt(valueStr);
    mechanismType = mechanism;
    mechanismVec[static_cast<uint32_t>(mechanismType)]->SetEnable(true);
    //将结果也重置为对应进制
    expressionLabel->setText("");
    valueStr = ConvertIntToString(value);
    resultLabel->setText(valueStr);
}

void Calculator::SetKeyBoardArea(const Mechanism &mechanism)
{
    if (mechanism == Mechanism::DEC) { // 十进制
        SetDecKeyBoard();
    }
}

void Calculator::InitKeyBoardStyle()
{
    std::vector<QString> styles {
        KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,

            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,


            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,

            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,

            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,

            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::NormalButtonStyle,
            KeyBoardStyle::SymbolButtonStyle,
            KeyBoardStyle::EqualButtonStyle,
    };
    if (styles.size() != buttons.size()) {
        qDebug() << __FILE__ << __LINE__ << "size of styles is not equal to buttons\n";
        return;
    }
    for (size_t i = 0; i < styles.size(); i++) {
        buttons[i]->setStyleSheet(styles[i]);
    }
}

void Calculator::SetDecKeyBoard()
{
    static std::vector<size_t> unused{0,5,10,15,20,25,28}; // 需要设置为不可用的序列号
    size_t unusedIndex = 0;
    for (size_t i = 0; i < buttons.size() - 1; i++) {
        if (unusedIndex < unused.size() && i == unused[unusedIndex]) {
            buttons[i]->setEnabled(false);
            buttons[i]->setStyleSheet(KeyBoardStyle::AbnormalButtonStyle);
            unusedIndex++;
        } else {
            buttons[i]->setEnabled(true);
            buttons[i]->setStyleSheet(KeyBoardStyle::NormalButtonStyle);
        }
    }
}

void Calculator::ShowValue()
{
    QString valueStr = resultLabel->text();
    int value = ConvertStringToInt(valueStr);
    for (const auto& mech : mechanismVec) {
        mech->ShowValue(value);
    }
}

QString Calculator::ConvertIntToString(const int &value)
{
    QString str("");
    if (mechanismType == Mechanism::HEX) {
        str = QString::number(value, 16);
    } else if (mechanismType == Mechanism::DEC) {
        str = QString::number(value, 10);
    } else if (mechanismType == Mechanism::OCT) {
        str = QString::number(value, 8);
    } else if (mechanismType == Mechanism::BIN) {
        str = QString::number(value, 2);
    }
    return str;
}

int Calculator::ConvertStringToInt(const QString &str)
{
    int value{0};
    if (mechanismType == Mechanism::HEX) {
        value = str.toInt(nullptr, 16);
    } else if (mechanismType == Mechanism::DEC) {
        value = str.toInt(nullptr, 10);
    } else if (mechanismType == Mechanism::OCT) {
        value = str.toInt(nullptr, 8);
    } else if (mechanismType == Mechanism::BIN) {
        value = str.toInt(nullptr, 2);
    }
    return value;
}

