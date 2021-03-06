// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_DIRECTORY_ANALYZER_HPP_
#define INCLUDE_DIRECTORY_ANALYZER_HPP_
#include <boost/filesystem.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>
namespace fs = boost::filesystem;
// YYYYMMDD -> дата, где YYYY-год, MM-месяц и DD-день
struct Date {
  unsigned int year;
  unsigned int month;
  unsigned int day;
};
struct Finance {
  std::string broker;     // брокер
  std::string fields;     // вся информация о брокере
  std::string type_file;  // тип файла
  size_t number_account;  // номер счета
  Date date;              // дата
  std::string extension;  // расширение файла
};
class directory_analyzer {
 private:
  fs::path path_to_ftp;  // путь к анализируемой директории
  std::vector<Finance> finance_files;  // вектор финансов
  std::vector<std::string> fields;  // вектор полей FTP файлов
  std::map<size_t, std::vector<Finance>>
      accounts;  // ключ-номер, значение-финансовый файл
  Finance parsing(std::string FIELDS);  // разбираем наши поля по переменным
  void analyze_directory(const fs::path& PATH_TO_FTP);
  void analyze_file(const fs::path& PATH_TO_FTP);

 public:
  const fs::path& get_path_to_ftp() const;
  explicit directory_analyzer(const fs::path& PATH_TO_FTP);
  void directory_analyzer2(const fs::path& PATH_TO_FTP);
  void directory_analyzer3();
  void list_files(std::ostream& out);  // выводим ВСЕ файлы
  void info_files(std::ostream& out);  // вводим основную информацию о файлах
};
// оператор сравнения для нахождения самого актуального (самого нового) файла
bool operator<(const Finance& lhs, const Finance& rhs);
#endif  // INCLUDE_DIRECTORY_ANALYZER_HPP_
