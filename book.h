#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
private:
    int m_id;
    QString m_title;
    QString m_author;
    int m_year;
    int m_publisherId;
    bool m_available;

public:
    Book(int id = 0, const QString& title = "", const QString& author = "",
         int year = 0, int publisherId = 0, bool available = true);

    int getId() const;
    void setId(int id);
    QString getTitle() const;
    void setTitle(const QString& title);
    QString getAuthor() const;
    void setAuthor(const QString& author);
    int getYear() const;
    void setYear(int year);
    int getPublisherId() const;
    void setPublisherId(int publisherId);
    bool isAvailable() const;
    void setAvailable(bool available);
};

#endif // BOOK_H
