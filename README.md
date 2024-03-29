**[Source available on GitHub](https://github.com/adamyaxley/Obfuscate)**

# Obfuscate
Guaranteed compile-time string literal obfuscation header-only library for C++14.

## Quick start guide
1. Copy `obfuscate.h` into your project
2. Wrap strings with `AY_OBFUSCATE("My String")`

Now your project will not expose those strings in plain text in the binary image.

_Note that these strings will still be accessible to determined hackers. Using obfuscation to hide private passwords or any other security sensitive strings is not recommended by the author._

## Whats the problem?
When plain text string literals are used in C++ programs, they will be compiled as-is into the resultant binary. This causes them to be incredibly easy to find. One can simply open up the binary file in a text editor to see all of the embedded string literals in plain view. A special utility called [strings](https://en.wikipedia.org/wiki/Strings_(Unix)) exists which can be used to search binary files for plain text strings.

## What does this library do?
This header-only library seeks to make it difficult (but not impossible) for embedded string literals in binary files to be found by encrypting them with an XOR cipher at compile-time using a constant expression, forcing the compiler to _work with_ the encrypted string instead of the plain text literal. Usage of `AY_OBFUSCATE` additionally removes the need for a const pointer to the string, which more often than not (for small strings) convinces the compiler to inline the encrypted string, building it up at runtime in a series of assembly operations, protecting the binary image against simple XOR decryption attacks. Encrypted strings will then be decrypted at runtime to be utilised within the program.

### Technical features
* _Guaranteed compile-time obfuscation_ - the string is compiled with a constexpr expression.
* _Global lifetime (per-thread)_ - the obfuscated string is stored in a thread local variable in a unique lambda.
* _Implicitly convertible to a char*_ - easy to integrate into existing codebases.
* _Random 64-bit key_ - obfusated with a random key each time.

By simply wrapping your string literal `"My String"` with `AY_OBFUSCATE("My String")` it will be encrypted at compile time with a random 64 bit key and stored in an `ay::obfuscated_data` object which you can manipulate at runtime. For convenience it is also implicitly convertable to a `char*`.

For example, the following program will not store the string "Hello World" in plain text anywhere in the compiled executable.
```c++
#include "obfuscate.h"

int main()
{
    std::cout << AY_OBFUSCATE("Hello World") << std::endl;
    return 0;
}
```

### Examples of usage
Because the obfuscated string that is generated by `AY_OBFUSCATE` has global lifetime per-thread, it is completely fine to also use it in both a local and a temporary context.
```c++
char* var = AY_OBFUSCATE("string");
const char* var = AY_OBFUSCATE("string");
static const char* var = AY_OBFUSCATE("string");
std::string var(AY_OBFUSCATE("string"));
function_that_takes_char_pointer(AY_OBFUSCATE("string"));
```

### Thread safety
This library can be used in a multi-threaded environment only if `AY_OBFUSCATE` is used in a local context per thread. This is because the obfuscated string is internally stored with `thread_local` storage. The following usage is supported:

```c++
void fun()
{
    auto var = AY_OBFUSCATE("Thread Safe");
    var.decrypt();
    std::cout << var << std::endl;
    var.encrypt();
}

int main()
{
    std::thread thread1(fun);
    std::thread thread2(fun);

    thread1.join();
    thread2.join();
    return 0;
}
```

Conversely, sharing an obfuscated string returned from `AY_OBFUSCATE` between multiple threads is *not* supported. In this case you must put locks in appropriate places in your code to ensure that only one thread accesses it at a time. The following usage is *not* supported:

```c++
int main()
{
    for (size_t i = 0; i < 1000; i++)
    {
        auto var = AY_OBFUSCATE("NOT Thread Safe");
        var.decrypt();
        
        std::thread thread([&var]() {
            std::cout << var << std::endl;
        });
        
        // We are encrypting the string here, but outputting it in
        // another thread at the same time. This will not work.
        var.encrypt();

        thread.join();
    }
    return 0;
}
```

## Binary file size overhead
This does come at a small cost. In a very naive login program, which obfuscates two strings (username and password) the following binary file bloat exists.

| Config | Plain string literals | Obfuscated strings | Bloat |
|:------:|:---------------------:|:------------------:|:-----:|
| Release | 18944 | 21504 | 2560 (13.5%) |
| Debug | 95232 | 101888 | 6656 (7.0%) |

This output is generated by running test_bloat.py
