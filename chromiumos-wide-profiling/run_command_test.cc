// Copyright 2015 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chromiumos-wide-profiling/run_command.h"

#include "chromiumos-wide-profiling/quipper_test.h"

#include <vector>
#include <string>

namespace quipper {

TEST(RunCommandTest, StoresStdout) {
  std::vector<char> output;
  EXPECT_TRUE(RunCommand({"/bin/sh", "-c", "echo 'Hello, world!'"}, &output));
  std::string output_str(output.begin(), output.end());
  EXPECT_EQ("Hello, world!\n", output_str);
}

TEST(RunCommandTest, RunsFromPath) {
  std::vector<char> output;
  EXPECT_TRUE(RunCommand({"sh", "-c", "echo 'Hello, world!'"}, &output));
  std::string output_str(output.begin(), output.end());
  EXPECT_EQ("Hello, world!\n", output_str);
}

TEST(RunCommandTest, LargeStdout) {
  std::vector<char> output;
  EXPECT_TRUE(RunCommand({"dd", "if=/dev/zero", "bs=5", "count=4096"},
                         &output));
  EXPECT_EQ(5 * 4096, output.size());
  EXPECT_EQ('\0', output[0]);
  EXPECT_EQ('\0', output[1]);
  EXPECT_EQ('\0', *output.rbegin());
}

TEST(RunCommandTest, StdoutToDevnull) {
  EXPECT_TRUE(RunCommand({"/bin/sh", "-c", "echo 'Hello, world!'"}, nullptr));
}

TEST(RunCommandTest, StderrIsNotStored) {
  std::vector<char> output;
  EXPECT_TRUE(RunCommand({"/bin/sh", "-c", "echo 'Hello, void!' >&2"},
                         &output));
  EXPECT_EQ(0, output.size());
}

}  // namespace quipper

int main(int argc, char * argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
