//  Copyright 2019 U.C. Berkeley RISE Lab
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "lattices/top_k_priority_lattice.hpp"
#include "gtest/gtest.h"

class TopKPriorityLatticeTest : public ::testing::Test {
protected:
  TopKPriorityLattice<double, string> *tkpl;

  PriorityValuePair<double, string> p1 = PriorityValuePair<double, string>(1.1, "1.1");
  PriorityValuePair<double, string> p2 = PriorityValuePair<double, string>(2.2, "2.2");
  PriorityValuePair<double, string> p3 = PriorityValuePair<double, string>(1.2, "1.2");
  PriorityValuePair<double, string> p4 = PriorityValuePair<double, string>(2.3, "2.3");
  PriorityValuePair<double, string> p5 = PriorityValuePair<double, string>(1.3, "1.3");
  PriorityValuePair<double, string> p6 = PriorityValuePair<double, string>(2.4, "2.4");

  std::set<PriorityValuePair<double, string>> set1 = {p1, p2}; 
  std::set<PriorityValuePair<double, string>> set2 = {p3, p4};
  std::set<PriorityValuePair<double, string>> set3 = {p5, p6};
  std::set<PriorityValuePair<double, string>> set12 = {p2, p4};
  std::set<PriorityValuePair<double, string>> set123 = {p4, p6};

  TopKPriorityLatticeTest() { tkpl = new TopKPriorityLattice<double, string>(2); }
  virtual ~TopKPriorityLatticeTest() { delete tkpl; }
};

TEST_F(TopKPriorityLatticeTest, Assign) {
  EXPECT_EQ(0, tkpl->size().reveal());
  tkpl->assign(set1);
  EXPECT_EQ(2, tkpl->size().reveal());
  EXPECT_EQ(set1, tkpl->reveal());
}

TEST_F(TopKPriorityLatticeTest, MergeByLattice) {
  EXPECT_EQ(0, tkpl->size().reveal());
  tkpl->merge(TopKPriorityLattice<double, string>(2, set1));
  EXPECT_EQ(2, tkpl->size().reveal());
  EXPECT_EQ(set1, tkpl->reveal());
  tkpl->merge(TopKPriorityLattice<double, string>(2, set2));
  EXPECT_EQ(2, tkpl->size().reveal());
  EXPECT_EQ(set12, tkpl->reveal());
  tkpl->merge(TopKPriorityLattice<double, string>(2, set3));
  EXPECT_EQ(2, tkpl->size().reveal());
  EXPECT_EQ(set123, tkpl->reveal());
}

TEST_F(TopKPriorityLatticeTest, MergeByValue) {
  EXPECT_EQ(0, tkpl->size().reveal());
  tkpl->merge(set1);
  EXPECT_EQ(2, tkpl->size().reveal());
  EXPECT_EQ(set1, tkpl->reveal());
  tkpl->merge(set2);
  EXPECT_EQ(2, tkpl->size().reveal());
  EXPECT_EQ(set12, tkpl->reveal());
  tkpl->merge(set3);
  EXPECT_EQ(2, tkpl->size().reveal());
  EXPECT_EQ(set123, tkpl->reveal());
}

