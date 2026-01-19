#include <gtest/gtest.h>
#include "Version.h"
#include "Utils.h"

// Dummy test that always passes
TEST(DummyTest, AlwaysPasses) {
    EXPECT_TRUE(true);
}

// Test Version header functionality
TEST(VersionTest, VersionStringNotEmpty) {
    std::string version = Version::getVersionString();
    EXPECT_FALSE(version.empty());
}

TEST(VersionTest, VersionContainsProjectName) {
    std::string version = Version::getVersionString();
    EXPECT_NE(version.find(Version::PROJECT_NAME), std::string::npos);
}

TEST(VersionTest, VersionContainsVersionNumber) {
    std::string version = Version::getVersionString();
    EXPECT_NE(version.find(Version::VERSION), std::string::npos);
}

// Test Utils functions
TEST(UtilsTest, TrimLeftRemovesLeadingSpaces) {
    std::string input = "   hello";
    std::string result = Utils::trimLeft(input);
    EXPECT_EQ(result, "hello");
}

TEST(UtilsTest, TrimRightRemovesTrailingSpaces) {
    std::string input = "hello   ";
    std::string result = Utils::trimRight(input);
    EXPECT_EQ(result, "hello");
}

TEST(UtilsTest, TrimRemovesBothSpaces) {
    std::string input = "   hello   ";
    std::string result = Utils::trim(input);
    EXPECT_EQ(result, "hello");
}

TEST(UtilsTest, GetFileExtensionWorks) {
    EXPECT_EQ(Utils::getFileExtension("file.txt"), "txt");
    EXPECT_EQ(Utils::getFileExtension("file.tar.gz"), "gz");
    EXPECT_EQ(Utils::getFileExtension("noextension"), "");
}

TEST(UtilsTest, GetFileNameWorks) {
    EXPECT_EQ(Utils::getFileName("/path/to/file.txt"), "file.txt");
    EXPECT_EQ(Utils::getFileName("file.txt"), "file.txt");
}

// DUPLICATED TEST PATTERN 1
TEST(ValidationTest, EmptyEmailIsInvalid) {
    EXPECT_FALSE(Utils::isValidEmail(""));
}

TEST(ValidationTest, ShortEmailIsInvalid) {
    EXPECT_FALSE(Utils::isValidEmail("a@b"));
}

TEST(ValidationTest, EmailWithoutAtIsInvalid) {
    EXPECT_FALSE(Utils::isValidEmail("invalidemail.com"));
}

TEST(ValidationTest, ValidEmailIsValid) {
    EXPECT_TRUE(Utils::isValidEmail("test@example.com"));
}

// DUPLICATED TEST PATTERN 2 (similar structure)
TEST(ValidationTest, EmptyUsernameIsInvalid) {
    EXPECT_FALSE(Utils::isValidUsername(""));
}

TEST(ValidationTest, ShortUsernameIsInvalid) {
    EXPECT_FALSE(Utils::isValidUsername("ab"));
}

TEST(ValidationTest, UsernameWithSpecialCharsIsInvalid) {
    EXPECT_FALSE(Utils::isValidUsername("user@name"));
}

TEST(ValidationTest, ValidUsernameIsValid) {
    EXPECT_TRUE(Utils::isValidUsername("valid_user123"));
}

// DUPLICATED TEST PATTERN 3 (similar structure)
TEST(ValidationTest, EmptyPasswordIsInvalid) {
    EXPECT_FALSE(Utils::isValidPassword(""));
}

TEST(ValidationTest, ShortPasswordIsInvalid) {
    EXPECT_FALSE(Utils::isValidPassword("Short1"));
}

TEST(ValidationTest, PasswordWithoutUppercaseIsInvalid) {
    EXPECT_FALSE(Utils::isValidPassword("lowercase123"));
}

TEST(ValidationTest, ValidPasswordIsValid) {
    EXPECT_TRUE(Utils::isValidPassword("ValidPass123"));
}
