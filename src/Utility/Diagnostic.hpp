#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

// Assertion macros useful for testing your program.
//
// Usage:
//
// 1. Perform some operations (optionally, using exec);
// 2. Test the results (compared to the expected results) using the
//    assertion macros below;
// 3. Call diagnostic() to show the results, and find the number of errors.
//
// For an example, see ToricTest.cpp.

#include <cmath>
#include <iostream>
#include <string>

static int gNumTests = 0;
static int gErrors = 0;
static int gRes = 0;

// Prints a statement, followed by a comment, then executes the statement.
#define exec(cmd, comment) \
    if (std::string(#comment).length() > 2) { \
        std::cout << "    [Exec] " #cmd " /* " #comment " */" << std::endl; \
    } else { \
        std::cout << "    [Exec] " #cmd << std::endl; \
    } \
    cmd;

// Checks that the numbers a and b are equal, allowing for a small error p (for
// floating point comparisons).
#define eqAssertPrec(a, b, p) \
    gNumTests++; \
    gRes = (std::abs((a) - (b)) <= p) ? 0 : 1; \
    if (gRes != 0) { \
        std::cout << "    [Fail] line " << __LINE__ << " " << #a ": " << std::endl \
                  << "      !!   Expected: " << (b) << std::endl \
                  << "      !!   Obtained: " << (a) << std::endl;\
    } else { \
        std::cout << "    [Pass] " #a " == " #b << std::endl; \
    } \
    gErrors += gRes;

// Checks that a and b are equal.
#define eqAssert(a, b) \
    gNumTests++; \
    gRes = ((a)==(b)) ? 0 : 1; \
    if (gRes != 0) { \
        std::cout << "    [Fail] line " << __LINE__ << " " << #a ": " << std::endl \
                  << "      !!   Expected: " << (b) << std::endl \
                  << "      !!   Obtained: " << (a) << std::endl;\
    } else { \
        std::cout << "    [Pass] " #a " == " #b << std::endl; \
    } \
    gErrors += gRes;

// Checks that a and b are not equal.
#define neqAssert(a, b) \
    gNumTests++; \
    gRes = ((a)!=(b)) ? 0 : 1; \
    if (gRes != 0) { \
        std::cout << "    [Fail] line " << __LINE__ << " " << #a ": " << std::endl \
                  << "      !!   Expected: " << (b) << std::endl \
                  << "      !!   Obtained: " << (a) << std::endl;\
    } else { \
        std::cout << "    [Pass] " #a " != " #b << std::endl; \
    } \
    gErrors += gRes;

// Checks that a is NULL or zero.
#define assertNULL(a) \
    gNumTests++; \
    gRes = ((a)==0) ? 0 : 1; \
    if (gRes != 0) { \
        std::cout << "    [Fail] line " << __LINE__ << " " << #a ": " << std::endl \
                  << "      !!   Expected: 0" << std::endl \
                  << "      !!   Obtained: " << (a) << std::endl;\
    } else { \
        std::cout << "    [Pass] " #a " == 0"<< std::endl; \
    } \
    gErrors += gRes;

// Displays a message summarizing the number of tests executed and the success rate.
// Returns the number of errors.
static int diagnostic()
{
    gRes = 0;
    std::cout << std::endl
              << "=======================================" << std::endl
              << (gNumTests-gErrors) << "/" << gNumTests << " tests passed (" << gErrors << " failed)." << std::endl
              << "=======================================" << std::endl;
    return gErrors;
}

#endif
