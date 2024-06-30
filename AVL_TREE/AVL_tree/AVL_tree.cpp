	#include<iostream>
	#include<conio.h>
	using namespace std;

//===================================================N O D E===============================================================


	class AVL_node_tree {
	public:
		int value;
		AVL_node_tree* left_child;
		AVL_node_tree* right_child;
		int height;
		~AVL_node_tree();
		AVL_node_tree(int value);
	};

	AVL_node_tree::~AVL_node_tree() {

	}

	AVL_node_tree::AVL_node_tree(int node_value) {
		this->value = node_value;
		this->left_child = nullptr;
		this->right_child = nullptr;
		this->height = 1;
	}

//====================================================F U N C T I O N==============================================================

	int height(AVL_node_tree* node) {
		if (node == nullptr) {
			return 0;
		}                                         // return hight of node
		else {
			return node->height;
		}
	}

//==================================================================================================================

	int max(int x, int y) {
		return (x > y) ? x : y;                 // find max of two int
	}


	AVL_node_tree* new_node(int value) {
		AVL_node_tree* node = new AVL_node_tree(value);      // returnthe new node
		return node;
	}

//==================================================================================================================

	AVL_node_tree* right_rotate(AVL_node_tree* ynode) {

		AVL_node_tree* xnode = ynode->left_child;

		AVL_node_tree* T2 = xnode->right_child;                                   // rotate right child

		ynode->height = max(height(ynode->left_child), height((ynode->right_child + 1)));

		xnode->height = max(height(xnode->left_child), height((xnode->right_child + 1)));
		
		return xnode;
	}

//==================================================================================================================
	
	AVL_node_tree* left_rotate(AVL_node_tree* xnode) {

		AVL_node_tree* ynode = xnode->right_child;

		AVL_node_tree* T2 = ynode->left_child;                                          // rotate right child

		xnode->height = max(height(xnode->left_child), height((xnode->right_child + 1)));

		ynode->height = max(height(ynode->left_child), height((ynode->right_child + 1)));

		return ynode;
	}

//==================================================================================================================
	
	int get_balance(AVL_node_tree* node) {
		if (node == nullptr) {
			return 0;
		}                                          // get balance of left and right child
		else {
			return (height(node->left_child) - height(node->right_child));
		}
	}

//==================================================================================================================

	AVL_node_tree* main_value_node(AVL_node_tree* node) {

		AVL_node_tree* currect = node;

		while (currect->left_child != nullptr) {                      //return leftest child

			currect = currect->left_child;
		}

		return currect;
	}

//==================================================================================================================
	AVL_node_tree* insert(AVL_node_tree* node, int value) {  // insert !

		//find the loc of value

		if (node == nullptr) {

			return (new AVL_node_tree(value));
		}

		if (value < node->value) {
			node->left_child = insert(node->left_child, value);
		}

		else
			if (value > node->value) {
				node->right_child = insert(node->right_child, value);
			}

		else
			return node;
		//get balace and hight

		node->height = 1 + max(height(node->left_child), height(node->right_child));

		int balance = get_balance(node);

		// find loc of element which insert and find side of rotate

		if (balance > 1 && value < node->right_child->value) {

			return right_rotate(node);
		}
		if (balance<-1 && value > node->left_child->value) {

			return left_rotate(node);
		}

		if (balance > 1 && value > node->right_child->value) {

			node->left_child = left_rotate(node->left_child);

			return right_rotate(node);
		}

		if (balance<-1 && value<node->left_child->value) {

			node->right_child = right_rotate(node->right_child);

			return left_rotate(node);
		}

		return node;
	}

//==================================================================================================================
	
	AVL_node_tree* delete_node(AVL_node_tree* root, int value) {    // delete !

		//find node to delete it

		if (root == nullptr) {
			return root;
		}

		if (value < root->value) {

			root->left_child = delete_node(root->left_child, value);

		}

		else if (value > root->value) {

			root->right_child = delete_node(root->right_child, value);

		}

		// finaly find it 

		else {

			if (root->left_child == nullptr || root->right_child == nullptr) {  // if dont have child

				AVL_node_tree* tmp = root->left_child ? root->left_child : root->right_child;
				 
				if (tmp == nullptr) {                                       
					tmp = root;
					root = nullptr;
				}

				else
					*root = *tmp;
				free(tmp);

			}

			else {
				// if have child
				AVL_node_tree* tmp = main_value_node(root->right_child);

				root->value = tmp->value;

				root->right_child = delete_node(root->right_child, tmp->value);

			}
		}

		if (root == nullptr) {

			return root;

		}
		// set balance and hight of root 
		root->height = 1 + max(height(root->left_child), height(root->right_child));

		int balance = get_balance(root);

		// find loc of element which insert and find side of rotate


		if (balance > 1 && get_balance(root->left_child) >= 0) {

			return right_rotate(root);

		}

		if (balance > 1 && get_balance(root->left_child) < 0) {

			root->left_child = left_rotate(root->left_child);

			return right_rotate(root);
		}

		if (balance < -1 && get_balance(root->right_child) <= 0) {

			return left_rotate(root);

		}

		if (balance < -1 && get_balance(root->right_child) > 0) {

			root->right_child = right_rotate(root->right_child);

			return left_rotate(root);

		}

		return root;
	}

//==================================================================================================================

	void pre_order(AVL_node_tree* root) {

		if (root != nullptr) {

			cout << root->value << " ";    // print preeorder of tree
			pre_order(root->left_child);
			pre_order(root->right_child);

		}
	}

//==================================================A V L================================================================

	class AVL_tree {
	public:
		AVL_node_tree* root;
		~AVL_tree();
		AVL_tree(AVL_node_tree* node);
	};

	AVL_tree::~AVL_tree() {

	}

	AVL_tree::AVL_tree(AVL_node_tree* node) {
		this->root = node;
	}

//==================================================M A I N================================================================

	int main() {
		AVL_node_tree* root = NULL;

		/* Constructing tree given in
		the above figure */
		root = insert(root, 9);
		root = insert(root, 5);
		root = insert(root, 10);
		root = insert(root, 0);
		root = insert(root, 6);
		root = insert(root, 11);
		root = insert(root, -1);
		root = insert(root, 1);
		root = insert(root, 2);

		/* The constructed AVL Tree would be
					9
				  /   \
				1      10
			  /   \      \
			 0     5      11
			/    /   \
		  -1    2     6



		*/

		cout << "Preorder traversal of the "
			"constructed AVL tree is \n";
		pre_order(root);

		root = delete_node(root, 10);

		/* The AVL Tree after deletion of 10
		 
		 
		 
				 1
			   /   \
			  0     9
			 /    /   \
			-1   5     11
			   /   \
			  2     6



		*/

		cout << "\nPreorder traversal after"
			<< " deletion of 10 \n";
		pre_order(root);

		return 0;
	}

//==================================================E N D==================================================