#include "book.h"

Book::Book(int id, const QString& title, const QString& author,
           int year, int publisherId, bool available)
    : m_id(id), m_title(title), m_author(author),
    m_year(year), m_publisherId(publisherId), m_available(available) {}

int Book::getId() const { return m_id; }
void Book::setId(int id) { m_id = id; }
QString Book::getTitle() const { return m_title; }
void Book::setTitle(const QString& title) { m_title = title; }
QString Book::getAuthor() const { return m_author; }
void Book::setAuthor(const QString& author) { m_author = author; }
int Book::getYear() const { return m_year; }
void Book::setYear(int year) { m_year = year; }
int Book::getPublisherId() const { return m_publisherId; }
void Book::setPublisherId(int publisherId) { m_publisherId = publisherId; }
bool Book::isAvailable() const { return m_available; }
void Book::setAvailable(bool available) { m_available = available; }
