#include "List.h"

int main() 
{

	TList<int> a;
	a.InsFirst(10);
	a.InsLast(11);

	cout << a << endl;

	TList<int> b(a);
	cout << b << endl;

	TList<int> c;
	c.InsLast(1);
	c.InsLast(2);
	c.InsLast(3);
	c.InsLast(1);
	c.InsLast(2);

	c.cleanse();

	TListIterator<int> i = c.Begin();

	for (int j = 0; j < c.GetCount(); j++)
	{
		cout << i.GetData() << " ";
		if(i.CanGoFwd())
			i++;
	}
	cout << endl;
	c.reverse();
	cout << c << endl;

}

