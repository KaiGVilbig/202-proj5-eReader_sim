#include "EReader.h"

//Name: EReader - Default Constructor
  //Precondition: None
  //Postcondition: Creates a new EReader
EReader::EReader()
{
	
}
//Name: EReader - Overloaded Constructor
//Precondition: None
//Postcondition: Creates a new EReader and passes the book filename
EReader::EReader(string filename)
{
	LoadCatalog(filename);
}
//Name: ~EReader - Destructor
//Precondition: None
//Postcondition: Creates a new EReader
EReader::~EReader()
{
	for (unsigned int i = 0; i < m_bookCatalog.size(); i++)
	{
		Book* tmp = m_bookCatalog[i];
		delete tmp;
	}
}
//Name: LoadCatalog(string filename)
//Precondition: Requires filename
//Postcondition: Loads the file into the m_bookCatalog (as books)
void EReader::LoadCatalog(string filename)
{
	fstream inputStream;
	inputStream.open(filename);

	do
	{
		string name, author, rank, price;
		int irank;
		double dprice;

		getline(inputStream, name, ',');
		getline(inputStream, author, ',');
		getline(inputStream, rank, ',');
		getline(inputStream, price);

		irank = stoi(rank);
		dprice = stod(price);

		if (inputStream.peek() == '\n')
		{
			inputStream.ignore();
		}
		m_bookCatalog.push_back(new Book(name, author, irank, dprice));

	} while (!inputStream.eof());

	inputStream.close();
}
//Name: MainMenu
//Precondition: None
//Postcondition: Manages the application and the menu
void EReader::MainMenu()
{
	int choice = 0;
	int catalogSize = m_bookCatalog.size();
	cout << "Catalog populated with " << catalogSize << " books\n\n";

	while (choice != 5)
	{
		cout << "What would you like to do?\n";
		cout << "1. Display All Books\n";
		cout << "2. Add Book to Readlist\n";
		cout << "3. Display Readlist\n";
		cout << "4. Sort Readlist by Price\n";
		cout << "5. Quit\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << endl;
			for (unsigned int i = 0; i < m_bookCatalog.size(); i++)
			{
				cout << i + 1 << "\t" << *m_bookCatalog[i] << endl;
			}
			cout << endl;
			break;
		case 2:
			AddBook();
			break;
		case 3:
			DisplayReadlist();
			break;
		case 4:
			SortReadlist();
			break;
		case !5:
			cout << "Please chose 1 - 5\n";
			break;
		}
	}

	cout << "Thank you for using the UMBC E-Reader\n\n";
}
//Name: DisplayBooks
//Precondition: Displays all 150 books
//Postcondition: Lists all books (numbered)
void EReader::DisplayBooks()
{
	cout << endl;
	for (unsigned int i = 0; i < m_bookCatalog.size(); i++)
	{
		cout << i + 1 << "\t" << left << setw(45) << m_bookCatalog[i]->getTitle() << left << setw(25) << m_bookCatalog[i]->getAuthor();
		cout << " (" << m_bookCatalog[i]->getPrice() << ")\n";
	}
	cout << endl;
}
//Name: AddBook
//Precondition: m_bookCatalog is populated
//Postcondition: Displays the current list and adds a book
//               to the m_readList
void EReader::AddBook()
{
	int choice;
	int catalogSize = m_bookCatalog.size();
	cout << "Choose the book you'd like to add to your reading list\n";

	DisplayBooks();

	do
	{
		cout << "Enter the number of the book you'd like to add: ";
		cin >> choice;
		cout << endl;
	} while (choice < 0 || choice > catalogSize);

	m_readList.Push(*m_bookCatalog[choice - 1], true);
}
//Name: DisplayReadlist
//Precondition: None (can be empty)
//Postcondition: Displays the readlist
void EReader::DisplayReadlist()
{
	cout << endl;
	for (int i = 0; i < m_readList.GetSize(); i++)
	{
		cout << i + 1 << "\t" << left << setw(45) << m_readList[i].getTitle() << left << setw(25) << m_readList[i].getAuthor();
		cout << " (" << m_readList[i].getPrice() << ")\n";
	}
	cout << endl;
}
//Name: SortReadlist()
//Precondition: Requires Readlist
//Postcondition: Uses the overloaded < operator in Book to sort
//               the prices from high to low in the m_readList
void EReader::SortReadlist()
{
	cout << endl;
	for (int i = 0; i < m_readList.GetSize() - 1; i++)
	{
		if (m_readList[i] < m_readList[i + 1])
		{
			m_readList.Swap(i);
		}
	}
}