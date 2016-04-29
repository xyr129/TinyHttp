#include"AVLTree.h"

void TestAVLTree()
{
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> t;
	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		t.Insert(a[i], i);
	}
	t.InOrder();
	cout << "isBlance?" << t.IsBlance() << endl;
}

int main()
{
	TestAVLTree();
	system("pause");
	return 0;
}
