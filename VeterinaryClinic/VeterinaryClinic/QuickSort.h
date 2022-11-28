#pragma once

#include <algorithm>
#include <vector>
#include "Animal.h"
#include "Select.h"

namespace QuickSort
{
    int partition(Select::Array& animals, int low, int high)
    {
        Animal pivot = animals.first[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (animals.first[j] < pivot) {
                i++; 
                std::swap(animals.first[i], animals.first[j]);
            }
        }
        std::swap(animals.first[i + 1], animals.first[high]);
        return (i + 1);
    }

    void recursiveSort(Select::Array& animals, int low, int high)
    {
        if (low < high) {
            int partIndex = partition(animals, low, high);

            recursiveSort(animals, low, partIndex - 1);
            recursiveSort(animals, partIndex + 1, high);
        }
    }

    void recursive(Select::Array& animals, int low, int high)
    {
        PROFILE_FUNCTION();
        recursiveSort(animals, low, high);
    }

	void iterative(Select::Array& animals)
	{
        PROFILE_FUNCTION();
        int low = 0, high = animals.second - 1;
        int* stack = new int[high - low + 1];
        int top = -1;

        stack[++top] = low;
        stack[++top] = high;
        
        while (top >= 0) {
            high = stack[top--];
            low = stack[top--];
            int pivot = partition(animals, low, high);
            
            if (pivot - 1 > low) {
                stack[++top] = low;
                stack[++top] = pivot - 1;
            }

            if (pivot + 1 < high) {
                stack[++top] = pivot + 1;
                stack[++top] = high;
            }
        }

        delete stack;
	}

    void STL(Select::Array& animals)
    {
        PROFILE_FUNCTION();
        std::sort(animals.first, animals.first + animals.second);
    }
}