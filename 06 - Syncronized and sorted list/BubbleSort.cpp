#include "BubbleSort.h"

void BubbleSort::sort(Data* front, Data* end)
{
	assert(front != nullptr && "Received NULL pointer in BubbleSort : front");
	assert(end != nullptr && "Received NULL pointer in BubbleSort : end");

	Data* firstPointer = front;
	Data* secondPointer = front->getNext();

	while (firstPointer != nullptr)
	{
		secondPointer = firstPointer->getNext();

		while(secondPointer != nullptr)
		{
			if (*secondPointer > *firstPointer)
			{
				swapData(*firstPointer, *secondPointer);
			}

			secondPointer = secondPointer->getNext();
		}

		firstPointer = firstPointer->getNext();
	}
}
