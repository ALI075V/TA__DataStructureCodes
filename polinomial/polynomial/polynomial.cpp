#include<iostream>
#include<math.h>
using namespace std;
class node {
public:
	int node_value;
	double node_pow;
	node* next_node;
	//==============
	node();
	node(int n, double);
	~node();
	int value();
	int Pow();
	void set_value(int value);
	node* next();
};
node::node() {
	node_value = 0;
	node_pow = 0;
	next_node = nullptr;
}
node::node(int n, double p) {
	node_value = n;
	node_pow = p;
	next_node = nullptr;
}
node::~node() {

}
int node::value() {
	return node_value;
}
int node::Pow() {
	return node_pow;
}
void node::set_value(int value) {
	node_value = value;
}
node* node::next() {
	return next_node;
}

//===============================================================

class list_polinomial {
public:
	node* list_head;
	int num;
	//==============
	~list_polinomial();
	list_polinomial();
	node* end();
	int front();
	int powfront();
	node* begin();
	void insert(node* nod);
	void delet(int pow);
	list_polinomial operator+(list_polinomial);
	list_polinomial sum(list_polinomial pol1, list_polinomial pol2);
	int set_value(double value);
	void print();
};
list_polinomial::~list_polinomial() {}
list_polinomial::list_polinomial() {
	list_head = nullptr;
	num = 0;
}
node* list_polinomial::end() {
	return nullptr;
}
int list_polinomial::front() {
	return list_head->node_value;
}
int list_polinomial::powfront() {
	return list_head->node_pow;
}
node* list_polinomial::begin() {
	return list_head;
}
int list_polinomial::set_value(double value) {
	double element = 0, sum = 0;
	for (node* ptr = list_head; ptr != end(); ptr = ptr->next()) {
		element = pow(value, ptr->node_pow);
		sum += (ptr->node_value * element);
	}
	return sum;
}
void list_polinomial::print() {
	for (node* ptr = list_head; ptr != end(); ptr = ptr->next()) {
		cout << ptr->node_value << "x^" << ptr->node_pow;
		if (ptr->next() != nullptr)
			cout << "+";
	}
}
//===================================================
void list_polinomial::insert(node* nod) {
	node* smalnode = new node();
	node* bignode = new node();
	bool smal = false;
	bool big = false;
	if (list_head == nullptr) {
		list_head = nod;
	}
	else {
		for (node* ptr = list_head; ptr != end(); ptr = ptr->next()) {
			if (nod->node_pow == ptr->node_pow) {
				ptr->node_value += nod->node_value;
				break;
			}
			if (nod->node_pow < ptr->node_pow) {
				bignode = ptr;
				big = true;
			}
			if (nod->node_pow > ptr->node_pow) {
				smalnode = ptr;
				smal = true;
			}
		}
		if (smal && big) {
			smalnode->next_node = nod;
			nod->next_node = bignode;
		}
		else {
			if (smal) {
				smalnode->next_node = nod;
			}
			else
				if (big) {
					node* ptr = list_head;
					list_head = nod;
					nod->next_node = ptr;
				}
		}

	}
	num++;
}
void list_polinomial::delet(int Pow) {
	node* befornode = new node();
	for (node* ptr = list_head; ptr != end(); ptr = ptr->next()) {
		if (list_head->node_pow == Pow) {
			list_head = list_head->next();
		}
		else
			if (ptr->node_pow == Pow)
				befornode->next_node = ptr->next_node;
		befornode = ptr;
	}
}
list_polinomial list_polinomial:: operator + (list_polinomial polinomial2) {
	list_polinomial pol2;
	node* smalnode = new node();
	node* bignode = new node();
	node* sum = new node();
	bool smal = false;
	bool big = false;
	bool equal = false;
	node* ptr1 = polinomial2.begin();
	node* ptr = list_head;
	for (node* ptr1 = polinomial2.begin(); ptr1 != end(); ptr1 = ptr1->next()) {
		for (node* ptr = list_head; ptr != end(); ptr = ptr->next()) {
			if (ptr1->node_pow == ptr->node_pow) {
				ptr->node_value += ptr1->node_value;
			}
			if (ptr1->node_pow < ptr->node_pow && !big) {
				bignode = ptr1;
				big = true;
			}
			if (ptr1->node_pow > ptr->node_pow && !smal) {
				smalnode = ptr1;
				smal = true;
			}
		}

		if (smal) {
			insert(smalnode);
			smal = false;
		}
		else
			if (big) {
				insert(bignode);
				big = false;
			}
	}
	while (ptr->next() == nullptr && ptr1->next() == nullptr) {
		if (ptr1->node_pow == ptr->node_pow) {
			ptr->node_value += ptr1->node_value;
		}
		if (ptr1->node_pow < ptr->node_pow && !big) {
			bignode = ptr1;
			big = true;
		}
		if (ptr1->node_pow > ptr->node_pow && !smal) {
			smalnode = ptr1;
			smal = true;
		}
	}

	if (smal) {
		insert(smalnode);
		smal = false;
	}
	else
		if (big) {
			insert(bignode);
			big = false;
		}
	return pol2;
	/*
	if (ptr->node_pow == ptr1->node_pow) {
		sum = ptr;
		sum->node_value = (sum->node_value + ptr1->node_pow);
		pol2.insert(sum);
		if(ptr->next()!=nullptr)
			ptr = ptr->next();
		if(ptr1->next()!=nullptr)
			ptr1 = ptr1->next();
	}
	else
		if (ptr->node_pow > ptr1->node_pow) {
			pol2.insert(ptr1);
			if (ptr1->next() != nullptr)
				ptr1 = ptr1->next();
		}
	else
		if (ptr->node_pow < ptr1->node_pow) {
			pol2.insert(ptr);
			if (ptr->next() != nullptr)
				ptr = ptr->next();
		}
}
return pol2;*/
}
list_polinomial list_polinomial::sum(list_polinomial pol1, list_polinomial pol2) {
	node* ptr1 = pol2.begin();
	node* ptr2 = pol1.begin();
	node* sum = new node();
	bool result = 0;
	list_polinomial sumpol;
	for (; ptr1 != end();ptr1 = ptr1->next() ) {
		for (;ptr2 != end() && result != 1; ptr2 = ptr2->next() ) {
			if (ptr2->Pow() == ptr1->Pow()) {
				result = 1;
				sum->node_value = ptr1->value() + ptr2->value();
				sum->node_pow = ptr1->Pow();
			}
		}
		if (result == 1) {
			sumpol.insert(sum);
		}
		else {
			sumpol.insert(ptr1);
			sumpol.insert(ptr2);
		}
	}
	return sumpol;
	/*while (pol2.num == 0 || pol1.num == 0) {
		if (ptr1->next() == nullptr) {
			while (ptr2 == nullptr) {
				//insert(ptr2);
				ptr2 = ptr2->next();
			}
		}
		if (ptr2->next_node = nullptr) {
			while (ptr1 == nullptr) {
				//insert(ptr1);
				ptr1 = ptr1->next();
			}
		}
		if (ptr2->node_pow == ptr1->node_pow) {
			sum = ptr2;
			sum->node_value = (sum->node_value + ptr1->node_pow);
			//insert(sum);
			ptr2 = ptr2->next();
			ptr1 = ptr1->next();
		}
		else
			if (ptr2->node_pow > ptr1->node_pow) {
				insert(ptr1);
				ptr1 = ptr1->next();
			}
			else
				if (ptr2->node_pow < ptr1->node_pow) {
					insert(ptr2);
					ptr2 = ptr2->next();
				}
	}
*/	
}
//=======================================================

list_polinomial sum(list_polinomial pol1, list_polinomial pol2) {
	node* sum = new node();
	bool result = 0;
	list_polinomial sumpol;
	node* ptr2 = pol1.begin();
	int num1 = pol1.num;
	int num2 = pol2.num;
	for (node* ptr1 = pol2.begin(); num1 != 0 && ptr1!=nullptr; ptr1 = ptr1->next()) {
		for (node* ptr2 = pol1.begin(); num2 != 0 && ptr2 != nullptr && result != 1; ptr2 = ptr2->next()) {
			if (ptr2->Pow() == ptr1->Pow()) {
				result = 1;
				sum->node_value = ptr1->value() + ptr2->value();
				sum->node_pow = ptr1->Pow();
			}
		}
		if (result == 1) {
			sumpol.insert(sum);
		}
		else {
			sumpol.insert(ptr1);
			sumpol.insert(ptr2);
		}
		num1--;
		num2--;
	}
	return sumpol;
}
//======================================================================================
void main() {
	list_polinomial pol;
	list_polinomial pol1;
	list_polinomial pol2;
	int number = 0, number1 = 0, number2 = 0;
	int power = 0, power1 = 0, power2 = 0;
	cout << "set number:";
	cin >> number;
	cout << "set power:";
	cin >> power;
	node* num = new node(number, power);
	pol.insert(num);
	pol.print();
	cout << "\nset number(pol1):";
	cin >> number1;
	cout << "set power(pol1):";
	cin >> power1;
	node* num1 = new node(number1, power1);
	pol1.insert(num1);
	pol1.print();
	/*cout << "\nset number(pol 2):";
	cin >> number2;
	cout << "set power(pol 2):";
	cin >> power2;
	node* num2 = new node(number2, power2);
	pol1.insert(num2);
	cout << "\ndelete one of them (write power):";
	int delpower = 0;
	cin >> delpower;
	pol.delet(delpower);
	pol.print();*/
	pol2 = sum(pol, pol1);
	cout << "\nsum of polinomial:";
	pol2.print();
	/*
	cout << "\nset value:";
	int value = 0;
	cin >> value;
	cout<< pol.set_value(value);*/
}