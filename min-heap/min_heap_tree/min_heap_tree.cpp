#include<iostream>
using namespace std;
class binary_tree_node {
	public:
		int data;
		int childs;
		binary_tree_node* parent;
		binary_tree_node* left_child;
		binary_tree_node* right_child;
//======================function============================
		~binary_tree_node();
		binary_tree_node(int data_node);
		binary_tree_node();
		binary_tree_node* insert(binary_tree_node* child, int& lhight, int& rhight, bool& ischange, bool& ischek);
		binary_tree_node* del();
};
	binary_tree_node ::~binary_tree_node() {

	}
	binary_tree_node::binary_tree_node(int data_node) {
		this->data = data_node;
		this->childs = 0;
		this->parent = nullptr;
		this->left_child = nullptr;
		this->right_child = nullptr;

	}
	binary_tree_node::binary_tree_node() {
		this->data = 0;
		this->childs = 0;
		this->parent = nullptr;
		this->left_child = nullptr;
		this->right_child = nullptr;
	}
	binary_tree_node* binary_tree_node::insert(binary_tree_node* child, int& lhight, int& rhight, bool& ischange, bool& ischek) {
		bool isleft = 0;
		bool isright = 0;
		if (ischek == false) {
			if (lhight == rhight) {
				if (left_child == nullptr) {
					left_child = child;
					left_child->parent = this;
					childs++;
					lhight++;
					ischange = 1;
					return left_child;
				}
				else
					if (right_child == nullptr) {
						right_child = child;
						right_child->parent = this;
						childs++;
						rhight++;
						ischange = 1;
						isright = 1;
						return right_child;
					}
					else {
						if (left_child->childs < 2) {
							left_child->left_child = child;
							child->parent = left_child;
							lhight++;
							left_child->childs++;
							if (lhight - rhight > 1) {
								lhight--;
							}
							return child;
						}
						else {
							right_child->insert(child, lhight, rhight, ischange , ischek);
						}
					}
			}
			else
				if (lhight > rhight) {
					if (left_child == nullptr) {
						this->left_child = child;
						child->parent = this;
						lhight++;
						childs++;
						if (lhight - rhight > 1)
							lhight--;
						isleft = 1;
						return child;
					}
					if (right_child == nullptr && left_child != nullptr) {
						right_child = child;
						right_child->parent = this;
						childs++;
						rhight++;
						ischange = 1;
						isright = 1;
						return right_child;
					}
					if (this->left_child->childs < 2 && this->right_child != nullptr) {
						left_child->right_child = child;
						child->parent = left_child;
						lhight++;
						left_child->childs++;
						if (lhight - rhight > 1)
							lhight--;
						isleft = 1;
						return child;
					}
					if (isleft == 0)
						right_child->insert(child, lhight, rhight, ischange , ischek);
				}
		}
		else {
			return child;
		}
	}
	binary_tree_node* binary_tree_node::del() {
		if (this->left_child->childs == 0) {
			return this->left_child;
			this->left_child = nullptr;
		}
		if (this->left_child == nullptr) {
			return this->right_child;
			this->right_child = nullptr;
		}
		if (this->right_child->childs > 0) 
			right_child->del();
	}
	
//======================function============================
class binary_tree {
	public:
		binary_tree_node* root;
		int lhight;
		int rhight;
		int lptr;
		int rptr;
//==========================================================
		~binary_tree();
		binary_tree();
		binary_tree(binary_tree_node* value);
		bool isempty();
		void insert(binary_tree_node* child, bool& ischang, bool& ischek);
		int delet();
		
};
	binary_tree :: ~binary_tree() {
	}
	binary_tree::binary_tree() {
		this->root = new binary_tree_node();
		this->lhight = 0;
		this->rhight = 0;
		this->lptr = root->data;
		this->rptr = root->data;
	}
	binary_tree::binary_tree(binary_tree_node* value) {
		this->root = value;
		this->lhight = 0;
		this->rhight = 0;
		this->lptr =root->data;
		this->rptr = root->data;
	}
	bool binary_tree::isempty() {
		if (root == nullptr)
			return 1;
		else
			return 0;
	}
	void binary_tree::insert(binary_tree_node* child , bool& ischang , bool& ischek) {
		bool isroot = false;
		bool isbig = false;
		if (isempty()) {
			root = child;
			bool isroot = true;
		}
		else {
				binary_tree_node* ptr1 = root->insert(child, lhight, rhight, ischang , ischek);
				if (ischang == 1 && isroot == false || ischang == false) {
					binary_tree_node* ptr = ptr1->parent;
					if (ptr1->data < ptr->data) {
						int tmp = ptr->data;
						ptr->data = ptr1->data;
						ptr1->data = tmp;
						isbig = true;

					}
					if (ptr1->parent->data == root->data) {
						root = ptr;
						isroot = 1;
						isbig = 0;
						return;
					}
					if (isbig == true) {
						ischek = 1;
						insert(ptr, ischang, ischek);
					}
				
			    }
			
		}
	}
	int binary_tree::delet() {
		if (isempty()) {
			return 0;
		}
		else {
			binary_tree_node* head = new binary_tree_node();
			int result = root->data;
			head=root->del();
			root->data = head->data;
			return result;
		}
	}
//===================================================================
	int main() {
		bool change = 0;
		bool ischeck = 0;
		binary_tree_node* child = new binary_tree_node(1);
		binary_tree root(child);
		binary_tree_node* child1 = new binary_tree_node(3);
		ischeck = 0;
		root.insert(child1,change , ischeck);
		binary_tree_node* child2 = new binary_tree_node(8);
		ischeck = 0;
		root.insert(child2, change, ischeck);
		binary_tree_node* child3 = new binary_tree_node(5);
		ischeck = 0;
		root.insert(child3, change, ischeck);
		binary_tree_node* child4 = new binary_tree_node(12);
		ischeck = 0;
		root.insert(child4, change, ischeck);
		binary_tree_node* child5 = new binary_tree_node(9);
		ischeck = 0;
		root.insert(child5, change, ischeck);
		binary_tree_node* child6 = new binary_tree_node(10);
		ischeck = 0;
		root.insert(child6, change, ischeck);
		root.delet();
		return 0;
	}