#include <QDebug>

#include "mechanismbase.h"

const std::vector<QString> MechanismBase::mechanismTextStr = {"HEX     ", "DEC     ", "OCT     ", "BIN      "};
const std::vector<QString> MechanismBase::mechanismNameStr = {"HEX_LINE", "DEC_LINE", "OCT_LINE", "BIN_LINE"};


void MechanismBase::SetEnable(bool isEnable)
{
    if (isEnable) {
        vline->setStyleSheet(R"(
            QFrame {
                color: blue;
            }
        )");
    } else {
        vline->setStyleSheet(R"(
            QFrame {
                color: transparent;
            }
        )");
    }
}

QLayout *MechanismBase::GenerateLayout(const Mechanism &mtype)
{
    type = mtype;
    vline = new QFrame;
    vline->setFrameShape(QFrame::VLine);
    vline->setStyleSheet(R"(
        QFrame {
            color: transparent;
        }
    )");
    button = new QPushButton;
    button->setObjectName(MechanismBase::mechanismNameStr[static_cast<uint32_t>(type)]);
    button->setText(MechanismBase::mechanismTextStr[static_cast<uint32_t>(type)]);
    button->setStyleSheet(KeyBoardStyle::MechanismButtonStyle);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vline);
    layout->addWidget(button);

    return layout;
}

void MechanismBase::ShowValue(const int& value)
{
    if (type == Mechanism::HEX) {
        ShowHexValue(value);
    } else if (type == Mechanism::DEC) {
        ShowDecValue(value);
    } else if (type == Mechanism::OCT) {
        ShowOctValue(value);
    } else if (type == Mechanism::BIN) {
        ShowBinValue(value);
    }
}

void MechanismBase::ShowHexValue(const int& value) // 十六进制
{
    button->setText(MechanismBase::mechanismTextStr[static_cast<uint32_t>(type)] +
                    QString::number(value, 16));
}

void MechanismBase::ShowDecValue(const int& value) // 十进制
{
    button->setText(MechanismBase::mechanismTextStr[static_cast<uint32_t>(type)] +
                    QString::number(value, 10));
}

void MechanismBase::ShowOctValue(const int& value) // 八进制
{
    button->setText(MechanismBase::mechanismTextStr[static_cast<uint32_t>(type)] +
                    QString::number(value, 8));
}

void MechanismBase::ShowBinValue(const int& value) // 二进制
{
    button->setText(MechanismBase::mechanismTextStr[static_cast<uint32_t>(type)] +
                    QString::number(value, 2));
}
