#include <string>
#include "..\Tik_Tak_Toe\Exceptions.h"

// class ExtensionIndex
int ExceptionErrorIndex::get_row() const { return row_index; }
int ExceptionErrorIndex::get_col() const { return col_index; }

// class ExtensionSize
int ExceptionErrorSize::get_size() const { return size; }

// class ExtensionFigureType
char ExceptionErrorFigureType::get_er_fig() const { return this->er_figure; }