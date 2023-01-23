#include "BubbleSort.h"

#include <cassert>

void BubbleSort::sort(Data* front, /* unused */ Data* end) const
{
	assert(front != nullptr && "Received NULL pointer in BubbleSort : front");
	assert(end != nullptr && "Received NULL pointer in BubbleSort : end");

	Data* firstPointer = front;

	while (firstPointer != nullptr)
	{
		Data* secondPointer = firstPointer->getNext();

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
