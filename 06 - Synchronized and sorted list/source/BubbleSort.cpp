#include "BubbleSort.h"

void BubbleSort::sort(Data* front) const
{
	if (front == nullptr)
	{
		return;
	}

	front->lock();
	Data* firstPointer = front;

	while (firstPointer != nullptr)
	{
		Data* secondPointer = firstPointer;
		setToTheNextPointer(&secondPointer, false);

		while(secondPointer != nullptr)
		{
			if (*secondPointer > *firstPointer)
			{
				swap(firstPointer, secondPointer);
			}

			setToTheNextPointer(&secondPointer, true);
		}

		setToTheNextPointer(&firstPointer, true);
	}
}

/*
 * This method will swap the messages of two elements.
 * It's thread-safe, if the method is called from the `sort` method.
 * @param firstPointer - pointer to the first element
 * @param secondPointer - pointer to the second element
 */
void BubbleSort::swap(Data* firstPointer, Data* secondPointer)
{
	const std::string tmp = firstPointer->getMessage();
	firstPointer->setMessage(secondPointer->getMessage());
	secondPointer->setMessage(tmp);
}

/*
 * This function will set the pointer to the next element in the list.
 * This method is thread-safe.
 * @param pointer - pointer that has to be set to the next
 * @param unlockPointer - if true, the pointer will be unlocked after setting to the next element. Otherwise, new and old pointers will be locked.
 */
void BubbleSort::setToTheNextPointer(Data** pointer, const bool unlockPointer)
{
	if ((*pointer)->getNext() == nullptr)
	{
		if(unlockPointer)
		{
			(*pointer)->unlock();
		}

		(*pointer) = nullptr;
		return;
	}

	(*pointer)->getNext()->lock();

	if (!unlockPointer)
	{
		(*pointer) = (*pointer)->getNext();
		return;
	}

	Data* pointerToUnlock = *pointer;
	(*pointer) = (*pointer)->getNext();
	pointerToUnlock->unlock();
}
