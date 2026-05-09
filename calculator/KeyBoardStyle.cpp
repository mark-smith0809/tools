#include "KeyBoardStyle.h"

namespace KeyBoardStyle {
const QString NormalButtonStyle = QString(R"(
                QPushButton {
                    background-color: #ffffff;
                    font-size: 20px;
                    color: black;
                }
                QPushButton:hover {
                    background-color: #eeeeee;
                }
                QPushButton:pressed {
                    background-color: #dddddd;
                }
            )");
const QString SymbolButtonStyle(R"(
                QPushButton {
                    background-color: #ffffff;
                    font-size: 20px;
                    color: black;
                }
                QPushButton:hover {
                    background-color: #eeeeee;
                }
                QPushButton:pressed {
                    background-color: #dddddd;
                }
            )");
const QString AbnormalButtonStyle(R"(
                QPushButton {
                    background-color: #f1f5fa;
                    font-size: 20px;
                    color: #b2b5b9;
                }
            )");
const QString EqualButtonStyle(R"(
                QPushButton {
                    background-color: #023363;
                    font-size: 20px;
                    color: white;
                }
                QPushButton:hover {
                    background-color: #194672;
                }
                QPushButton:pressed {
                    background-color: #315981;
                }
            )");
const QString MechanismButtonStyle(R"(
                QPushButton {
                    text-align: left;
                    border: none;
                    background-color: transparent;
                    color: black;
                }
                QPushButton:hover {
                    background-color: #dddddd;
                }
                QPushButton:pressed {
                    background-color: #bbbbbb;
                }
            )");
}