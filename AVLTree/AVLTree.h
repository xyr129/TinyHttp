#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _bf;

	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _bf(0)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		//1、插入key
		if (NULL == _root)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (key > parent->_key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		bool isRotate = false;
		
		//2、调整平衡因子
		while (parent)
		{
			if (cur == parent->_right)
			{
				parent->_bf++;
			}
			else
			{
				parent->_bf--;
			}
		
			if (parent->_bf == 0) //已经是平衡树
			{
				break;
			}
			if (parent->_bf == -1 || parent->_bf == 1) //继续回溯
			{
				cur = parent;
				parent = cur->_parent;
			}
			else  //2    -2
			{
				isRotate = true;
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)   //  '\'   1、左单旋  
					{
						_RotateL(parent);
					}
					else   //  '>'  2、右左旋
					{
						_RotateRL(parent);
					}
				}
				else
				{
					if (cur->_bf == -1)  //  '/'   3、右单旋
					{
						_RotateR(parent);
					}
					else
					{
						_RotateLR(parent);  //  '<'  4、左右旋
					}
				}
				break;
			}
		}
		
		if (isRotate)
		{
			Node* pParent = parent->_parent;
			if (pParent == NULL)
			{
				_root = parent;
			}
			else
			{
				if (pParent->_key < parent->_key)
				{
					pParent->_right = parent;
				}
				else
				{
					pParent->_left = parent;
				}
			}
		}

		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	bool IsBlance()
	{
		return _Blance(_root);
	}
protected:
	void _RotateL(Node*& parent)   ///    '\'   =>   '/\'
	{
		Node* subRight = parent->_right;
		Node* subRightL = subRight->_left;
		parent->_right = subRightL;
		subRight->_left = parent;

		if (subRightL != NULL)
		{
			subRightL->_parent = parent;
		}

		subRight->_parent = parent->_parent;
		parent->_parent = subRight;


		subRight->_bf = 0;
		parent->_bf = 0;

		parent = subRight;
	}

	void _RotateR(Node*& parent)    //  '/'  =>  '/\'
	{
		Node* subLeft = parent->_left;
		Node* subLeftR = subLeft->_right;
		parent->_left = subLeftR;
		if (subLeftR)
		{
			subLeftR->_parent = parent;
		}
		
		subLeft->_right = parent;
		subLeft->_parent = parent->_parent;
		parent->_parent = subLeft;

		subLeft->_bf = 0;
		parent->_bf = 0;

		parent = subLeft;
	}

	void _RotateLR(Node*& parent)   //  '<'  =>   '/'  =>   '/\'
	{
		Node* subLeft = parent->_left;
		Node* subLeftR = subLeft->_right;
		subLeft->_right = subLeftR->_left;
		if (subLeft->_left)
		{
			subLeftR->_left->_parent = subLeft;
		}
		subLeftR->_left = subLeft;
		subLeftR->_parent = subLeft->_parent;
		subLeft->_parent = subLeftR;

		if (subLeftR->_bf == 0 || subLeftR->_bf == -1)
		{
			subLeft->_bf = 0;
		}
		else
		{
			subLeft->_bf = -1;
		}
		//右旋
		parent->_left = subLeftR->_right;
		if (subLeftR->_right)
		{
			subLeftR->_right->_parent = parent;
		}

		subLeftR->_right = parent;
		subLeftR->_parent = parent->_parent;
		parent->_parent = subLeftR;

		if (subLeftR->_bf == 0 || subLeftR->_bf == 1)
		{
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = 1;
		}

		subLeftR->_bf = 0;
		parent = subLeftR;

	}

	void _RotateRL(Node*& parent)   //  '>'  =>   '\'   =>  '/\'
	{
		Node* subRight = parent->_right;
		Node* subRightL = subRight->_left;
		subRight->_left = subRightL->_right;
		if (subRightL->_right)
		{
			subRightL->_parent = subRight;
		}

		subRightL->_right = subRight;
		subRightL->_parent = subRight->_parent;
		subRight->_parent = subRightL;

		if (subRightL->_bf == 0 || subRightL->_bf == 1)
		{
			subRight->_bf = 0;
		}
		else
		{
			subRight->_bf = 1;
		}

		parent->_right = subRightL->_left;
		if (subRightL->_left)
		{
			subRightL->_left->_parent = parent;
		}

		subRightL->_left = parent;
		subRightL->_parent = parent->_parent;
		parent->_parent = subRightL;

		if (subRightL->_bf == 0 || subRightL->_bf == -1)
		{
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = -1;
		}

		subRightL->_bf = 0;
		parent = subRightL;
	}

	void _InOrder(Node* root)
	{
		if (NULL == root)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	int _Height(Node* root)
	{
		if (NULL == root)
		{
			return 0;
		}
		int left = _Height(root->_left) + 1;
		int right = _Height(root->_right) + 1;
		return left > right ? left : right;
	}
	bool _Blance(Node* root)
	{
		if (NULL == root)
		{
			return true;
		}
		
		int bf = _Height(root->_right) - _Height(root->_left);
		if (abs(bf) > 1 || bf != root->_bf)
		{
			cout << "平衡因子有问题：" << root->_key << endl;
			return false;
		}
	
		return _Blance(root->_left) && _Blance(root->_right);

	}
protected:
	AVLTreeNode<K, V>* _root;
};

