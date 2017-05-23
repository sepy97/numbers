#include "history.h"

history::history()
{

}

history::history(QTextEdit *inp)
{
    this->add(inp);
}

void history::clear(){
    this->allhistory.clear();
    this->inphistory.clear();
    this->pointer = 0;
    //this->result.clear();
}

void history::fullclear(){
    this->clear();
    this->result.clear();
}

void history::add(QTextEdit *inp)
{
    this->clear();
    this->allhistory = inp->toPlainText();
    QString tmp;
    for (int i = 0; i < this->allhistory.size(); i++){
        if (this->allhistory[i]=='*'){

        }else if (this->allhistory[i]== '\n'){
            if (this->allhistory[i-1]!='*') {
                this->inphistory.push_back(tmp);
                tmp.clear();
            }
        }else if(i == this->allhistory.size()-1){
            tmp.push_back(this->allhistory[i]);
            this->inphistory.push_back(tmp);
        }else{
            tmp.push_back(this->allhistory[i]);
        }
    }
    pointer = this->inphistory.size();
}

history::~history()
{

}

