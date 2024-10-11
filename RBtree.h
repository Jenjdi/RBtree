#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;
enum Color
{
	BLACK,
	RED
};
template<typename T>
struct RBTreeNode
{
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;
	Color _col;
	T _val;
	RBTreeNode(T val)
		:_left(nullptr),
		_right(nullptr),
		_parent(nullptr),
		_col(RED),
		_val(val) {};
};
template<typename key>
class RBTree
{
public:
	typedef RBTreeNode<key> node;
	bool insert(const key& k)
	{
		if (_root == nullptr)
		{
			_root = new node(k);
			_root->_col = BLACK;
			return true;
		}
		node* parent = nullptr;
		node* cur = _root;
		while (cur)
		{
			if (cur->_val > k)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_val < k)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		
		cur = new node(k);
		cur->_col = RED;
		if (cur->_val < parent->_val)
		{
			parent->_left = cur;
			
		}
		else
		{
			parent->_right = cur;
			
		}
		cur->_parent = parent;

		while (parent&&parent->_col == RED)
		{
			node* grand = parent->_parent;
			if (parent == grand->_left)
			{
				node* uncle = grand->_right;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grand->_col = RED;
					cur = grand;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						rightrotate(grand);
						parent->_col = BLACK;
						grand->_col = RED;
					}
					else
					{
						leftrotate(parent);
						rightrotate(grand);
						cur->_col = BLACK;
						grand->_col = RED;
					}
					break;
				}
			}
			else
			{
				node* uncle = grand->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grand->_col = RED;
					cur = grand;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						leftrotate(grand);
						parent->_col = BLACK;
						grand->_col = RED;
					}
					else
					{
						rightrotate(parent);
						leftrotate(grand);
						cur->_col = BLACK;
						grand->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	void leftrotate(node* parent)
	{
		node* subR = parent->_right;
		node* subRL = subR->_left;
		parent->_left = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		node* pparent = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;
		if (parent == _root)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (subR == pparent->_left)
			{
				pparent->_left = subR;
			}
			else
			{
				pparent->_parent = subR;
			}
			subR->_parent = pparent;
		}
		
	}
	void rightrotate(node* parent)
	{
		node* subL = parent->_left;
		node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		node* pparent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		if (parent == _root)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (subL == pparent->_left)
			{
				pparent->_left = subL;
			}
			else
			{
				pparent->_right = subL;
			}
			subL->_parent = pparent;
		}
		
	}
	void inorder()
	{
		_inorder(_root);
	}
private:
	node* _root = nullptr;
	void _inorder(node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_inorder(root->_left);
		cout << root->_val;
		_inorder(root->_right);
	}
};

