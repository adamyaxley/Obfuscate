#include <cstdio>
#ifdef USE_AY_OBFUSCATE
	#include "obfuscate.h"
#else
	#define AY_OBFUSCATE(text) text
#endif

int main() 
{
	puts(AY_OBFUSCATE("Hello World. -Brian Kernighan"));
	puts(AY_OBFUSCATE("Life is about making an impact, not making an income. -Kevin Kruse"));
	puts(AY_OBFUSCATE("Whatever the mind of man can conceive and believe, it can achieve. -Napoleon Hill"));
	puts(AY_OBFUSCATE("Two roads diverged in a wood, and I—I took the one ""less traveled by, And that has made all the difference. -Robert Frost"));
	puts(AY_OBFUSCATE("Twenty years from now you will be more disappointed by the things that you didn’t do than by the ones you did do, so throw off the bowlines, sail away from safe harbor, catch the trade winds in your sails.  Explore, Dream, Discover. -Mark Twain"));
	return 0;
}