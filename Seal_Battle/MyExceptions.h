#pragma once

#include <exception>
#include <string>

class MyException : public std::exception
{
	std::string message;

public:
	MyException(const std::string& message) : message(message)
	{}

	const char* what() const noexcept override
	{
		return this->message.c_str();
	}
};

class ExceptionFieldCoords : public MyException
{
public:
	ExceptionFieldCoords(const std::string& message) : MyException(message)
	{}
};

class ExceptionFieldPoint : public MyException
{
public:
	ExceptionFieldPoint(const std::string& message) : MyException(message)
	{}
};

class ExceptionInvalidArgument : public MyException
{
public:
	ExceptionInvalidArgument(const std::string& message) : MyException(message)
	{}
};

class ExceptionExitCode : public MyException
{
public:
	ExceptionExitCode(const std::string& message) : MyException(message)
	{
	}
};