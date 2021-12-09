#include "calculator.h"
#include "ui_calculator.h"

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);
    ui->grpbox_advance->hide();
    ui->grpbox_option->hide() ;
    ui->grpbox_stepbystep->hide() ;
}

calculator::~calculator()
{
    delete ui;
}

int calculator::opr_priority(QChar ch)
{
    if(ch == '+' || ch == '-')
        return 1;
    else if(ch == '*' || ch == '/')
        return 2;
    else if(ch == '^')
        return 3;
    else
        return 0;
}

bool calculator::isnegetivsign(QString str, int i)
{
    if (i == 0 )
        return true;
    if (str[i-1] == ')' and str[i+1] == '(')
        return false;
    if (isnum( str[i-1]) and isnum( str[i+1] ))
        return false;
    if (str[i-1] == ')' and isnum( str[i+1]))
        return false;
    return true;
}

QString calculator::clearinput(QString input)
{
    for (auto it=0 ; it < input.length() ; it++)
        if (input[it] == ' ' )
        {
            input.remove(it,1) ;
            it--;
        }
        else if ( input[it] == '\n' )
        {
            input.remove(it,2) ;
            it-=2;
        }
    return input;
}

QList<QString> calculator::infixtopostfix(QString infix)
{
    Stack<char> stack;
    QList<QString> postfix ;
    bool flag = true ;
    int i=0 ;
    for(auto it = infix.begin(); it!=infix.end(); it++ , i++)
    {
        if(isnum(*it))
            if (flag == true)// flag its gone detect num with more than one digits
                postfix += *it;
            else
            {
                QString s = postfix.last() + *it ;
                postfix.pop_back() ;
                postfix.append(s) ;
            }
        else if(*it == '(')
            stack.push('(');
        else if(*it == '^')
            stack.push('^');
        else if(*it == ')')
        {
            while(!stack.isemptys() && stack.top() != '(')
                postfix.append(QChar::fromLatin1( stack.pop() )) ;
            stack.pop();
        }
        else if (isopr(*it))
        {
            if (*it == '-' and isnegetivsign(infix , i ))
                postfix += "0" ;
            if(opr_priority(*it) > opr_priority(stack.top()))
                stack.push(it->toLatin1());
            else
            {
                while(!stack.isemptys() && opr_priority(*it) <= opr_priority(stack.top()))
                    postfix += QChar::fromLatin1( stack.pop() );
                stack.push(it->toLatin1());
            }
        }
        flag = !isnum(*it) ;
    }
    while(!stack.isemptys())
        postfix +=QChar::fromLatin1( stack.pop() );
    return postfix;
}

bool calculator::isnum(QString input)
{
    if (input == "0")
        return true;
    if (input == "1")
        return true;
    if (input == "2")
        return true;
    if (input == "3")
        return true;
    if (input == "4")
        return true;
    if (input == "5")
        return true;
    if (input == "6")
        return true;
    if (input == "7")
        return true;
    if (input == "8")
        return true;
    if (input == "9")
        return true;
    if (input == ".")
        return true;
    return false;
}

bool calculator::isopr(QString input)
{
    if (input == "+")
        return true;
    if (input == "-")
        return true;
    if (input == "/")
        return true;
    if (input == "*")
        return true;
    if (input == "^")
        return true;
    return false;
}

bool calculator::ismatch(QString input)
{

    return true;
}

double calculator::calculate(QList<QString> postfix)
{
    double answer = 0 ;
    int i=0 ;
    auto it = postfix.begin() ;
    while ( postfix.size() != 1 )
    {
        if (isopr(*it))
        {
            QString opr = *it ;
            it--;
            i--;
            double num2 = (*it).toDouble() ;
            it--;
            i--;
            double num1 = (*it).toDouble() ;
            //int n = postfix.indexOf(*it) ;
            postfix.removeAt(i) ;
            postfix.removeAt(i) ;
            postfix.removeAt(i) ;
            if (opr == "+")
                answer = num1 + num2 ;
            else if (opr == "-")
                answer = num1 - num2 ;
            else if (opr == "*")
                answer = num1 * num2 ;
            else if (opr == "/")
                answer = num1 / num2 ;
            else if (opr == "^")
                answer = pow(num1 , num2) ;
            postfix.insert(i, QString::number(answer)) ;
            it = postfix.begin() ;
            i=0;
            continue;
        }
        ++it ;
        i++ ;
    }
    return answer;
}


void calculator::on_equalbtn_pressed()
{
    QString infix = ui->inputpte->toPlainText() ;
    if ( !ismatch(infix) )
    {
        ui->inputpte->clear() ;
        ui->inputpte->setPlaceholderText("error !") ;
        QMessageBox::information(this , "error" , "input is invalid try again") ;
        return;
    }
    QString xx = clearinput(infix) ;
    QList<QString> a = infixtopostfix(xx) ;
    double output = calculate(a) ;
    ui->inputpte->clear() ;
    ui->inputpte->setPlainText(QString::number(output)) ;
}

