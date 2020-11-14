// Copyright 2020 Your Name <your_email>

#include <algorithm>
#include <directory_analyzer.hpp>
#include <iomanip>
#include <tuple>
const fs::path &directory_analyzer::get_path_to_ftp() const {
  return path_to_ftp;
}
std::ostream &operator<<(std::ostream &out, const Date &date) {
  out << date.year << "-" << date.month << "-" << date.day;
  return out;
}
bool operator<(const Finance &lhs, const Finance &rhs) {
  return std::make_tuple(lhs.date.year, lhs.date.month, lhs.date.day) <
         std::make_tuple(rhs.date.year, rhs.date.month, rhs.date.day);
}
void directory_analyzer::start(const fs::path &PATH_TO_FTP) {
  for (const auto &it : fs::directory_iterator(PATH_TO_FTP)) {
    if (fs::is_regular_file(it)) {
      analyze_file(it);
    } else if (fs::is_directory(it)) {
      analyze_directory(it);
    }
  }
  if (finance_files.empty()) {
    finance_files.pop_back();
  }
}
directory_analyzer::directory_analyzer(const fs::path &PATH_TO_FTP) {
  if (PATH_TO_FTP.empty()) {
    path_to_ftp = fs::path{".."};
  } else {
    path_to_ftp = PATH_TO_FTP;
  }
}
Finance directory_analyzer::parsing(std::string FIELDS) {
  Finance finance;
  finance.fields = FIELDS;

  finance.type_file = FIELDS.substr(0, FIELDS.find('_'));
  FIELDS = FIELDS.substr(FIELDS.find('_') + 1);

  finance.number_account = std::stoi(FIELDS.substr(0, FIELDS.find('_')));
  FIELDS = FIELDS.substr(FIELDS.find('_') + 1);

  finance.date.year = std::stoi(FIELDS.substr(0, 4));
  finance.date.month = std::stoi(FIELDS.substr(4, 2));
  finance.date.day = std::stoi(FIELDS.substr(6, 2));
  FIELDS = FIELDS.substr(8);

  if (FIELDS[0] != '.' || FIELDS.substr(0, 4) == ".old") {
    throw std::exception();
  } else if (FIELDS.substr(1).find('.') != std::string::npos) {
    throw std::exception();
  }
  if (FIELDS != ".txt") {
    throw std::exception();
  }
  finance.extension = FIELDS;
  return finance;
}
void directory_analyzer::list_files(std::ostream &out) {
  for (const auto &it : finance_files)
    out << it.broker << " " << it.fields << std::endl;
}
void directory_analyzer::info_files(std::ostream &out) {
  for (const auto &it : accounts) {
    out << "broker: " << it.second[0].broker << " ";
    out << " account: ";
    out << std::setw(8) << std::setfill('0') << it.first << " ";
    out << " files: " << it.second.size() << " ";
    out << " lastdate: "
        << std::max_element(it.second.begin(), it.second.end())->date << " ";
    out << std::endl;
  }
}
void directory_analyzer::analyze_directory(const fs::path &PATH_TO_FTP) {
  fields.push_back(PATH_TO_FTP.stem().string());
  start(PATH_TO_FTP);
}
void directory_analyzer::analyze_file(const fs::path &PATH_TO_FTP) {
  try {
    Finance file = parsing(PATH_TO_FTP.filename().string());
    file.broker = fields.back();
    finance_files.emplace_back(file);
    accounts[file.number_account].emplace_back(file);
  } catch (std::exception &ex) {
  }
}
