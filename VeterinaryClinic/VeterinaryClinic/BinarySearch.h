#include <vector>

#include "Animal.h"
#include <optional>
#include "Select.h"

namespace BinarySearch
{
	std::optional<std::reference_wrapper<Animal>> iterative(Select::Array& animals, const std::string animalId)
	{
		PROFILE_FUNCTION();

		int left = 0, right = animals.second - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (animals.first[mid].GetPersonalId() == animalId)
			{
				return { animals.first[mid] };
			}
			if (animals.first[mid].GetPersonalId() < animalId) 
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
		return std::nullopt;
	}

	std::optional<std::reference_wrapper<Animal>> recursiveSearch(Select::Array& animals, const std::string animalId, int left, int right)
	{
		if (left > right)
		{
			return std::nullopt;
		}
		int mid = (left + right) / 2;
		if (animals.first[mid].GetPersonalId() == animalId)
		{
			return { animals.first[mid] };
		}
		if (animals.first[mid].GetPersonalId() < animalId)
		{
			return BinarySearch::recursiveSearch(animals, animalId, mid + 1, right);
		}
		return BinarySearch::recursiveSearch(animals, animalId, left, mid - 1);
	}

	std::optional<std::reference_wrapper<Animal>> recursive(Select::Array& animals, const std::string animalId, int left, int right)
	{
		PROFILE_FUNCTION();
		return recursiveSearch(animals, animalId, left, right);
	}
}
