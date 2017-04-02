#pragma once

#include <exception>
#include <string>

namespace kiwi {

	class KiwiException : public std::exception
	{
	public:
		KiwiException(const std::string& message);

		virtual const char* what() const throw();

	protected:
		std::string message_;
	};
}
