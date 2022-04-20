#pragma once
/*
 * (c) Dmitry Dzyuba, 20.04.2022
 */
#ifdef SAVER_LIB
#define DELCSPEC __declspec(ddlexport)
#else
#define DELCSPEC __declspec(ddlimport)
#endif
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>

 /**
  * \brief �����, ����������� ��������� ��������� ������� � ����. ��������� �� ���� ������ �������� ���
  * \tparam T ��� �������
  */
template<
	typename T, //real type
	typename = std::enable_if_t<std::is_arithmetic_v<T>, T>
>
class saver
{
public:
	/**
	 * \brief ��������� � ����
	 * \param path ���� � ��������� ����� ����� � �����������
	 * \param arr ��������� ������
	 * \param row ���������� ����� � �������
	 * \param col ���������� �������� � �������
	 * \param delimiter ����������� ����� �������. �� ��������� ����� � �������
	 * \param comma_float_separator ����������� ��� �����, ��� ����������� �������
	 */
	static void save(const std::string& path, const std::vector<std::vector<T>>& arr, const int& row, const int& col,
		const char& delimiter = ';', const bool& comma_float_separator = true);
	/**
	 * \brief ��������� � ����
	 * \param path ���� � ��������� ����� ����� � �����������
	 * \param arr ��������� ������������ ������
	 * \param row ���������� ����� � �������
	 * \param col ���������� �������� � �������
	 * \param delimiter ����������� ����� �������. �� ��������� ����� � �������
	 * \param comma_float_separator ����������� ��� �����, ��� ����������� �������
	 */
	static void save(const std::string& path, T** arr, const int& row, const int& col,
		const char& delimiter = ';', const bool& comma_float_separator = true);
	/**
	 * \brief ��������� � ����
	 * \tparam RowCount ���������� ����� � �������
	 * \tparam ColumnCount ���������� �������� � �������
	 * \param path ���� � ��������� ����� ����� � �����������
	 * \param arr ��������� ����������� ������
	 * \param delimiter ����������� ����� �������. �� ��������� ����� � �������
	 * \param comma_float_separator ����������� ��� �����, ��� ����������� �������
	 */
	template <int RowCount, int ColumnCount>
	static void save(const std::string& path, T(&arr)[RowCount][ColumnCount], const char& delimiter = ';',
		const bool& comma_float_separator = true);
	/**
	 * \brief ��������� � ����
	 * \param path ���� � ��������� ����� ����� � �����������
	 * \param arr ���������� ������
	 * \param size ������ �������
	 * \param delimiter ����������� ����� �������. �� ��������� ����� � �������
	 * \param comma_float_separator ����������� ��� �����, ��� ����������� �������
	 */
	static void save(const std::string& path, const std::vector<T>& arr, const int& size, const char& delimiter = ';',
		const bool& comma_float_separator = true);
	/**
	 * \brief ��������� � ����
	 * \param path ���� � ��������� ����� ����� � �����������
	 * \param arr ���������� ������������ ������
	 * \param size ������ �������
	 * \param delimiter ����������� ����� �������. �� ��������� ����� � �������
	 * \param comma_float_separator ����������� ��� �����, ��� ����������� �������
	 */
	static void save(const std::string& path, T* arr, const int& size, const char& delimiter = ';',
		const bool& comma_float_separator = true);
	/**
	 * \brief ��������� � ����
	 * \tparam Size ������ �������
	 * \param path ���� � ��������� ����� ����� � �����������
	 * \param arr ���������� ����������� ������
	 * \param delimiter ����������� ����� �������. �� ��������� ����� � �������
	 * \param comma_float_separator ����������� ��� �����, ��� ����������� �������
	 */
	template <int Size>
	static void save(const std::string& path, T(&arr)[Size], const char& delimiter = ';',
		const bool& comma_float_separator = true);
	/**
	 * \brief ��������� �� ����� � ��������� ������
	 * \param path ���� � ��������� ����� ����� � �����������
	 * \param arr ��������� ������
	 * \param row ���������� ����� � �������
	 * \param col ���������� �������� � �������
	 * \param delimiter ����������� ����� �������. �� ��������� ����� � �������
	 * \param comma_float_separator ����������� ��� �����, ��� ����������� �������
	 */
	static std::vector<std::vector<T>> load(const std::string& path, int& row, int& col,
		const char& delimiter = ';', const bool& comma_float_separator = true);
};

template <typename T, typename T0>
void saver<T, T0>::save(const std::string& path, const std::vector<std::vector<T>>& arr, const int& row, const int& col,
	const char& delimiter, const bool& comma_float_separator)
{
	std::ofstream fout(path);
	if (!fout.is_open())
	{
		throw std::runtime_error("File hasn't been opened");
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (comma_float_separator)
			{
				std::string result = std::to_string(arr[i][j]);
				std::replace(result.begin(), result.end(), '.', ',');
				fout << result;
			}
			else
			{
				fout << arr[i][j];
			}
			if (i == row - 1 && j == col - 1)
			{
				break;
			}
			fout << std::string(1, delimiter);
		}
		fout << std::endl;
	}
	std::cout << "The file " << path << " has been saved" << std::endl;
}

template <typename T, typename T0>
void saver<T, T0>::save(const std::string& path, const std::vector<T>& arr, const int& size, const char& delimiter,
	const bool& comma_float_separator)
{
	std::ofstream fout(path);
	if (!fout.is_open())
	{
		throw std::runtime_error("File hasn't been opened");
	}
	for (int i = 0; i < size; i++)
	{
		if (comma_float_separator)
		{
			std::string result = std::to_string(arr[i]);
			std::replace(result.begin(), result.end(), '.', ',');
			fout << result;
		}
		else
		{
			fout << arr[i];
		}
		if (i == size - 1)
		{
			break;
		}
		fout << delimiter;
	}
	std::cout << "The file " << path << " has been saved" << std::endl;
}

template <typename T, typename T0>
void saver<T, T0>::save(const std::string& path, T** arr, const int& row, const int& col, const char& delimiter, const bool& comma_float_separator)
{
	std::vector<std::vector<T> > temp(row, std::vector<T>(col));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			temp[i][j] = arr[i][j];
		}
	}
	saver<T>::save(path, temp, row, col, delimiter, comma_float_separator);
	temp.clear();
	temp.~vector();
}

template <typename T, typename T0>
void saver<T, T0>::save(const std::string& path, T* arr, const int& size, const char& delimiter,
	const bool& comma_float_separator)
{
	std::vector<T>temp(size);
	for (int i = 0; i < size; i++)
	{
		temp[i] = arr[i];
	}
	saver<T>::save(path, temp, size, delimiter, comma_float_separator);
	temp.clear();
	temp.~vector();
}

template <typename T, typename T0>
template <int RowCount, int ColumnCount>
void saver<T, T0>::save(const std::string& path, T(&arr)[RowCount][ColumnCount], const char& delimiter,
	const bool& comma_float_separator)
{
	std::vector<std::vector<T> > temp(RowCount, std::vector<T>(ColumnCount)); // ��� �������
	for (int i = 0; i < RowCount; i++)
	{
		for (int j = 0; j < ColumnCount; j++)
		{
			temp[i][j] = arr[i][j];
		}
	}
	saver<T>::save(path, temp, RowCount, ColumnCount, delimiter, comma_float_separator);
	temp.clear();
	temp.~vector();
}

template <typename T, typename T0>
template <int Size>
void saver<T, T0>::save(const std::string& path, T(&arr)[Size], const char& delimiter, const bool& comma_float_separator)
{
	std::vector<T>temp(Size);
	for (int i = 0; i < Size; i++)
	{
		temp[i] = arr[i];
	}
	saver<T>::save(path, temp, Size, delimiter, comma_float_separator);
	temp.clear();
	temp.~vector();
}

template <typename T, typename T0>
std::vector<std::vector<T>> saver<T, T0>::load(const std::string& path, int& row, int& col,
	const char& delimiter, const bool& comma_float_separator)
{
	std::vector<std::vector<T>> arr;
	row = 0;
	col = 0;
	std::ifstream fin(path);
	if (!fin.is_open())
	{
		throw std::runtime_error("File hasn't been opened");
	}
	std::string get;
	while (std::getline(fin, get))
	{
		std::vector<std::string> vec;
		std::stringstream ss(get);
		while (std::getline(ss, get, delimiter))
		{
			vec.push_back(get);
		}
		std::vector<T> result;
		for (auto& element : vec)
		{
			std::replace(element.begin(), element.end(), ',', '.');
			std::stringstream is_string_stream(element);
			T num{};
			is_string_stream >> num;
			result.push_back(num);
		}
		arr.push_back(result);
		col = static_cast<int> (vec.size());
		result.clear();
		result.~vector();
		vec.clear();
		vec.~vector();
		row++;
	}
	std::cout << "The file " << path << " has been loaded. The data has been uploaded to the array" << std::endl;
	return arr;
}


