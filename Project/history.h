#ifndef HISTORY_H
#define HISTORY_H

#include <QVector>
#include <QString>
#include <QTextEdit>

class history
{
public:
    history();
    history(QTextEdit *inp);
    ~history();

    QVector<QString> inphistory;//содержить только то, что вводил пользователь (т.е. без знаков *)
    QString allhistory;//содержит все, что находится в inptxt
    int pointer;
        //QString laststring;//содержит последнюю строку (ту, что выполняется в executor). НЕ УВЕРЕН, ЧТО НУЖНА

    QVector<QString> result;//содержит информацию о выводимом в формате ТЕХ результате

    void clear();
    void add(QTextEdit *inp);

    void fullclear();//использовать только при полной чистке!!!!! очищает в том числе результаты, которые потом не восстановить
};

#endif // HISTORY_H
