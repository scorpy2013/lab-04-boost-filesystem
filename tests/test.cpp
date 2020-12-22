// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <sstream>

#include "directory_analyzer.hpp"
std::string find_broker() {
  std::string s = __FILE__;
  return s.substr(0, s.find("test.cpp"));
}
TEST(Finance, BoolOperator) {
  Finance lhs, rhs;
  lhs.date.year = 2020;
  lhs.date.month = 12;
  lhs.date.day = 30;
  rhs.date.year = 2020;
  rhs.date.month = 12;
  rhs.date.day = 31;
  EXPECT_TRUE(lhs < rhs);
}
TEST(DirectoryAnalyzer, Constructor) {
  fs::path PATH1;
  ASSERT_EQ(directory_analyzer{PATH1}.get_path_to_ftp().string(), "..");
  fs::path PATH2{"../misc"};
  ASSERT_EQ(directory_analyzer{PATH2}.get_path_to_ftp().string(), "../misc");
}
TEST(DirectoryAnalyzer, ListFiles) {
  directory_analyzer analyzer1{fs::path{find_broker()}};
  analyzer1.directory_analyzer3();
  std::stringstream str;
  analyzer1.list_files(str);
  EXPECT_EQ(str.str(), "brokers balance_12345678_20201230.txt\n");
}
TEST(DirectoryAnalyzer, InfoFiles) {
  directory_analyzer analyzer2{fs::path{find_broker()}};
  analyzer2.directory_analyzer3();
  std::stringstream str;
  analyzer2.info_files(str);
  EXPECT_EQ(
      str.str(),
      "broker: brokers  account: 12345678  files: 1  lastdate: 2020-12-30 \n");
}