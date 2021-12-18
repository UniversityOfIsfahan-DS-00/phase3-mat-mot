#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QObject>
#include <QStringList>
#include <QMessageBox>
#include <QString>
#include "Stack.h"
#include <QChar>
#include <QDebug>
#include <wchar.h>
#include <QList>
#include <string.h>
#include <QIcon>
#include <string>
#include "Tree.h"
#include <QShortcut>
#include <cmath>
QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

class calculator : public QMainWindow
{
    Q_OBJECT
    double memory ;
    bool memoryenable ;
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
    double calculate (QList<QString> postfix , bool stepbystepon ) ;
    QString postfixtoinfix (QList<QString> postfix) ;
private slots:

    void on_equalbtn_pressed();

   // void on_stepbystepboxbtn_clicked(bool checked);

    void on_stepbystepboxbtn_pressed();

    void on_stepbystepboxbtn_clicked();

    void on_openbraketbtn_pressed();

    void on_closebraketbtn_pressed();

    void on_zerobtn_pressed();

    void on_dotbtn_pressed();

    void on_onebtn_pressed();

    void on_twobtn_pressed();

    void on_threebtn_pressed();

    void on_plusbtn_pressed();

    void on_fourbtn_pressed();

    void on_fivebtn_pressed();

    void on_sixbtn_pressed();

    void on_minesbtn_pressed();

    void on_sevenbtn_pressed();

    void on_eightbtn_pressed();

    void on_ninebtn_pressed();

    void on_fullclearbtn_pressed();

    void on_powerbtn_pressed();

    void on_divisinbtn_pressed();

    void on_multiplebtn_pressed();

    void on_singledeletebtn_pressed();

    void on_mcbtn_pressed();

    void on_mrbtn_pressed();

    void on_mplusbtn_pressed();

    void on_mminesbtn_pressed();

    void on_optionboxbtn_pressed();

    void on_optionboxbtn_clicked();

    void on_inputpte_textChanged();

    void on_treeptebtn_clicked();

    void on_treeptebtn_pressed();

    void on_actionExit_triggered();

private:
    Ui::calculator *ui;
};
#endif // CALCULATOR_H
