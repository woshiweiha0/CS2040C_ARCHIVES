#include "LinkedList.h"
#include <stdexcept>
#include <sstream>

// Returns the value at head
int List::head() {
	if (m_head == nullptr) {
		throw std::out_of_range("List is empty");
	}
	return m_head->element;
}

// Checks whether the container is empty
bool List::empty() const {
	return m_size == 0;
}

// Returns the number of elements
size_t List::size() const {
	return m_size;
}

// Inserts an element to the head
void List::push_head(int element) {
	Node* Newnode = new Node(element);
	Newnode->next = m_head;
	m_head = Newnode;
	m_size += 1;
}

// Removes the head element
int List::pop_head() {
	if (m_size > 0) {
		Node* temp = m_head;
		m_head = m_head->next;
		int headvalue = temp->element;
		delete temp;
		m_size -= 1;
		return headvalue;
	}
	else {
		throw std::out_of_range("List is empty");
	}
}

// Checks whether the container contains the specified element
bool List::contains(int element) const {
	Node* ptr = m_head;
	while (ptr != nullptr) {
		if (ptr->element == element) {
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

// Returns a std::string equivalent of the container
std::string List::to_string() const {
	if (m_size == 0) {
		return "{}";
	}
	std::ostringstream container;
	container << "{";
	Node* ptr = m_head;
	while (ptr != nullptr) {
		container << ptr->element;
		if (ptr->next != nullptr) {
			container << ", ";
		}
		ptr = ptr->next;
	}
	container << "}";
	return container.str();
}

/*
void List::insertTail(int element) {
 Node* ptr = m_head;
 for (long i = 0; i < m_size; i++) {  // by me: use while (ptr->next != nullptr);
  ptr = ptr->next;
 }
 Node* Newnode = new Node(element); // Allocates a new node for the element, with next being nullptr
 ptr->next = Newnode; // Points the previous tail to the new tail instead of nullptr
 m_size++;
}

int List::returnTail() {
 if (m_size == 0) {
  throw std::out_of_range("List is empty");
 }
 Node* ptr = m_head;
 for (long i = 0; i < m_size; i++) {
  ptr = ptr->next;
 }
 return ptr->element;
}
*/
