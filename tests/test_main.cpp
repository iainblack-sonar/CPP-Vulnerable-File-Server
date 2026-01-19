#include <gtest/gtest.h>
#include "Version.h"

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

