#include <string>
#include <iostream>

#include "status_macros.h"
#include "gtest/gtest.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"

namespace {

absl::Status InvalidErrOnEvenArg(const int val) {
  if (val % 2 == 0) {
    return absl::Status(
        absl::StatusCode::kInvalidArgument,
        "Only odd values allowed.");
  }
  return absl::OkStatus();
}

absl::Status InvokeFunctionWithArg(const int val) {
  RETURN_IF_ERROR(InvalidErrOnEvenArg(val));
  return absl::OkStatus();
}

TEST(StatusMacrosTest, ReturnIfErrorMacroTest) {
  const absl::Status status = InvokeFunctionWithArg(2);
  EXPECT_FALSE(status.ok());
  EXPECT_STREQ(status.message().data(), "Only odd values allowed.");
}

TEST(StatusMacrosTest, ReturnIfErrorMacroTest2) {
  const absl::Status status = InvokeFunctionWithArg(3);
  EXPECT_TRUE(status.ok());
  EXPECT_STREQ(status.message().data(), nullptr);
}

absl::StatusOr<int> OnlyReturnSumOnEvenResult(const int a, const int b) {
  if ((a + b) % 2 == 0) {
    return a + b;
  }
  return absl::Status(absl::StatusCode::kInvalidArgument,
      absl::StrFormat("Sum of args [%d + %d] is not even.", a, b));
}

absl::Status InvokeReturnSumOnEvenResult(const int a, const int b) {
  ASSIGN_OR_RETURN(const int sum, OnlyReturnSumOnEvenResult(a, b));
  return absl::OkStatus();
}

TEST(StatusMacrosTest, StatusOrReturnsErrorOnBadStatus) {
  const absl::Status status = InvokeReturnSumOnEvenResult(2, 1);
  EXPECT_FALSE(status.ok());
  EXPECT_STREQ(status.message().data(),
      "Sum of args [2 + 1] is not even.");
}

TEST(StatusMacrosTest, StatusOrReturnsOkOnGoodStatus) {
  const absl::Status status = InvokeReturnSumOnEvenResult(2, 2);
  EXPECT_TRUE(status.ok());
  EXPECT_STREQ(status.message().data(), nullptr);
}

}

