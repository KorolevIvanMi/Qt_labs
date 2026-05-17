#include "searchstrategy.h"
#include <QSqlQuery>

QSqlQueryModel* SearchByTitle::search(const QString& keyword) const
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT id, title, author, year, "
                  "CASE WHEN available=1 THEN 'В наличии' ELSE 'Выдана' END as status "
                  "FROM books WHERE title LIKE ?");
    query.addBindValue("%" + keyword + "%");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Автор");
    model->setHeaderData(3, Qt::Horizontal, "Год");
    model->setHeaderData(4, Qt::Horizontal, "Статус");
    return model;
}

QSqlQueryModel* SearchByAuthor::search(const QString& keyword) const
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT id, title, author, year, "
                  "CASE WHEN available=1 THEN 'В наличии' ELSE 'Выдана' END as status "
                  "FROM books WHERE author LIKE ?");
    query.addBindValue("%" + keyword + "%");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Автор");
    model->setHeaderData(3, Qt::Horizontal, "Год");
    model->setHeaderData(4, Qt::Horizontal, "Статус");
    return model;
}

QSqlQueryModel* SearchByYear::search(const QString& keyword) const
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    bool ok;
    int year = keyword.toInt(&ok);
    if (!ok) year = 0;
    query.prepare("SELECT id, title, author, year, "
                  "CASE WHEN available=1 THEN 'В наличии' ELSE 'Выдана' END as status "
                  "FROM books WHERE year = ?");
    query.addBindValue(year);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Автор");
    model->setHeaderData(3, Qt::Horizontal, "Год");
    model->setHeaderData(4, Qt::Horizontal, "Статус");
    return model;
}
