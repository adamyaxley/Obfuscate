#include "obfuscate.h"
#include <cstdio>
#include <cassert>
#include <string>

static const char* g_global_static1 = AY_OBFUSCATE("global_static1");
static const char* g_global_static2 = AY_OBFUSCATE("global_static2");

int main() 
{
	// Test AY_OBFUSCATE (main test)
	{
		// Encrypt a string literal with an XOR cipher at compile time and store
		// it in test.
		auto test = AY_OBFUSCATE("Hello World");

		// The string starts out as encrypted
		assert(test.is_encrypted());

		// Manually decrypt the string. This is useful for pre-processing
		// especially large strings.
		test.decrypt();
		assert(!test.is_encrypted());

		// Output the plain text string to the console (implicitly converts to
		// const char*)
		puts(test);

		// Re-encrypt the string so that it cannot be seen in it's plain text
		// form in memory.
		test.encrypt();
		assert(test.is_encrypted());

		// The encrypted string will be automatically decrypted if necessary
		// when implicitly converting to a const char*
		puts(test);

		// The string is in a decrypted state
		assert(!test.is_encrypted());

		// Test comparison
		assert(std::string("Hello World") == (char*)test);
	}
	
	// Test AY_OBFUSCATE_KEY
	{
		auto test = AY_OBFUSCATE_KEY("Hello World", '@');

		puts(test);

		// Test comparison
		assert(std::string("Hello World") == (char*)test);
	}
	
	// Test direct API usage
	{
		constexpr auto obfuscator = ay::make_obfuscator("Hello World");
		auto test = ay::obfuscated_data<obfuscator.getSize(), 
			obfuscator.getKey()>(obfuscator);

		puts(test);

		// Test comparison
		assert(std::string("Hello World") == (char*)test);
	}

	// Test global static const char* variables
	{
		assert(strcmp(g_global_static1, "global_static1") == 0);
		puts(g_global_static1);
		assert(strcmp(g_global_static2, "global_static2") == 0);
		puts(g_global_static2);
	}

	// Test local const char* variables
	{
		const char* local1 = AY_OBFUSCATE("local1");
		const char* local2 = AY_OBFUSCATE("local2");

		assert(strcmp(local1, "local1") == 0);
		puts(local1);
		assert(strcmp(local2, "local2") == 0);
		puts(local2);
	}

	return 0;
}