#include <vector>

#include "Animal.h"
#include <optional>

namespace BinarySearch
{
	std::optional<std::reference_wrapper<Animal>> iterative(std::vector<Animal>& animals, const std::string animalId) //TODO move sem
	{
		PROFILE_FUNCTION();
		int left = 0, right = animals.size() - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (animals[mid].GetPersonalId() == animalId)
			{
				return { animals[mid] };
			}
			if (animals[mid].GetPersonalId() < animalId) 
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

	std::optional<std::reference_wrapper<Animal>> recursiveSearch(std::vector<Animal>& animals, const std::string animalId, int left, int right) //TODO move sem
	{
		if (left > right)
		{
			return std::nullopt;
		}
		int mid = (left + right) / 2;
		if (animals[mid].GetPersonalId() == animalId)
		{
			return { animals[mid] };
		}
		if (animals[mid].GetPersonalId() < animalId)
		{
			return BinarySearch::recursiveSearch(animals, animalId, mid + 1, right);
		}
		return BinarySearch::recursiveSearch(animals, animalId, left, mid - 1);
	}

	std::optional<std::reference_wrapper<Animal>> recursive(std::vector<Animal>& animals, const std::string animalId, int left, int right)
	{
		PROFILE_FUNCTION();
		return recursiveSearch(animals, animalId, left, right);
	}
}
