#include "gtest/gtest.h"
#include "obfuscate.h"

#include <cstdio>
#include <string>

// Test AY_OBFUSCATE (main test)
TEST(Obfuscate, AY_OBFUSCATE)
{
	// Encrypt a string literal with an XOR cipher at compile time and store
	// it in test.
	auto test = AY_OBFUSCATE("Hello World");

	// The string starts out as encrypted
	ASSERT_TRUE(test.is_encrypted());

	// Manually decrypt the string. This is useful for pre-processing
	// especially large strings.
	test.decrypt();
	ASSERT_TRUE(!test.is_encrypted());

	// Output the plain text string to the console (implicitly converts to
	// const char*)
	puts(test);

	// Re-encrypt the string so that it cannot be seen in it's plain text
	// form in memory.
	test.encrypt();
	ASSERT_TRUE(test.is_encrypted());

	// The encrypted string will be automatically decrypted if necessary
	// when implicitly converting to a const char*
	puts(test);

	// The string is in a decrypted state
	ASSERT_TRUE(!test.is_encrypted());

	// Test comparison
	ASSERT_TRUE(std::string("Hello World") == (char*)test);
}

// Test AY_OBFUSCATE_KEY
TEST(Obfuscate, AY_OBFUSCATE_KEY)
{
	auto test = AY_OBFUSCATE_KEY("Hello World", 0xf8d3481a4bc32d83ull);

	puts(test);

	// Test comparison
	ASSERT_TRUE(std::string("Hello World") == (char*)test);
}

// Test direct API usage
TEST(Obfuscate, API)
{
	constexpr auto obfuscator = ay::make_obfuscator("Hello World");
	auto test = ay::obfuscated_data<obfuscator.size(), obfuscator.key()>(obfuscator);

	puts(test);

	// Test comparison
	ASSERT_TRUE(std::string("Hello World") == (char*)test);
}

static const char* g_global_static1 = AY_OBFUSCATE("global_static1");
static const char* g_global_static2 = AY_OBFUSCATE("global_static2");

// Test global static const char* variables
TEST(Obfuscate, GlobalConstCharPtr)
{
	ASSERT_TRUE(strcmp(g_global_static1, "global_static1") == 0);
	puts(g_global_static1);
	ASSERT_TRUE(strcmp(g_global_static2, "global_static2") == 0);
	puts(g_global_static2);
}

// Test local const char* variables
TEST(Obfuscate, LocalConstCharPtr)
{
	const char* local1 = AY_OBFUSCATE("local1");
	const char* local2 = AY_OBFUSCATE("local2");

	ASSERT_TRUE(strcmp(local1, "local1") == 0);
	puts(local1);
	ASSERT_TRUE(strcmp(local2, "local2") == 0);
	puts(local2);
}

// Test non-null terminated strings
TEST(Obfuscate, NonNullTerminatedStr)
{
	constexpr auto obfuscator = ay::obfuscator<10, AY_OBFUSCATE_DEFAULT_KEY>("1234567890");
	auto test = ay::obfuscated_data<obfuscator.size(), obfuscator.key()>(obfuscator);

	puts(test);

	// Test comparison
	assert(std::string("1234567890") == (char*)test);
}
