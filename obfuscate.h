#include <cstddef>

namespace ay
{
	// Obfuscates a string at compile time
	template <std::size_t N, char KEY>
	class obfuscator
	{
	public:
		// Obfuscates the string 'data' on construction
		constexpr obfuscator(const char* data)
		{
			static_assert(KEY != '\0', "KEY must not be the null character.");

			// On construction each of the characters in the string is obfuscated with an XOR cipher based on KEY
			for (std::size_t i = 0; i < N; i++)
			{
				m_data[i] = data[i] ^ KEY;
			}
		}

		constexpr const char* getData() const
		{
			return &m_data[0];
		}

	private:

		char m_data[N]{};
	};

	// Handles decryption and re-encryption of an encrypted string at runtime
	template <std::size_t N, char KEY>
	class obfuscated_data
	{
	public:
		obfuscated_data(const char* data)
		{
			for (int i = 0; i < N; i++)
			{
				m_data[i] = data[i];
			}
		}

		~obfuscated_data()
		{
			// Zero m_data to remove it from memory
			for (int i = 0; i < N; i++)
			{
				m_data[i] = 0;
			}
		}

		// Returns a pointer to the plain text string, decrypting it if necessary
		operator char*()
		{
			decrypt();
			return m_data;
		}

		// Manually decrypt the string
		void decrypt()
		{
			if (is_encrypted())
			{
				for (std::size_t i = 0; i < N; i++)
				{
					m_data[i] ^= KEY;
				}
			}
		}

		// Manually re-encrypt the string
		void encrypt()
		{
			if (!is_encrypted())
			{
				for (std::size_t i = 0; i < N; i++)
				{
					m_data[i] ^= KEY;
				}
			}
		}

		// Returns true if this string is currently encrypted, false otherwise.
		bool is_encrypted() const
		{
			return m_data[N - 1] != '\0';
		}

	private:

		// Local storage for the string. Call is_encrypted() to check whether or not the string is currently obfuscated.
		char m_data[N];
	};

	// This function exists purely to extract the number of elements 'N' in the array 'data'
	template <std::size_t N, char KEY>
	constexpr auto makeObfuscator(const char(&data)[N])
	{
		return obfuscator<N, KEY>(data);
	}
}

// This helper macro will encrypt the string 'data' with an XOR cipher at compile-time based on 'key'
// and return it in an ay::obfuscated_data object. This object is implicitly convertable to a
// char* and when it is converted it will be automatically decrypted to the original string.
// This macro is useful because it guarantees that ay::makeObfuscator is run at compile-time by
// assigning it to a constexpr variable.
#define AY_OBFUSCATE(data, key) \
	[](){ \
		constexpr auto n = sizeof(data)/sizeof(data[0]); \
		static_assert(data[n - 1] == '\0', "String must be null terminated"); \
		constexpr auto obfuscator = ay::makeObfuscator<n, key>(data); \
		return ay::obfuscated_data<n, key>(obfuscator.getData()); \
	}()