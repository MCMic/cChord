#ifndef DISTRIBUTEDTEXTEDIT_H
#define DISTRIBUTEDTEXTEDIT_H

#include <QTextEdit>
#include "lib/TextHandler.hh"

class DistributedTextEdit : public QTextEdit, public TextHandler
{
    Q_OBJECT
public:
    explicit DistributedTextEdit(std::string,int,QWidget *parent = 0);

signals:

public slots:

};

#endif // DISTRIBUTEDTEXTEDIT_H
