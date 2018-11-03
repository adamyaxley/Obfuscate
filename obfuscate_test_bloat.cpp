/* ------------------------------- ABOUT ---------------------------------------

Obfuscate naive login example (bloat test)
This example login program demonstrates how much bloat is added to the final
executable if AY_OBFUSCATE is used to obfuscate security sensitive strings at
compile-time.

Run calculate_bloat.py to output a table comparing release and debug configs.

----------------------------------------------------------------------------- */

#include <iostream>
#include <string>

#ifdef USE_AY_OBFUSCATE
	#include "obfuscate.h"
#else
	#define AY_OBFUSCATE(text) text
#endif

int main() 
{
	const std::string username = AY_OBFUSCATE("root");
	const std::string password = AY_OBFUSCATE("password");

	std::cout << "Obfuscate naive login example (bloat test)" << std::endl;

	std::string input_username;
	std::string input_password;

	while (true)
	{
		std::cout << "Username: ";
		std::cin >> input_username;

		std::cout << "Password: ";
		std::cin >> input_password;

		if (input_username == username && input_password == password)
		{
			std::cout << "Login success!" << std::endl;
			break;
		}
		else
		{
			std::cout << "Login failure: unrecognised username and password"
				"combination." << std::endl;
		}
	}

	return 0;
}