#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor
  T& GetData(); //Node Data Getter
  void SetData( const T& data ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  T m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

template <class T>
T& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator= (const Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: If the bool = true, adds to front else adds a new node to the
  //                 end of the lqueue.
  void Push(const T&, bool);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  void TestHeadTail();
  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const Lqueue<U>&);
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement Lqueue here

// Name: Lqueue() (Linked List Queue) - Default Constructor
// Desc: Used to build a new linked queue (as a linked list)
// Preconditions: None
// Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
template<class T>
Lqueue<T>::Lqueue()
{
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}
// Name: ~Lqueue() - Destructor
// Desc: Used to destruct a Lqueue
// Preconditions: There is an existing lqueue with at least one node
// Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template<class T>
Lqueue<T>::~Lqueue()
{
	Clear();
}
// Name: Lqueue (Copy Constructor)
// Preconditions: Creates a copy of existing LQueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
template<class T>
Lqueue<T>::Lqueue(const Lqueue& source)
{
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;

	if (source.m_head != nullptr)
	{
		Node<T> *curr = source.m_head;
		while (curr->GetNext() != nullptr)
		{
			Push(curr->GetData(), 1);
			curr = curr->GetNext();
		}
	}
}
// Name: operator= (Overloaded Assignment Operator)
// Preconditions: Copies an Lqueue into an existing Lqueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
template<class T>
Lqueue<T>& Lqueue<T>::operator= (const Lqueue& source)
{
	Clear();
	Node<T> *temp = source.m_head;
	while (temp != nullptr)
	{
		T toRef = temp->GetData();
		Push(toRef, 1);
		temp = temp->GetNext();
	}
	return *this;
}
// Name: Push
// Preconditions: Takes in data. Creates new node. 
//                Requires a Lqueue
// Postconditions: If the bool = true, adds to front else adds a new node to the
//                 end of the lqueue.
template<class T>
void Lqueue<T>::Push(const T& data, bool place)
{
	Node<T> *temp = new Node<T>(data);

	if (place)
	{
		if (m_size == 0)
		{
			m_head = temp;
			m_tail = temp;
		}
		else
		{
			temp->SetNext(m_head);
			m_head = temp;
		}
	}
	else
	{
		//if bool is false and there is nothin in Lqueue
		if (m_size == 0)
		{
			temp->SetNext(m_head);
			m_head = temp;

			m_tail = temp;
		}
		else
		{
			Node<T> *last = m_tail;
			last->SetNext(temp);
			m_tail = temp;
			temp->SetNext(nullptr);
		}
	}
	m_size++;
}
// Name: Pop
// Preconditions: Lqueue with at least one node. 
// Postconditions: Removes first node in the lqueue, returns data from first node.
template<class T>
T Lqueue<T>::Pop()
{
	Node<T> *temp = m_head->GetNext();
	T data = m_head->GetData();

	delete m_head;

	m_head = temp;
	return data;
}
// Name: Display
// Preconditions: Outputs the lqueue.
// Postconditions: Displays the data in each node of lqueue
template<class T>
void Lqueue<T>::Display()
{
	Node<T> *temp = m_head;

	while (temp->GetNext() != nullptr)
	{
		cout << temp->GetData();
		temp = temp->GetNext();
	}
}
// Name: Front
// Preconditions: Requires a populated lqueue
// Postconditions: Returns whatever data is in front 
template<class T>
T Lqueue<T>::Front()
{
	return m_head->GetData();
}
// Name: IsEmpty
// Preconditions: Requires a lqueue
// Postconditions: Returns if the lqueue is empty.
template<class T>
bool Lqueue<T>::IsEmpty()
{
	if (m_size > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
int Lqueue<T>::GetSize()
{
	return m_size;
}
// Name: Swap(int)
// Preconditions: Requires a lqueue
// Postconditions: Swaps the nodes at the index with the node prior to it.
template<class T>
void Lqueue<T>::Swap(int place)
{
	//Node<T> *temp = m_head;
	//for (int i = 0; i < place; i++) {
	//	temp = temp->GetNext()
	//}
	//if (temp == m_head->GetNext()){
	//	Node<T> *cur = m_head->GetNext();
	//	m_temp->SetNext(m_head);
	//	m_head->SetN
	//}
	Node<T> *curr = m_head;
	Node<T> *next = curr->GetNext();

	for (int i = 0; i <= place; i++)
	{
		if (i == place)
		{
			Node<T> *temp = new Node<T>(curr->GetData());
			curr->SetData(next->GetData());
			next->SetData(temp->GetData());
		}
		else
		{
			curr = next;
			next = next->GetNext();
		}
	}
}
// Name: Clear
// Preconditions: Requires a lqueue
// Postconditions: Removes all nodes in a lqueue
template<class T>
void Lqueue<T>::Clear()
{
	Node<T> *del;
	//Node<T> *delnext = m_head;

	while (del != nullptr)
	{
		del = m_head;
		m_head = m_head->GetNext();
		delete del;
		//del = delNext->GetNext();
		//delnext = delnext->GetNext();
	}
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}
// Name: TestHeadTail() (Optional test function)
// Preconditions: Requires a lqueue
// Postconditions: Returns the value of the head and the tail (used for main below)
template<class T>
void Lqueue<T>::TestHeadTail()
{

}
// Name: operator<< (Overloaded << operator)
// Preconditions: Requires a lqueue
// Postconditions: Returns an ostream with the data from each node on different line
template<class U>
ostream& operator<<(ostream& output, const Lqueue<U>& lqueue)
{
	Node<U> *curr = lqueue.m_head;
	do
	{
		output << curr->GetData() << endl;
		curr = curr->GetNext();
	} while (curr->GetNext() != nullptr);

	return output;
}
//Name: Overloaded [] operator
//Precondition: Existing Lqueue
//Postcondition: Returns object from Lqueue using []
//Overloaded [] operator to pull data from Lqueue
template<class U>
U& Lqueue<U>::operator[] (int x)
{
	int count = 0;
	Node<U> *curr = m_head;

	while (curr->GetNext() != nullptr && count != x)
	{
		curr = curr->GetNext();
		count++;
	}

	return curr->GetData();
}

//****************************************************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue (try valgrind too!)

/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10, 1);
  newLQ1.Push(11, 1);
  newLQ1.Push(12, 1);
  newLQ1.Push(13, 1);
  cout << endl;
  
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);
  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ1;
  cout << endl;

  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1;
  cout << "newLQ2" << endl;
  cout << newLQ2;
  cout << "newLQ3" << endl;
  cout << newLQ3;
  cout << endl;
    
  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;
  
  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;
  
  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  newLQ2.TestHeadTail();
  cout << "Should display head 10 and tail 13" << endl;
  cout << endl;  

  return 0;
}
*/