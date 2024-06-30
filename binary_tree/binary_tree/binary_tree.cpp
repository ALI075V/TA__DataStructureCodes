#include<iostream>
#include<conio.h>
using namespace std;
//=================================== queue ===================================
class Queue {
public:
	int* Element;
	int Size;
	int Capacity;
	Queue(int);
	void Insert(int);
	void pririty();
	int Remove();
	bool isempty();
};
//============================================
bool Queue::isempty() {
	if (Size == 0)
		return true;
	else
		return false;
}
void Queue::pririty() {
	for (int i = 0; i < Size; i++) {
		if (Element[i] < Element[i + 1]) {
			Element[i] = Element[i + 1];
		}
	}
}
void Queue::Insert(int num) {
	if (Size < Capacity) {
		Element[Size] = num;
		Size++;
	}
}
Queue::Queue(int s) {
	Element = new int[5];
	Size = 0;
	Capacity = s;
}
int Queue::Remove() {
	int result = 0;
	if (Size > 0) {
		result = Element[0];
		for (int i = 0; i < Size; i++) {
			Element[i] = Element[i + 1];
		}
		Size--;
	}
	return result;
}
//=================================== stack ===================================
class stack {
public:
	int* elements;
	int sizes;
	int capacitys;
//==========================================
	stack(int);
	void inserts(int);
	int removes();
	bool isempty();
	void print();
};
bool stack::isempty() {
	if (sizes == 0)
		return true;
	else
		return false;
}
stack::stack(int s) {
	elements = new int[s];
	sizes = 0;
	capacitys = s;
}
void stack::inserts(int	num) {
	if (isempty()) {
		elements[sizes] = num;
		sizes++;
	}
	else {
		if (sizes < capacitys) {
			for (int i = 0; i <= sizes+1; i++) {
				elements[i + 1] = elements[i];
			}
			sizes++;
			elements[0] = num;
		}
	}
}
int stack::removes() {
	int result = 0;
	if (sizes > 0) {
		result = elements[0];
		for (int i = 0; i < sizes; i++) {
			elements[i] = elements[i + 1];
			sizes--;
		}
	}
	return result;
}
void stack::print() {
	for (int i = 0; i < 4; i++) {
		cout << removes();
	}
}
//=================================== node binary tree ===================================
class node_binary_tree{
public:
	node_binary_tree* left_child;
	int value_node;
	node_binary_tree* right_sibiling;
//=================================================================
	~node_binary_tree();
	node_binary_tree(int value);
	node_binary_tree();
	int return_value();
	node_binary_tree* left_Child();
	node_binary_tree* right_Sibiling();
	void inorder_traversal();
	void preorder_traversal();
	void postorder_traversal();
	void insert(node_binary_tree* child);
};
node_binary_tree::~node_binary_tree() {
}
node_binary_tree::node_binary_tree(int value) {
	left_child = nullptr;
	right_sibiling = nullptr;
	value_node = value;
}
node_binary_tree::node_binary_tree() {
	left_child = nullptr;
	right_sibiling = nullptr;
	value_node = 0;
}
int node_binary_tree::return_value() {	
	return value_node;
}
node_binary_tree* node_binary_tree::left_Child() {
	return left_child;
}
node_binary_tree* node_binary_tree::right_Sibiling() {
	return right_sibiling;
}
void node_binary_tree::inorder_traversal() {
	if (left_child != nullptr)
		left_child->inorder_traversal();
	cout << value_node;
	if (right_sibiling != nullptr)
		right_sibiling->inorder_traversal();
}
void node_binary_tree::preorder_traversal() {
	cout << value_node;
	if (left_Child() != nullptr)
		left_child->preorder_traversal();
	if (right_Sibiling() != nullptr)
		right_sibiling->preorder_traversal();
}
void node_binary_tree::postorder_traversal() {
	if (left_child != nullptr) {
		left_child->postorder_traversal();
	}
	if (right_sibiling != nullptr) {
		right_sibiling->postorder_traversal();
	}
	cout << value_node ;
}
void node_binary_tree::insert(node_binary_tree* child) {
	if (child->return_value() < return_value()) {
		if (left_Child() == nullptr)
			left_child = child;
		else {
			left_child->insert(child);
		}
	}
	else {
		if (right_sibiling == nullptr) {
			right_sibiling = child;
		}
		else {
			right_sibiling->insert(child);
		}
	}
}
//=================================== binary tree ===================================
class binary_treee {
public:
	node_binary_tree* root;
	int size = 0;
//============================
	~binary_treee();
	binary_treee();
	binary_treee(int value);
	int return_value();
	node_binary_tree* left_child();
	node_binary_tree* right_sibiling();
	void inorder_traversal();
	void preorder_traversal();
	void postorder_traversal();
	void insert(node_binary_tree* child);
};
binary_treee::~binary_treee() {
}
binary_treee::binary_treee() {
	root = new  node_binary_tree();
}
binary_treee::binary_treee(int value) {
	root = new  node_binary_tree(value);
}
int binary_treee::return_value() {
	return root->return_value();
}
node_binary_tree* binary_treee :: left_child() {
	return root->left_Child();
}
node_binary_tree* binary_treee :: right_sibiling() {
	return root->right_Sibiling();
}
void binary_treee::inorder_traversal() {
	root->inorder_traversal();
}
void binary_treee::preorder_traversal() {
	root->preorder_traversal();
}
void binary_treee::postorder_traversal() {
	root->postorder_traversal();
}
void binary_treee ::insert(node_binary_tree* child) {
	if (root->value_node == 0) {
		root = child;
		size++;
	}
	else{
		root->insert(child);
		size++;
	}
}
//=================================== functions ===================================
void BFS (node_binary_tree* root, Queue que, int size) {
	if (que.isempty()) {
		que.Insert(root->return_value());
	}
	if (root->left_Child() != nullptr && root->right_Sibiling() != nullptr && size > 0) {
		cout << que.Remove();
		size--;
	}
	if (root->left_Child() == nullptr && root->right_Sibiling() == nullptr && size>0) {
		cout << que.Remove();
		size--;
	}
	if (root->left_Child() != nullptr && root->right_Sibiling() == nullptr && size > 0) {
		cout << que.Remove();
		size--;
	}
	if (root->left_Child() == nullptr && root->right_Sibiling() != nullptr && size > 0) {
		cout << que.Remove();
		size--;
	}
	if (root->left_Child() != nullptr) {
		que.Insert(root->left_Child()->return_value());
}
	if (root->right_Sibiling() != nullptr) {
		que.Insert(root->right_Sibiling()->return_value());
	}
	if (root->left_Child() != nullptr) {

		BFS(root->left_Child(), que , size);
	}
	if (root->right_Sibiling() != nullptr) {
		BFS(root->right_Sibiling(), que , size);
	}
}
void DFS(node_binary_tree* root, stack Stack, int size){
	bool isnull = 0;
	if (Stack.isempty()) {
		Stack.inserts(root->return_value());
		size--;
	}
	//if (root->left_Child() == nullptr ) {
		
		//isnull = 1;
	//}
	if (root->left_Child() != nullptr && size > 0) {
		cout << Stack.removes();
		Stack.inserts(root->left_Child()->return_value());
		DFS(root->left_Child(), Stack, size);
		if (Stack.sizes == ((Stack.capacitys) - 1))
			cout << Stack.removes();
	}
	//if (root->right_Sibiling() == nullptr && isnull == 0 ) {
		
	//}
	if (root->right_Sibiling() != nullptr && size > 0) {
		cout<<Stack.removes();
		Stack.inserts(root->right_Sibiling()->return_value());
		DFS(root->right_Sibiling(), Stack, size);
		if(Stack.sizes==((Stack.capacitys)-1))
		cout << Stack.removes();
	}
	//if (size == 0) {
		//Stack.print();
	//}
	/*if (Stack.isempty()) {
		Stack.inserts(root->return_value());
	}
	cout<<Stack.removes();
	if (root->left_Child() != nullptr) {
		Stack.inserts(root->left_Child()->return_value());
	}
	if (root->right_Sibiling() != nullptr) {
		Stack.inserts(root->right_Sibiling()->return_value());
	}
	if (root->left_Child() != nullptr) {
		DFS(root->left_Child(), Stack);
	}
	if (root->right_Sibiling() != nullptr) {
		DFS(root->right_Sibiling(), Stack);
	}
	if (root->left_Child() == nullptr && root->right_Sibiling() == nullptr) {
		cout<<Stack.removes();
	}*/
}
/*void add_child(binary_tree* root, binary_tree* child) {
	int condition = 0;
	binary_tree* rptr = root->right_Sibiling();
	binary_tree* lptr = root->left_Child();
	while (condition == 0) {
		if (lptr == nullptr && condition == 0) {
			root->left_child = child;
			condition = 1;
		}
		else
			if (rptr == nullptr && condition == 0) {
				root->right_sibiling = child;
				condition = 1;
			}
		if (lptr != nullptr && condition == 0) {
			if (rptr != nullptr && condition == 0) {
				add_child(lptr,child);
				condition = 1;
			}
			else {
				add_child(rptr, child);
				condition = 1;
			}
		}
	}
	root->size = root->size++;
}
*/
//=================================== main ===================================
int main() {
	int value_root = 0, child_value = 0, child_value1 = 0, child_value2 = 0;
	binary_treee* tree = new binary_treee();
	cout << "set value of root:";
	cin >> value_root;
	node_binary_tree* root = new node_binary_tree(value_root);
	tree->insert(root);
	cout << "set value of child:";
	cin >> child_value;
	node_binary_tree* child = new node_binary_tree(child_value);
	tree->insert(child);
	cout << "set value of child:";
	cin >> child_value1;
	node_binary_tree* child1 = new node_binary_tree(child_value1);
	tree->insert(child1);
	cout << "set value of child:";
	cin >> child_value2;
	node_binary_tree* child2 = new node_binary_tree(child_value2);
	tree->insert(child2);
	/*cout << "preorder_traversal:";
	root->preorder_traversal();
	cout << "\ninorder_traversal:";
	root->inorder_traversal();
	cout << "\npostorder_traversal:";
	root->postorder_traversal();
	cout << "\nBFS:";
	Queue que(tree->size);
	BFS(tree->root , que , tree->size);*/
	cout << "\nDFS:";
	stack Stack(tree->size);
	stack Stack1(4);
	DFS(tree->root, Stack, tree->size);
	//Stack1.print();
	return 0;
}
