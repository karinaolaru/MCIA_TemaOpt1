#pragma once

#include <string>

namespace AnimalInfoMatch {
	const std::string MALE = "0[0-9]{9}";
	const std::string FEMALE = "1[0-9]{9}";
	const std::string HOUSE_PET = "[0-1]1[0-9]{8}";
	const std::string DOMESTIC = "[0-1]2[0-9]{8}";
	const std::string EXOTIC = "[0-1]3[0-9]{8}";
	const std::string BIRD = "[0-1]4[0-9]{8}";
	const std::string FIHS = "[0-1]5[0-9]{8}";
	const std::string INVALID_BIRTHDATE = "[0-1][1-5]00000000";
}