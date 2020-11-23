
#include <iomanip>
#include "List.h"

int main() 
{

	TList<int> a;
	a.InsFirst(10);
	a.InsLast(11);

	cout << a << endl;
}

