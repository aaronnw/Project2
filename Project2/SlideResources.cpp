/*
#include <iostream>
using namespace std;

template <class DataType>
class AbstractArrayClass {
public:
	virtual int size() const = 0;
	virtual DataType& operator [] (int k) = 0;
};

template <class DataType>
class ArrayClass : virtual public AbstractArrayClass<DataType> {
protected:
	// An array of type DataType will be created and paObject will be
	// the address of the array.
	DataType* paObject;
	int _size;
	void copy(const ArrayClass<DataType>& ac);
public:
	ArrayClass();
	ArrayClass(int n);
	ArrayClass(int n, const DataType& val);
	ArrayClass(const ArrayClass<DataType>& ac);
	virtual ~ArrayClass();
	virtual int size() const;
	virtual DataType& operator [] (int k);
	void operator= (const ArrayClass<DataType>& ac);
};

template <class DataType>
ArrayClass<DataType>::ArrayClass() {
	_size = 0; // default in case allocation fails
	paObject = new DataType[1];
	if (paObject == NULL) //exceptions

	_size = 1;
}
template <class DataType>
ArrayClass<DataType>::ArrayClass(int n) {
	_size = 0; // default in case allocation fails
	paObject = new DataType[n];
	if (paObject == NULL) //exceptions

	_size = n;
}
template<class DataType>
ArrayClass<DataType>::ArrayClass(int n, const DataType& val) {
	_size = 0; // default in case allocation fails
	paObject = new DataType[n];
	if (paObject == NULL) //exceptions


	_size = n;
	for (int i = 0; i < n; i++)
		paObject[i] = val;
}

template <class DataType>
ArrayClass<DataType>::ArrayClass
(const ArrayClass<DataType>& ac) {
	copy(ac);
}

template <class DataType>
void ArrayClass<DataType>::copy(const ArrayClass<DataType>& ac) {
	_size = 0; // default in case allocation fails
	paObject = new DataType[ac._size];
	if (paObject == NULL) //exceptions

	_size = ac._size;
	for (int i = 0; i < _size; i++) {
		paObject[i] = ac.paObject[i];
	}
}

template<class DataType>
ArrayClass<DataType>::~ArrayClass() {
	if (paObject != NULL)
		delete[] paObject;
	paObject = NULL;
	_size = 0;
}
template <class DataType>
int ArrayClass<DataType>::size() const {
	return _size;
}
template <class DataType>
DataType& ArrayClass<DataType>::operator [] (int k) {
	if ((k < 0) || (k >= size())) //Exceptions
	return paObject[k];
}
template <class DataType>
void ArrayClass<DataType>::operator=
(const ArrayClass<DataType>& ac) {
	if (paObject != NULL)
		delete[] paObject;
	copy(ac);
}
template <class DataType>
ostream& operator <<
(ostream& s, AbstractArrayClass<DataType>& ac) {
	s << "[";
	for (int i = 0; i < ac.size(); i++) {
		if (i > 0) {
			s << ',';
		}
		s << ac[i];
	}
	s << "]";
	return s;
}
int main() {
	ArrayClass<int> ai(5, 5);
	ArrayClass<int> ai2 = ai;
	ArrayClass<int> ai3(10);
	cout << ai << endl;
	cout << ai2 << endl;
	cout << ai3 << endl; // output varies as ai3 is uninitialized
	cout << endl;
	for (int i = 0; i < ai.size(); i++) {
		ai[i] = i * 2;
	}
	cout << endl;
	ai3 = ai;
	cout << ai << endl;
	cout << ai2 << endl;
	cout << ai3 << endl;
	return 0;
}

*/