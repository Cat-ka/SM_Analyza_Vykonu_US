#include "vector.h"
#include "ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {
	//inicializaËna sekcia
	Vector::Vector(size_t size) : memory_(calloc(size, 1)), size_(size)
		//void* calloc (size_t num, size_t size);
		//priradÌm do memory v˝sledok oper·cie calloc - vr·ti adresu na zaËiatok,
		//prebera dva parametre, robÌ nulovanie, malloc nenuluje
		// do size velkosti
		// : n·m nahradÌ ()
	{
	}

	Vector::Vector(const Vector& other) :  //kopirovaci konstruktor
		Vector(other.size_)					//zavolalo konstruktor, velkost bude velkost vektora other, vznikol prazdny
	{
		memory_ = memcpy(memory_, other.memory_, size_);
		//memcpy - adresa na ktoru chcem zapisovat, z ktorej chcem citat, velkost
		//z jednej adresy sa na druhu prekopituje dany pocet bajtov
		//memcpy(void*, void*, size_t)
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr; //nemusÌ to byù, ale aj keÔ nieËo zruöÌm, tak smernÌk ukazuje na nieËo, Ëo neexistuje, preto pre istotu d·me nullptr
		size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	//operator : specialna metoda pre uspornejsi kod
	//objekt.opertor + (param) == objekt+(param)

	Structure& Vector::operator=(const Structure& other)
		//operator pridarenia od predka
	{
		if (this != &other)
			//porovnanie adries, ci sa neodkazuje na tu istu adresu,
			//ak su identicke nemusim kontrolovat
		{
			*this = dynamic_cast<const Vector&>(other);   // nikdy nedovolÌme priraÔovanie samÈho do seba! vector1 = vector1
			//*this = je vlastne volanie metody operator= (metoda hned pod toutou)
			//pretypovanie dynamic_cast
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other)
		{
			size_ = other.size_;
			memory_ = realloc(memory_, size_);
			memory_ = memcpy(memory_, other.memory_, size_);

		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		if (this == &other)
		{
			return true;
		}
		else
		{
			return size_ == other.size && memcpy(memory_, other.memory_, size_) == 0;
		}
		// alebo aj takto sa to d·
		//return size_ == other.size_ && memcmp(memory_, other.memory_, size_) == 0;
	}

	byte& Vector::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte Vector::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Vector::readBytes: invalid index.");
		DSRoutines::rangeCheckExcept(index + count, this->size_ + 1, "Vector::readBytes: invalid count.");

		if ((this->getBytePointer(index) <= &dest && &dest < this->getBytePointer(index + count)) ||
			(&dest <= this->getBytePointer(index) && this->getBytePointer(index) < &dest + count))
		{
			memmove(&dest, this->getBytePointer(index), count);
		}
		else
		{
			memcpy(&dest, this->getBytePointer(index), count);

		}
		return dest;

	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		if (length == 0)
			return;
		DSRoutines::rangeCheck(srcStartIndex, src.size_, true);
		DSRoutines::rangeCheck(srcStartIndex + length, src.size_ + 1, true);
		DSRoutines::rangeCheck(destStartIndex, dest.size_, true);
		DSRoutines::rangeCheck(destStartIndex + length, dest.size_ + 1, true);
		DSRoutines::rangeCheck(length, src.size_ + 1, true);

		if (&src != &dest)
		{
			memcpy(reinterpret_cast<byte*>(dest.memory_) + destStartIndex, reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
		}
		else
		{
			memmove(reinterpret_cast<byte*>(dest.memory_) + destStartIndex, reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
		}

	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		return reinterpret_cast<byte*>(memory_) + index;
	}

}
