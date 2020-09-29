#include "Book.h"

//Name: Book - Default Constructor
 //Precondition: None
 //Postcondition: Creates a default book
Book::Book()
{

}
//Name: Book - Overloaded Constructor
//Precondition: Requires title, author, rank and price (in dollars)
//Postcondition: Creates a book based on passed parameters
Book::Book(string title, string author, int rank, double price)
{
	m_title = title;
	m_author = author;
	m_rank = rank;
	m_price = price;
}

//Name: Mutators and Accessors
//Precondition: None
//Postcondition: Sets and Gets private member variables
string Book::getTitle()const
{
	return m_title;
}
string Book::getAuthor()const
{
	return m_author;
}
int Book::getRank()const
{
	return m_rank;
}
double Book::getPrice()const
{
	return m_price;
}
void Book::setTitle(string title)
{
	m_title = title;
}
void Book::setAuthor(string author)
{
	m_author = author;
}
void Book::setRank(int rank)
{
	m_rank = rank;
}
void Book::setPrice(double price)
{
	m_price = price;
}
// Overloaded << - Prints the details of a book
// Preconditions: all variables are set valid
// Postconditions: returns an ostream with details of a book
ostream& operator<<(ostream& output, Book& book)
{
	output << left << setw(45) << book.getTitle() << left << setw(25) << book.getAuthor() << book.getPrice();

	return output;
}
// Overloaded < - compares the price of the book
// Preconditions: all variables are set valid
// Postconditions: returns true if lhs price is less than rhs price
bool operator< (Book const & lhs, Book const & rhs)
{
	if (lhs.getPrice() < rhs.getPrice())
	{
		return true;
	}
	else
	{
		return false;
	}
}