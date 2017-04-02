#include "kiwi_exception.h"

namespace kiwi {

	KiwiException::KiwiException(const std::string &message) : message_(message)
	{
	}

	const char *KiwiException::what() const throw()
	{
		return message_.c_str();
	}

}
