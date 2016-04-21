#pragma once
#include<iostream>
#include<cassert>
#include<queue>
#include"Heap.h"
using namespace std;

template<class T>
struct HaffmanTreeNode
{
	HaffmanTreeNode<T>* _left;
	HaffmanTreeNode<T>* _right;
	HaffmanTreeNode<T>* _parent;
	T _weight;
	
	HaffmanTreeNode(const T& x)
		:_weight(x)
		,_left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class T>
struct NodeCompare
{
	bool operator()(HaffmanTreeNode<T>* h1, HaffmanTreeNode<T>* h2)
	{
		return h1->_weight < h2->_weight;
	}
};

template<class T>
class HaffmanTree
{
	typedef HaffmanTreeNode<T> HTNode;
public:
	HaffmanTree(const T* array,size_t size,const T& x)
	{
		_CreateTree(array, size, x);
	}
	~HaffmanTree()
	{}
	void Print()
	{
		assert(_root);
		HTNode* cur = _root;
		queue<HTNode*> q;
		q.push(cur);
		while (!q.empty())
		{
			cur = q.front();
			cout << cur->_weight << " ";
			q.pop();
			if (NULL!=cur->_left)
			{
				q.push(cur->_left);
			}
			if (NULL!=cur->_right)
			{
				q.push(cur->_right);
			}
		}
		cout << endl;
	}
protected:
	void _CreateTree(const T* array, size_t size, const T& invalid)
	{
		assert(array);
		Heap<HTNode*, NodeCompare<T>> minHp;   //¶Ñ½ÚµãÊÇnode
		for (size_t index = 0; index < size; ++index)
		{
			if (array[index] != invalid)
			{
				HTNode* node = new HTNode(array[index]);
				minHp.Push(node);
			}
		}
		while (minHp.size()>1)
		{
			HTNode* left = minHp.Top();
			minHp.Pop();
			HTNode* right = minHp.Top();
			minHp.Pop();
			HTNode* parent = new HTNode(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;
			
			minHp.Push(parent);
		}
		_root = minHp.Top();
	}
public: 
	HaffmanTreeNode<T>* _root;
};


