#include "obfuscate.h"
#include <cstdio>
#include <cassert>

int main() 
{
	// Encrypt a string literal with an XOR cipher at compile time and store it in test.
	// To guarantee compile time obfuscation, this MUST be stored in a constexpr variable.
	constexpr auto test = ay::obfuscate("Hello World");
	
	// The string is encrypted at compile-time so this static_assert must be true
	static_assert(test.is_encrypted(), "String must be obfuscated on construction.");

	// Manually decrypt the string. This is useful for pre-processing especially large strings.
	test.decrypt();
	assert(!test.is_encrypted());

	// Output the plain text string to the console (implicitly converts to const char*)
	puts(test);

	// Re-encrypt the string so that it cannot be seen in it's plain text form in memory.
	test.encrypt();
	assert(test.is_encrypted());

	// The encrypted string will be automatically decrypted if necessary when implicitly converting to a const char*
	puts(test);
	
	// The string is in a decrypted state
	assert(!test.is_encrypted());

	return 0;
}