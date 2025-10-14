#pragma once
#include <iostream>

class ExceptionError : std::exception
{
protected:
	std::string msg;
public:
	ExceptionError(const char* str): msg(str) {}
	virtual ~ExceptionError() {}

	const char* what() const noexcept override
	{
		return this->msg.c_str();
	}
};

class ExceptionErrorIndex: public ExceptionError
{
	int row_index{ 0 }, col_index{ 0 };

public:
	ExceptionErrorIndex(const char* str, int row_index, int col_index) : ExceptionError(str), row_index(row_index), col_index(col_index) {}

	int get_row() const;
	int get_col() const;
};

class ExceptionErrorSize : public ExceptionError
{
	int size{ 0 };

public:
	ExceptionErrorSize(const char* str, int size) : ExceptionError(str), size(size) {}

	int get_size() const;
};

class ExceptionErrorInt : public ExceptionError
{
public:
	ExceptionErrorInt(const char* str): ExceptionError(str)
	{}
};

class ExceptionErrorGmpType : public ExceptionError
{
public:
	ExceptionErrorGmpType(const char* str) : ExceptionError(str)
	{}
};

class ExceptionErrorFigureType : public ExceptionError
{
	char er_figure;
public:
	ExceptionErrorFigureType(const char* str, char c) : ExceptionError(str), er_figure(c)
	{}

	char get_er_fig() const;
};

class ExceptionErrorFieldCoordChar : public ExceptionError
{
public:
	ExceptionErrorFieldCoordChar(const char* str): ExceptionError(str) {}
};

class ExceptionErrorDifLevel : public ExceptionError
{
public:
	ExceptionErrorDifLevel(const char* str) : ExceptionError(str)
	{}
};