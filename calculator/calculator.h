#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QStringList>
#include <QMessageBox>
#include <QString>
#include "Stack.h"
#include <QChar>
#include <QDebug>
#include <wchar.h>
#include <QList>
#include <string.h>
#include <string>
#include <cmath>
QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();
    int opr_priority (QChar ch) ;
    bool isnegetivsign (QString str , int i) ;
    QString clearinput (QString input) ;
    QList<QString> infixtopostfix (QString infix) ;
    bool isnum (QString input ) ;
    bool isopr (QString input ) ;
    bool ismatch (QString input ) ;
    double calculate (QList<QString> postfix) ;
    QString postfixtoinfix (QList<QString> postfix) ;
private slots:

    void on_equalbtn_pressed();

   // void on_stepbystepboxbtn_clicked(bool checked);

    void on_stepbystepboxbtn_pressed();

    void on_stepbystepboxbtn_clicked();

private:
    Ui::calculator *ui;
};
#endif // CALCULATOR_H
