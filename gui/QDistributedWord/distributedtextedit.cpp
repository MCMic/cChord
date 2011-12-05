#include "distributedtextedit.h"

DistributedTextEdit::DistributedTextEdit(string ip, int port, QWidget *parent) :
    QTextEdit(parent),
    TextHandler(ip,port)
{
    this->connect(this,)

}
