#include <iostream>

using namespace std;

template <class T>
class TListElem
{
protected:
	T data;
	TListElem* next;
	TListElem* prev;
public:
	TListElem(T _data);
	~TListElem();

	T GetData();
	TListElem* GetNext();
	TListElem* GetPrev();

	void SetData(T _data);
	void SetNext(TListElem* _next);
	void SetPrev(TListElem* _prev);
	
	template <class T1>
	friend ostream& operator<< (ostream& ostr, const TListElem<T1>& A);
	template <class T1>
	friend istream& operator >> (istream& istr, TListElem<T1>& A);

	template<class T1>
	friend class TList;
};

template<class T2>
class TListIterator
{
protected:
	TList<T2>& link;
	TListElem<T2>* current;
public:
	TListIterator(TList<T2>& _list, TListElem<T2>* _c) : link(_list), current(_c) {}
	TListIterator(TListIterator<T2>& _v) : link(_v.link), current(_v.current) {}
	~TListIterator();

	bool CanGoFwd();
	bool CanGoBck();
	void GoFwd();
	void GoBck();

	bool operator==(const TListIterator<T2>& _v);
	TListIterator<T2> operator++(int);
	TListIterator<T2> operator--(int);

	TListIterator<T2>& operator=(const TListIterator<T2>& _v);

	T2 GetData();
};

template <class T>
class TList
{
protected:
	TListElem<T>* root;
	TListElem<T>* end;
	int count;
public:
	TList();
	TList(TList<T>& _v);
	~TList();

	TList<T>& operator =(TList<T>& _v);

	TListIterator<T> Begin();
	TListIterator<T> End();

	void InsFirst(T d);
	void InsLast(T d);
	void Ins(TListElem<T>* e, T d);

	TListElem<T>* GetFirst();
	TListElem<T>* GetLast();

	void DelFirst();
	void DelLast();
	void Del(TListElem<T>* e);

	bool IsEmpty(void) const;
	//bool IsFull(void) const;

	template <class T1>
	friend ostream& operator<< (ostream& ostr, const TList<T1> &A);
	template <class T1>
	friend istream& operator >> (istream& istr, TList<T1> &A);

	int GetCount();

	//extra
	template<class T2>
	friend class TListIterator;
	void reverse();
	void cleanse();
};

template<class T1>
inline ostream& operator<<(ostream& ostr, const TListElem<T1>& A)
{
	ostr << A.data;
	return ostr;
}

template<class T1>
inline istream& operator >> (istream& istr, TListElem<T1>& A)
{
	istr >> A.data;
	return istr;
}

template <class T1>
ostream& operator<< (ostream& ostr, const TList<T1> &A) 
{
	TListElem<T1>* i = A.root;

	while (i != 0)
	{
		ostr << *i << endl;
		i = i->GetNext();
	}
	return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TList<T1> &A) {
	int count;
	istr >> count;
	for (int i = 0; i < count; i++)
	{
		T1 d;
		istr >> d;
		A.InsLast(d);
	}
	return istr;
}

template<class T>
inline TList<T>::TList()
{
	root = 0;
	end = 0;
	count = 0;
}

template <class T>
TList<T>::TList(TList<T>& _v)
{
	root = nullptr;
	count = _v.count;
	TListElem<T>* i = _v.root;
	TListElem<T>* j = this->root;
	TListElem<T>* p = 0;

	while (i != 0)
	{
		j = new TListElem<T>(*i);
		j->SetNext(0);
		if (p != 0)
		{
			p->SetNext(j);
			j->SetPrev(p);
		}

		p = j;

		if (root == nullptr)
			root = j;

		end = j;

		i = i->next;
	}
}
template <class T>
TList<T>::~TList()
{
	if (this->root != 0)
	{
		TListElem<T>* i = this->root;
		TListElem<T>* p = 0;

		while (i != 0)
		{
			p = i;
			i = i->GetNext();
			delete p;
		}

		this->root = 0;
		this->end = 0;
		count = 0;
	}
}

template <class T>
TList<T>& TList<T>::operator =(TList<T>& _v)
{
	if (this == &_v)
		return *this;

	if (this->root != 0)
	{
		TListElem<T>* i = this->root;
		TListElem<T>* p = 0;

		while (i != 0)
		{
			p = i;
			i = i->GetNext();
			delete p;
		}

		this->root = 0;
		this->end = 0;
		count = 0;
	}

	root = nullptr;
	count = _v.count;

	TListElem<T>* i = _v.root;
	TListElem<T>* j = this->root;
	TListElem<T>* p = 0;

	while (i != 0)
	{
		j = new TListElem<T>(*i);
		j->SetNext(0);
		if (p != 0)
		{
			p->SetNext(j);
			j->SetPrev(p);
		}

		p = j;

		if (root == nullptr)
			root = j;

		end = j;

		i = i->next;
	}

}

template<class T>
inline TListIterator<T> TList<T>::Begin()
{
	return TListIterator<T>(*this, root);
}

template<class T>
inline TListIterator<T> TList<T>::End()
{
	return TListIterator<T>(*this, end);
}

template<class T>
inline void TList<T>::InsFirst(T d)
{
	TListElem<T>* tmp = new TListElem<T>(d);
	tmp->SetNext(root);
	root = tmp;
	if (end == 0)
		end = tmp;
	count++;
}

template<class T>
inline void TList<T>::InsLast(T d)
{
	//if (end == root && root != 0)
		//root->SetNext(tmp);
	if (IsEmpty())
		InsFirst(d);
	else
	{
		TListElem<T>* tmp = new TListElem<T>(d);
		if (end != 0)
			end->SetNext(tmp);
		tmp->SetPrev(end);
		tmp->SetNext(0);
		end = tmp;
		count++;
	}
}

template<class T>
inline void TList<T>::Ins(TListElem<T>* e, T d)
{
	TListElem<T>* tmp = new TListElem<T>(d);
	tmp->SetNext(e->GetNext());
	tmp->SetPrev(e);
	e->GetNext()->SetPrev(tmp);
	e->SetNext(tmp);
	count++;
}

template<class T>
inline bool TList<T>::IsEmpty(void) const
{
	return count == 0;
}

template<class T>
inline TListElem<T>* TList<T>::GetFirst()
{
	if ((*this).IsEmpty())
		throw logic_error("empty_list");
	return root;
}

template<class T>
inline TListElem<T>* TList<T>::GetLast()
{
	if ((*this).IsEmpty())
		throw logic_error("empty_list");
	return end;
}

template<class T>
inline void TList<T>::DelFirst()
{
	if (root == 0) throw logic_error("invalid argument");
	TListElem<T>* i = root;
	root = root->GetNext();
	delete i;
	count--;
}

template<class T>
inline void TList<T>::DelLast()
{
	if ((*this).IsEmpty()) throw logic_error("empty list");
	TListElem<T>* j = root;
	if (j->GetNext() != 0) {
		while (j->GetNext()->GetNext() != 0) {
			j = j->GetNext();
		}
		delete j->GetNext();
		j->SetNext(0);
		return;
	}
	delete j;
	root = 0;
}

template<class T>
inline void TList<T>::Del(TListElem<T>* e)
{
	e->GetPrev()->SetNext(e->GetNext());
	e->GetNext()->SetPrev(e->GetPrev());
	count--;
	delete e;
}

template<class T>
inline int TList<T>::GetCount()
{
	return count;
}

template<class T>
inline void TList<T>::reverse()
{
	TListElem<T>* temp = root;

	while (temp != nullptr)
	{
		TListElem<T>* temp2 = temp->GetNext();
		temp->SetNext(temp->GetPrev());
		temp->SetPrev(temp2);
		temp = temp2;
	}
	temp = root;
	root = end;
	end = temp;

}

template<class T>
inline void TList<T>::cleanse()
{
	if (!IsEmpty())
	{
		TList<T> temp;
		temp.InsLast(GetFirst()->GetData());
		TListIterator<T> i(*this, root);
		for(int l = 0; l < GetCount(); l++)
		{
			TListIterator<T> j(temp, temp.root);
			bool CanAdd = true;
			for (int k = 0; k < temp.GetCount(); k++)
			{
				if (j.GetData() == i.GetData())
					CanAdd = false;
				else if (j.CanGoFwd())
					j++;
			}
			if (CanAdd)
				temp.InsLast(i.GetData());
			if (i.CanGoFwd())
				i++;
		}
		*this = temp;
	}
}


template<class T>
inline TListElem<T>::TListElem(T _data)
{
	data = _data;
	next = 0;
	prev = 0;
}

template<class T>
inline TListElem<T>::~TListElem()
{
	next = 0;
	prev = 0;
}

template<class T>
inline T TListElem<T>::GetData()
{
	return data;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetNext()
{
	return next;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetPrev()
{
	return prev;
}

template<class T>
inline void TListElem<T>::SetData(T _data)
{
	data = _data;
}

template<class T>
inline void TListElem<T>::SetNext(TListElem<T>* _next)
{
	next = _next;
}

template<class T>
inline void TListElem<T>::SetPrev(TListElem<T>* _prev)
{
	prev = _prev;
}


template<class T2>
inline TListIterator<T2>::~TListIterator()
{
}

template<class T2>
inline bool TListIterator<T2>::CanGoFwd()
{
	return (current->GetNext() != nullptr);
}

template<class T2>
inline bool TListIterator<T2>::CanGoBck()
{
	return (current->GetPrev() != nullptr)
}

template<class T2>
inline void TListIterator<T2>::GoFwd()
{
	if (!CanGoFwd())
		throw - 1;
	current = current->GetNext();
}

template<class T2>
inline void TListIterator<T2>::GoBck()
{
	if (!CanGoBck())
		throw - 1;
	current = current->GetPrev();
}

template<class T2>
inline bool TListIterator<T2>::operator==(const TListIterator<T2>& _v)
{
	return (current == _v.current);
}

template<class T2>
inline TListIterator<T2> TListIterator<T2>::operator++(int)
{
	GoFwd();
	return (*this);
}

template<class T2>
inline TListIterator<T2> TListIterator<T2>::operator--(int)
{
	GoBck();
	return (*this);
}

template<class T2>
inline TListIterator<T2>& TListIterator<T2>::operator=(const TListIterator<T2>& _v)
{
	link = _v.link;
	current = _v.current;
}

template<class T2>
inline T2 TListIterator<T2>::GetData()
{
	if (current == nullptr)
		throw - 1;
	return current->GetData();
}
