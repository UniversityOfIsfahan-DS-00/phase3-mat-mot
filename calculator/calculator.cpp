#include "calculator.h"
#include "ui_calculator.h"

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);
    this->memory = 0 ;
    this->memoryenable = false ;
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
    for (int it=0 ; it < input.length() ; it++)
        if (input[it] == ' ' or input[it] == '\n' )
        {
            input.remove(it,1) ;
            it--;
        }
//        else if ( input[it] == '\n' )
//        {
//            if (it == 0)
//            {
//                input.remove(it , 1) ;
//                continue;
//            }
//            input.remove(it,2) ;
//            it-=2;
//        }
    return input;
}

QList<QString> calculator::infixtopostfix(QString infix)// this function convert infix to postfix
{
    Stack<char> stack;
    QList<QString> postfix ;
    bool flag = true ;
    int i=0 ;
    for(QString::iterator it = infix.begin(); it!=infix.end(); it++ , i++)
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
    if (input.isEmpty())
        return false;
    input = clearinput(input) ; // removeing " " and "\n" in input to continue
    Stack<QString> stk ;
    for (int i=0 ; i<input.length() ; i++)// check all char in string
        if (isopr(input[i]) or input[i] == ')' or input[i] == '(')
        {
            if ( input[i] == '(' )// brakets checker ()
            {
                stk.push("(") ;
                continue;
            }
            else if (input[i] == ')')
            {
                if (stk.isemptys())
                    return false;
                if (stk.top() == "(" )
                {
                    stk.pop() ;
                    continue;
                }
                else
                    return false;
            }
            else if (i == 0 or i==input.length()-1 ) // check opr in first of input
            {
                if (input[i] == '-' and i==0 )
                    continue;
                return false;
            }
            else if (input[i] == '/' and input[i+1] == '0')
                return false;
            else if (input[i-1] == ')' and input[i+1] == '(')// check ) opr ( if true will continue in other char
                continue;
            else if (isnum( input[i-1]) and isnum( input[i+1] ))// check "num" opr "num" if true will continue in other char
                continue;
            else if (input[i-1] == ')' and isnum( input[i+1]))// check ) opr "num" if true will continue in other char
                continue;
            else if (isnum( input[i-1]) and input[i+1] == '(' )// check "num" opr ( if true will continue in other char
                continue;
            else if (input[i] == '-')
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

double calculator::calculate(QList<QString> postfix , bool stepbystepon )// calculate the input
{
    double answer = 0 ;
    int i=0 , j = 2 ;
    QList<QString>::iterator it = postfix.begin() ;
    Stack<QString> stk ;
    while (it!=postfix.end())
    {
        if (isopr((*it)))
        {
            double num2 = stk.pop().toDouble() ;
            double num1 = stk.pop().toDouble() ;
            QString opr = *it ;
            if (opr == "+")
                answer = num1 + num2 ;
            else if (opr == "-")
                answer = num1 - num2 ;
            else if (opr == "*")
                answer = num1 * num2 ;
            else if (opr == "/")
                answer = num1 / num2 ;
            else if (opr == "^")
                answer = pow(num1 , num2) ;//***********************---------complexity of pow is O(n) ;
            answer = round(answer*10000000)/10000000 ;
            stk.push(QString::number( answer , 'g' , 15 )) ;//********************------complexity of number is O(n) ;
            if (stepbystepon)
            {
                Stack<QString> stktmp ;
                stktmp =  stk  ; //*************----------------O(n)
                QList<QString> listtmp ;
                while (!stktmp.isemptys())//***********---- O(n)
                {
                        listtmp.push_back(stktmp.pop()) ;
                }
                QList<QString>::iterator ittmp = it ;
                ++ittmp ;
                while (ittmp != postfix.end())//***********------------O(n)
                {
                    listtmp.push_back(*ittmp) ;
                    ++ittmp ;
                }
                ui->stepbysteppte->appendPlainText(QString::number( j ) + " --> " + postfixtoinfix(listtmp) + "\n" ) ;//***---- complexity of postfix to infix is O(n)
                j++ ;
            }
        }
        else
            stk.push(*it) ;
        ++it ;
        i++ ;
    }
    //    while ( postfix.size() != 1 )
    //    {
    //        if (isopr(*it))
    //        {
    //            QString opr = *it ;
    //            it--;
    //            i--;
    //            double num2 = (*it).toDouble() ;
    //            it--;
    //            i--;
    //            double num1 = (*it).toDouble() ;
    //            postfix.removeAt(i) ;
    //            postfix.removeAt(i) ;
    //            postfix.removeAt(i) ;
    //            if (opr == "+")
    //                answer = num1 + num2 ;
    //            else if (opr == "-")
    //                answer = num1 - num2 ;
    //            else if (opr == "*")
    //                answer = num1 * num2 ;
    //            else if (opr == "/")
    //                answer = num1 / num2 ;
    //            else if (opr == "^")
    //                answer = pow(num1 , num2) ;
    //            answer = round(answer*100000)/100000 ;
    //            postfix.insert(i, QString::number(answer)) ;
    //            if (stepbystepon)
    //                ui->stepbysteppte->appendPlainText(QString::number( j ) + " --> " + postfixtoinfix(postfix) + "\n" ) ;
    //            it = postfix.begin() ;
    //            i=0;
    //            j++ ;
    //            continue;
    //        }
    //        ++it ;
    //        i++ ;
    //    }
    //    answer = postfix.first().toDouble() ;
    answer = stk.pop().toDouble() ;
    return answer;
}

QString calculator::postfixtoinfix(QList<QString> postfix)// converte postfix to infix
{
    QString infix ;
    Stack<QString> stk ;
    //for (auto it = postfix.begin() ; it!=postfix.end() ; ++it)
    for (QString it  : postfix)
    {
        if (isopr(it))
        {
            QString num2 = stk.pop() ;
            QString num1 = stk.pop() ;
            stk.push("(" + num1 + it + num2 + ")") ;
        }
        else
            stk.push(it) ;
    }
    infix = stk.pop() ;
    return infix;
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
    ui->stepbysteppte->clear() ;
    ui->stepbysteppte->setPlainText("1 --> " + infix + "\n" ) ;
    double output = calculate(infixtopostfix(clearinput(infix)) , true ) ;// calling 3 function in each other first call clearinput then call infix to postfix then call calculate fu
    ui->stepbysteppte->appendPlainText("final --> " + QString::number(output , 'g' , 15 ) + "\n" ) ;
    ui->inputpte->clear() ;// clear input plain text edit
    ui->inputpte->setPlainText(QString::number(output , 'g' , 15)) ; // set answer in input plain text edit
}


void calculator::on_stepbystepboxbtn_pressed()
{
    ui->grpbox_stepbystep->show() ;
}


void calculator::on_stepbystepboxbtn_clicked()
{
    ui->grpbox_stepbystep->hide() ;
}


void calculator::on_openbraketbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"(") ;
}


void calculator::on_closebraketbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+")") ;
}


void calculator::on_zerobtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"0") ;
}


void calculator::on_dotbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+".") ;
}


void calculator::on_onebtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"1") ;
}


void calculator::on_twobtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"2") ;
}


void calculator::on_threebtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"3") ;
}


void calculator::on_plusbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"+") ;
}


void calculator::on_fourbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"4") ;
}


void calculator::on_fivebtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"5") ;
}


void calculator::on_sixbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"6") ;
}


void calculator::on_minesbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"-") ;
}


void calculator::on_sevenbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"7") ;
}


void calculator::on_eightbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"8") ;
}


void calculator::on_ninebtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"9") ;
}


void calculator::on_fullclearbtn_pressed()
{
    ui->inputpte->clear();
}


void calculator::on_powerbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"^") ;
}


void calculator::on_divisinbtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"/") ;
}


void calculator::on_multiplebtn_pressed()
{
    ui->inputpte->setPlainText(ui->inputpte->toPlainText()+"*") ;
}


void calculator::on_singledeletebtn_pressed()
{
    //ui->inputpte->deleteLater();
    QString a = ui->inputpte->toPlainText() ;
    a.remove(a.length()-1 , 1) ;
    ui->inputpte->setPlainText(a) ;
}


void calculator::on_mcbtn_pressed()
{
    this->memory = 0 ;
    this->memoryenable = false ;
}


void calculator::on_mrbtn_pressed()
{
    if (memoryenable)
        ui->inputpte->setPlainText(ui->inputpte->toPlainText() + QString::number(memory)) ;
}


void calculator::on_mplusbtn_pressed()
{
    if ( !ismatch(ui->inputpte->toPlainText()) )// call is match fu that control input valieableity
    {
        QMessageBox::information(this , "error" , "input is invalid try again") ;
        return;
    }
    this->memoryenable = true ;
    this->memory += calculate(infixtopostfix(ui->inputpte->toPlainText()) , false) ;
}


void calculator::on_mminesbtn_pressed()
{
    if ( !ismatch(ui->inputpte->toPlainText()) )// call is match fu that control input valieableity
    {
        QMessageBox::information(this , "error" , "input is invalid try again") ;
        return;
    }
    this->memoryenable = true ;
    this->memory -= calculate(infixtopostfix(ui->inputpte->toPlainText()) , false) ;
}

