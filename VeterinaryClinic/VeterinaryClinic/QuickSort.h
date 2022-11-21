#pragma once

#include <algorithm>
#include <vector>
#include "Animal.h"

namespace QuickSort
{
    int partition(const std::vector<Animal>& animals, int low, int high)
    {
        Animal pivot = animals[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (animals[j] < pivot) {
                i++; 
                std::swap(animals[i], animals[j]);
            }
        }
        std::swap(animals[i + 1], animals[high]);
        return (i + 1);
    }

    void recursive(const std::vector<Animal>& animals, int low, int high)
    {
        if (low < high) {
            int partIndex = partition(animals, low, high);

            recursive(animals, low, partIndex - 1);
            recursive(animals, partIndex + 1, high);
        }
    }

	void iterative(const std::vector<Animal>& animals)
	{
        int low = 0, high = animals.size() - 1;
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

    void STL(const std::vector<Animal>& animals)
    {
        std::sort(animals.begin(), animals.end());
    }
}