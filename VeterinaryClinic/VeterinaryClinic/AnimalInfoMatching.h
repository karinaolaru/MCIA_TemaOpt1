#pragma once

namespace AnimalInfoRegex {
	const char* MALE = "[0-9]0{8}";
	const char* FEMALE = "[0-9]1{8}";
	const char* HOUSE_PET = "1[0-1][0-9]{8}";
	const char* DOMESTIC = "2[0-1][0-9]{8}";
	const char* EXOTIC = "3[0-1][0-9]{8}";
	const char* BIRD = "4[0-1][0-9]{8}";
	const char* FISH = "5[0-1][0-9]{8}";
	const char* INVALID_BIRTHDATE = "[0-1][1-5]00000000";
}