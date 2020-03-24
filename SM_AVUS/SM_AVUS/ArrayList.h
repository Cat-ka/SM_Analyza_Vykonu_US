#pragma once
#include "list.h"
#include "array.h"
#include "structure_iterator.h"


template<typename T>
class ArrayList : public List<T> //aj tu mi chýba nieèo
{
public:
	ArrayList();
	ArrayList(const ArrayList<T>& other);
	~ArrayList();
	Structure* clone() const overrride;  //tu mi asi nieèo chýba
	size_t size() const override;
	List<T>& operator=(const List<T>& other) override;
	ArrayList<T>& operator=(const ArrayList<T>& other);
	T& operator[](const int index) override;
	const T operator[](const int index) const override;
	void add(const T& data) override;
	void insert(const T& data, const int index) override;
	bool tryRemove(const T& data) override;
	T removeAt(const int index) override;
	int getIndexOf(const T& data) override;
	void clear() override;	
	Iterator<T>* getBeginIterator() const override;	
	Iterator<T>* getEndIterator() const override;
private:
	Array<T>* array_;
	size_t size_;
private: 
	void enlarge();

	class ArrayListIterator : public Iterator<T>
	{
	public:
		ArrayListIterator(const ArrayList<T>* arrayList, int position);
		~ArrayListIterator();
		Iterator<T>& operator= (const Iterator<T>& other) override;		
		bool operator!=(const Iterator<T>& other) override;		
		const T operator*() override;		
		Iterator<T>& operator++() override;
	private:
		const ArrayList<T>* arrayList_;
		int position_;
	};
};

template<typename T>
inline ArrayList<T>::ArrayList()
{
	List(),
		array_(new Array<T>(4)),
		size_(0);
}

template<typename T>
inline ArrayList<T>::ArrayList(const ArrayList<T>& other)
{
	List(),
	array_(new Array<T>(*other.array_)),
	size_(other.size_)
}

template<typename T>
inline ArrayList<T>::~ArrayList()
{
	delete T;
	array_ = nullptr;
	size_ = 0;
}

template<typename T>
inline size_t ArrayList<T>::size() const
{
	return size_t();
}

template<typename T>
inline List<T>& ArrayList<T>::operator=(const List<T>& other)
{
	if (this != &other)
	{
		*this = dynamic_cast<const ArrayList<T>&>(other);
	}
	return *this;
}
