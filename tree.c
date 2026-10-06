#include <stdio.h>
#include <stdlib.h>
#include "tree.h" 

void init(tree_t *ptr_tree)
{
	ptr_tree->root_ = -1;
	init_stack(&ptr_tree->s);
	// mark all locations as feww
	for(int i = MAXSIZE - 1; i >= 0; --i)
	{
		push(&ptr_tree->s, i);
	}
}

int insert_recursive(node_t elem[], int root, int temp)
{
	if(root == -1)
	{
		root = temp;
	}
	else if(elem[root].key_ > elem[temp].key_)
	{
		elem[root].left_ = insert_recursive(elem, elem[root].left_, temp);
	}
	else
	{
		elem[root].right_ = insert_recursive(elem, elem[root].right_, temp);
	}
	return root;
}
void insert(tree_t *ptr_tree, int key)
{
	// needs to be changed 
	// count_ should be the next free allocation
	// pop the stack to get the location
	int temp = pop(&ptr_tree->s);
	
	
	ptr_tree->elem_[temp].key_ = key;
	ptr_tree->elem_[temp].left_ = ptr_tree->elem_[temp].right_ = -1;
	ptr_tree->root_ = insert_recursive(ptr_tree->elem_, ptr_tree->root_, temp);
}

void disp_recursive(node_t elem[], int temp)
{
		if(temp != -1)
		{
			disp_recursive(elem, elem[temp].left_);
			printf("%d ", elem[temp].key_);
			disp_recursive(elem, elem[temp].right_);
		}
		
}


void disp(tree_t *ptr_tree)
{
	disp_recursive(ptr_tree->elem_, ptr_tree->root_); 
	printf("\n\n");
}

// needs to be totally changed to array implementation
// replace free by push to the stack
#if 0
node_t* inorder_successor(node_t* root)
{
	node_t* temp = root;
	while(temp->left_ != NULL)
		temp = temp->left_;
	return temp;
}
#endif
int inorder_successor(node_t elem_[], int root)
{
	int temp = root;
	while(elem_[temp].left_ != -1)
		temp = elem_[temp].left_;
	return temp;
}

int delete_key_recursive(tree_t* ptr_tree,
		node_t elem[], int root, int key)
{
	// locate the key
	// 1. empty tree 
	if(root == -1)
	{
		return -1;
	}
	// 2. in left subtree?
	else if(key < elem[root].key_)
	{
		elem[root].left_ = delete_key_recursive
			(ptr_tree, elem, elem[root].left_, key);
	}
	// 3. in right subtree?
	else if(key > elem[root].key_)
	{
		elem[root].right_ = delete_key_recursive
			(ptr_tree, elem, elem[root].right_, key);
	}
	// 4. key found
	else 
	{
		// 1. leaf 
		if(elem[root].left_ == -1 && 
			elem[root].right_ == -1)
		{
			push(&ptr_tree->s, root);
			return -1;
		}
		// 2. no left subtree 
		else if(elem[root].left_ == -1)
		{
			int temp = elem[root].right_;
			push(&ptr_tree->s, root);
			return temp;
		}
		// 3. no right subtree
		else if(elem[root].right_ == -1)
		{
			int temp = elem[root].left_;
			push(&ptr_tree->s, root);
			return temp;
		}
		// 4. has both left and right subtrees
		else 
		{
			// find the inorder successor
			int temp = inorder_successor(elem, elem[root].right_);
			// replace root key 
			elem[root].key_ = elem[temp].key_;
			// delete temp->key_ in the right subtree 
			elem[root].right_ = 
				delete_key_recursive(ptr_tree, elem, 
						elem[root].right_, elem[temp].key_);
			return root;
		}
		
	}
	return root;
}


void delete_key(tree_t *ptr_tree, int key)
{
	ptr_tree->root_ = delete_key_recursive(
		ptr_tree, ptr_tree->elem_, ptr_tree->root_, key);
}


