
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
	void InsFirst(T d);
	void InsLast(T d);
	void Ins(TListElem<T>* e, T d);
	bool IsEmpty(void) const;
	bool IsFull(void) const;
	TListElem<T>* GetFirst();
	TListElem<T>* GetLast();
	void DelFirst();
	void DelLast();
	void Del(TListElem<T>* e);
	template <class T1>
	friend ostream& operator<< (ostream& ostr, const TList<T1> &A);
	template <class T1>
	friend istream& operator >> (istream& istr, TList<T1> &A);
	int GetCount();
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

		if (root == 0)
			root = j;

		end = j;

		i = i->next();
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

		if (root == 0)
			root = j;

		end = j;

		i = i->next();
	}

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
	TListElem<T>* tmp = new TListElem<T>(d);
	tmp->SetPrev(end);
	end = tmp;
	count++;
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
inline bool TList<T>::IsFull(void) const
{
	try
	{
		TListElem<T>* tmp = new TListElem<T>(0);
		delete tmp;
		return false;
	}
	catch (...)
	{
		return true;
	}

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
