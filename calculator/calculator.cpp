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
    ui->advanceboxbtn->hide() ;
    ui->optionboxbtn->hide() ;
}

calculator::~calculator()
{
    delete ui;
}

int calculator::opr_priority(QChar ch)// check priority of operator
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

bool calculator::isnegetivsign(QString str, int i)// this function detect diffrence between - and negetive sign
{
    if (i == 0 )
        return true;
    if (str[i-1] == ')' and str[i+1] == '(')
        return false;
    if (isnum( str[i-1]) and isnum( str[i+1] ))
        return false;
    if (str[i-1] == ')' and isnum( str[i+1]))
        return false;
    if (isnum( str[i-1]) and str[i+1] == '(' )
        return false;
    return true;
}

QString calculator::clearinput(QString input) // this function clear " " and "\n" in input
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

QList<QString> calculator::infixtopostfix(QString infix)// this function convert infix to postfix
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
        else if (isopr(*it))// add operator
        {
            if (*it == '-' and isnegetivsign(infix , i ))
                postfix += "0" ;
            if(opr_priority(*it) > opr_priority(stack.top()))// check priority of operator
                stack.push(it->toLatin1());
            else
            {
                while(!stack.isemptys() && opr_priority(*it) <= opr_priority(stack.top()))
                    postfix += QChar::fromLatin1( stack.pop() );
                stack.push(it->toLatin1());
            }
        }
        flag = !isnum(*it) ; // if last operator is num flag is false
    }
    while(!stack.isemptys())// check existed operator in stack
        postfix +=QChar::fromLatin1( stack.pop() );
    return postfix;
}

bool calculator::isnum(QString input) // check the number and .
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

bool calculator::isopr(QString input)// check the  math operator
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

bool calculator::ismatch(QString input)// check input and return bool
{
    input = clearinput(input) ; // removeing " " and "\n" in input to continue
    Stack<QString> stk ;
    for (int i=0 ; i<input.length() ; i++)// check all char in string
        if (isopr(input[i]) or input[i] == ')' or input[i] == '(')
        {
            if ( input[i] == '(' )// brakets checker ()
                stk.push("(") ;
            else if (input[i] == ')')
            {
                if (stk.isemptys())
                    return false;
                if (stk.top() == "(" )
                    stk.pop() ;
                else
                    return false;
            }
            if (i == 0 or i==input.length()-1 ) // check opr in first of input
                return false;
            if (input[i] == '/' and input[i+1] == '0')
                return false;
            if (input[i-1] == ')' and input[i+1] == '(')// check ) opr ( if true will continue in other char
                continue;
            if (isnum( input[i-1]) and isnum( input[i+1] ))// check "num" opr "num" if true will continue in other char
                continue;
            if (input[i-1] == ')' and isnum( input[i+1]))// check ) opr "num" if true will continue in other char
                continue;
            if (isnum( input[i-1]) and input[i+1] == '(' )// check "num" opr ( if true will continue in other char
                continue;
            return false;// if opr does like four type then it is in valid
        }
        else if (!isnum(input[i]))
            return false;
    if (stk.isemptys())
        return true;
    else
        return false;
    return true;
}

double calculator::calculate(QList<QString> postfix)// calculate the input
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


void calculator::on_equalbtn_pressed()// ==
{
    QString infix = ui->inputpte->toPlainText() ;// get input from plain text edit in basic box
    if ( !ismatch(infix) )// call is match fu that control input valieableity
    {
        //ui->inputpte->clear() ;
        //ui->inputpte->setPlaceholderText("error !") ;
        QMessageBox::information(this , "error" , "input is invalid try again") ;
        return;
    }
    double output = calculate(infixtopostfix(clearinput(infix))) ;// calling 3 function in each other first call clearinput then call infix to postfix then call calculate fu
    ui->inputpte->clear() ;// clear input plain text edit
    ui->inputpte->setPlainText(QString::number(output)) ; // set answer in input plain text edit
}

