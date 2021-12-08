#include "calculator.h"
#include "ui_calculator.h"

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);

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

QList<QString> calculator::infixtopostfix(QString infix)
{
    Stack<char> stack;
    QList<QString> postfix ;
    bool flag = true ;
    for(auto it = infix.begin(); it!=infix.end(); it++)
    {
        if(isnum(*it))
            if (flag == true)
                postfix += *it;
            else
            {
                QString s = postfix.first() + *it ;
                postfix.pop_front() ;
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
        else
        {
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
