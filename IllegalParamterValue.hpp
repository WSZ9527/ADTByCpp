#pragma once
#include <string>
#include <ostream>
#include <sstream>
class IllegalParamterValue
{
	std::string m_message;
public:
	inline IllegalParamterValue()
		:m_message("Illegal parameter value") {}
	inline IllegalParamterValue(const char* _message)
		: m_message(_message) {}
	inline IllegalParamterValue(const std::ostringstream& _message)
		: m_message(_message.str()) {}
	inline friend std::ostream& operator<<(std::ostream& _out, const IllegalParamterValue& _ill)
	{
		_out << _ill.m_message;
		return _out;
	}
	operator std::string() const
	{
		return m_message;
	}

	const std::string& what() const
	{
		return this->m_message;
	}
};