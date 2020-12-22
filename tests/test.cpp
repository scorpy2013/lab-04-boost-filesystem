// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <sstream>

#include "directory_analyzer.hpp"

std::string find_file() {
  std::string s = __FILE__;
  return s.substr(0, s.find("test.cpp"));
}

TEST(Finance, make_tuple) {
  Finance lhs, rhs;
  lhs.date.year = 2020;
  lhs.date.month = 11;
  lhs.date.day = 11;
  rhs.date.year = 2020;
  rhs.date.month = 11;
  rhs.date.day = 12;
  EXPECT_TRUE(lhs < rhs);
}

TEST(directory_analyzer, path) {
  fs::path lhs;
  ASSERT_EQ(directory_analyzer{lhs}.get_path_to_ftp().string(), "..");
  fs::path rhs{"../misc"};
  ASSERT_EQ(directory_analyzer{rhs}.get_path_to_ftp().string(), "../misc");
}

TEST(directory_analyzer, list_files) {
  directory_analyzer analyzer{fs::path{find_file()}};
  analyzer.start(fs::path{find_file()});
  std::stringstream str;
  analyzer.list_files(str);
  EXPECT_EQ(str.str(), "Broker balance_00122223_20180901.txt\n");
}

TEST(directory_analyzer, info_files) {
  directory_analyzer analyzer{fs::path{find_file()}};
  analyzer.start(fs::path{find_file()});
  std::stringstream str;
  analyzer.info_files(str);
  EXPECT_EQ(
      str.str(),
      "broker: Broker  account: 00122223  files: 1  lastdate: 2018-9-1 \n");
}
