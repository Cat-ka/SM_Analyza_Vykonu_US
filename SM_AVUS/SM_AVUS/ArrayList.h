#pragma once
#include "list.h"
#include "array.h"
#include "structure_iterator.h"


//namespace structures
//{


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
		return size_;
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

	template<typename T>
	inline ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other)
	{
		if (this != &other)
		{
			size_ = other.size_;
			delete array_;
			array_ = new Array<T>(*other.array_);
		}
		return *this;
	}

	template<typename T>
	inline T& ArrayList<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Index out of range in ArrayList");
		return (*array_)[index];
	}

	template<typename T>
	inline const T ArrayList<T>::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Index out of range in ArrayList");
		return (*array_)[index];
	}

	template<typename T>
	inline void ArrayList<T>::add(const T& data)
	{
		if (array_->size() == size_)
		{
			enlarge();
		}
		(*array_)[static_cast<int>(size_++)] = data;
	}

	template<typename T>
	inline void ArrayList<T>::insert(const T& data, const int index)
	{
		if (index == static_cast<int>(size_))
		{
			add(data);
		}
		else
		{
			DSRoutines::rangeCheckExcept(index, size_, "Index out of range in ArrayList");
			if (array_->size() == size_)
			{
				this->enlarge();
			}
			Array<T>::copy(*array_, static_cast<int>(index), *array_, static_cast<int>(index + 1), size_ - index);
			(*array_)[index] = data;
			size_++;
		}
	}

	template<typename T>
	inline bool ArrayList<T>::tryRemove(const T& data)
	{
		int index = this->getIndexOf(data);
		if (index == -1)
		{
			return false;
		}
		else
		{
			removeAt(index);
			return true;
		}
	}

	template<typename T>
	inline T ArrayList<T>::removeAt(const int index)
	{
		T result = (*this)[index];

		DSRoutines::rangeCheckExcept(index, size_, "Index out of bounds");
		Array<T>::copy(*array_, static_cast<int>(index + 1), *array_, static_cast<int>(index), (size_ - index - 1));
		size_--;
		return result;
	}

	template<typename T>
	inline int ArrayList<T>::getIndexOf(const T& data)
	{
		for (int index = 0; index < static_cast<int>(size_); index++)
		{
			if ((*this)[index] == data)
			{
				return index;
			}
		}
		return -1;
	}

	template<typename T>
	inline void ArrayList<T>::clear()
	{
		size_ = 0; // nemám v arrayliste žiadne dáta!! èi mám v poli 0 alebo hocijaké iné hodnoty nás v tomto prípade nezaujíma, mažeme arraylist nie array
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getBeginIterator() const
	{
		return new ArrayListIterator(this, 0);
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getEndIterator() const
	{
		return new ArrayListIterator(this, static_cast<int>(size_));
	}

	template<typename T>
	inline void ArrayList<T>::enlarge()
	{
		Array<T>* newArray = new Array<T> * (2 * size_);
		Array<T>::copy(*array_, 0, *newArray, 0, static_cast<int>(size_));
		delete array_;
		array_ = newArray_;
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::ArrayListIterator(const ArrayList<T>* arrayList, int position) :
		arrayList_(arrayList),
		position_(position)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::~ArrayListIterator()
	{
		arrayList_ = nullptr;
		position_ = -1;
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator=(const Iterator<T>& other)
	{
		position_ = dynamic_cast<const ArrayListIterator&>(other).position_;
		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::ArrayListIterator::operator!=(const Iterator<T>& other)
	{
		return position_ != dynamic_cast<const ArrayListIterator&>(other).position_;
	}

	template<typename T>
	inline const T ArrayList<T>::ArrayListIterator::operator*()
	{
		return (*arrayList_)[position_];
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator++()
	{
		position_++;
		return *this;
	}
//}
