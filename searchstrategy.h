#ifndef SEARCHSTRATEGY_H
#define SEARCHSTRATEGY_H

#include <QString>
#include <QSqlQueryModel>

class SearchStrategy
{
public:
    virtual ~SearchStrategy() = default;
    virtual QSqlQueryModel* search(const QString& keyword) const = 0;
};

class SearchByTitle : public SearchStrategy
{
public:
    QSqlQueryModel* search(const QString& keyword) const override;
};

class SearchByAuthor : public SearchStrategy
{
public:
    QSqlQueryModel* search(const QString& keyword) const override;
};

class SearchByYear : public SearchStrategy
{
public:
    QSqlQueryModel* search(const QString& keyword) const override;
};

#endif // SEARCHSTRATEGY_H
