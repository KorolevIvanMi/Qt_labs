#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include <QSqlQueryModel>

class ModelFactory
{
public:
    virtual ~ModelFactory() = default;
    virtual QSqlQueryModel* createBookModel() const = 0;
    virtual QSqlQueryModel* createReaderModel() const = 0;
    virtual QSqlQueryModel* createLoanModel() const = 0;
    virtual QSqlQueryModel* createPublisherModel() const = 0;
};

class StandardModelFactory : public ModelFactory
{
public:
    QSqlQueryModel* createBookModel() const override;
    QSqlQueryModel* createReaderModel() const override;
    QSqlQueryModel* createLoanModel() const override;
    QSqlQueryModel* createPublisherModel() const override;
};

#endif // MODEL_FACTORY_H
