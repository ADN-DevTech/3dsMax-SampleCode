/********************************************************************************
** Form generated from reading UI file 'server_rollup.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_ROLLUP_H
#define UI_SERVER_ROLLUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_server_rollup
{
public:
    QGridLayout *gridLayout;
    QPushButton *button_start;
    QPlainTextEdit *text_status;

    void setupUi(QWidget *server_rollup)
    {
        if (server_rollup->objectName().isEmpty())
            server_rollup->setObjectName(QStringLiteral("server_rollup"));
        server_rollup->resize(116, 144);
        gridLayout = new QGridLayout(server_rollup);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        button_start = new QPushButton(server_rollup);
        button_start->setObjectName(QStringLiteral("button_start"));
        button_start->setCheckable(true);

        gridLayout->addWidget(button_start, 0, 0, 1, 1);

        text_status = new QPlainTextEdit(server_rollup);
        text_status->setObjectName(QStringLiteral("text_status"));

        gridLayout->addWidget(text_status, 1, 0, 1, 1);


        retranslateUi(server_rollup);

        QMetaObject::connectSlotsByName(server_rollup);
    } // setupUi

    void retranslateUi(QWidget *server_rollup)
    {
        server_rollup->setWindowTitle(QApplication::translate("server_rollup", "Form", 0));
        button_start->setText(QApplication::translate("server_rollup", "Start Server", 0));
    } // retranslateUi

};

namespace Ui {
    class server_rollup: public Ui_server_rollup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_ROLLUP_H
