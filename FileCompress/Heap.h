#include<iostream>
#include<cassert>
#include<vector>
using namespace std;

template<class T>
struct Less
{
	bool operator()(const T& t1,const T& t2)
	{
		return t1 < t2;
	}
};
template<class T>
struct Great
{
	bool operator()(const T& t1, const T& t2)
	{
		return t1 > t2;
	}
};

template<class T,class Compare=Less<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(const T* array,size_t size)
	{
		assert(array);
		for (size_t i = 0; i < size; ++i)
		{
			_array.push_back(array[i]);
		}
		//从第一个非叶子节点开始向下调整
		for (int index =(size-2)/2; index>=0; --index)
		{
			AdjustDown(index);
		}
	}
	T& Top()
	{
		assert(_array.size());
		return _array[0];
	}
	void Push(const T& x)
	{
		_array.push_back(x);
		AdjustUp(_array.size() - 1);
	}
	void Pop()
	{
		assert(_array.size());
		swap(_array[0], _array[_array.size() - 1]);
		_array.pop_back();
		AdjustDown(0);
	}
	bool Empty()
	{
		return _array.empty();
	}
	size_t size()
	{
		return _array.size();
	}

	void PrintHeap()
	{
		for (size_t i = 0; i < _array.size(); ++i)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}
protected:
	void AdjustDown(size_t root)
	{
		Compare com;
		size_t size = _array.size();
		size_t child = 2 * root + 1;
		while (child < size)
		{
			if (child + 1 < size && com(_array[child + 1],_array[child]))
			{
				child++;
			}
			if (com(_array[child], _array[root]))
			{
				swap(_array[child], _array[root]);
				root = child;
				child = 2 * root + 1;
			}
			else
			{
				break;
			}
		}
	}
	void AdjustUp(int child)
	{
		Compare com;
		int root = (child - 1) / 2;
		while (root>=0)
		{
			if (com(_array[child], _array[root]))
			{
				swap(_array[child], _array[root]);
				child = root;
				root = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
protected:
	vector<T> _array;
};