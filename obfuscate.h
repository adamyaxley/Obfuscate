#include <cstddef>

namespace ay
{
	// Stores a compile-time obfuscated string
	template <std::size_t N, char KEY>
	class obfuscated_data
	{
	public:
		// Obfuscates the string 'str' on construction
		constexpr obfuscated_data(const char* str)
		{
			static_assert(KEY != '\0', "KEY must not be the null character.");

			// On construction each of the characters in the string is obfuscated with an XOR cipher based on KEY
			for (std::size_t i = 0; i < N; i++)
			{
				m_storage[i] = str[i] ^ KEY;
			}
		}

		// Returns a pointer to the deobfuscated string.
		operator const char*() const
		{
			decrypt();
			return m_storage;
		}

		// Manually deobfuscate the string
		void decrypt() const
		{
			if (is_encrypted())
			{
				for (std::size_t i = 0; i < N; i++)
				{
					m_storage[i] ^= KEY;
				}
			}
		}

		// Manually re-obfuscate the string
		void encrypt() const
		{
			if (!is_encrypted())
			{
				for (std::size_t i = 0; i < N; i++)
				{
					m_storage[i] ^= KEY;
				}
			}
		}

		// Returns true if this string is currently encrypted with an XOR cipher, false otherwise.
		constexpr bool is_encrypted() const
		{
			return m_storage[N - 1] != '\0';
		}

	private:

		// Local storage for the string. Call is_encrypted() to check whether or not the string is currently obfuscated.
		mutable char m_storage[N]{};
	};

	// This function will encrypt the string 'str' with an XOR cipher at compile-time based on 'KEY'
	// and return it in an ay::obfuscated_data object. This object is implicitly convertable to a
	// const char* and when it is converted it will be automatically decrypted to the original string.
	// To guarantee compile-time encryption, the result of this MUST be stored in a constexpr variable
	// For example:
	//     constexpr auto obfuscatedString = ay::obfuscate("Hello World");
	template <std::size_t N, char KEY = '.'>
	constexpr auto obfuscate(const char(&str)[N])
	{
		return obfuscated_data<N, KEY>(str);
	}
}
