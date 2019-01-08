/********************************************************************************
** Form generated from reading UI file 'player.ui'
**
** Created: Sat May 26 19:15:05 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER_H
#define UI_PLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Player
{
public:

    void setupUi(QWidget *Player)
    {
        if (Player->objectName().isEmpty())
            Player->setObjectName(QString::fromUtf8("Player"));
        Player->resize(400, 300);

        retranslateUi(Player);

        QMetaObject::connectSlotsByName(Player);
    } // setupUi

    void retranslateUi(QWidget *Player)
    {
        Player->setWindowTitle(QApplication::translate("Player", "Player", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Player: public Ui_Player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_H
