#include <hackertoolkit/unindent-literal.h>

#include <iostream>
#include <format>

static void printTest(const char* const name, const char* const value) {
    std::cout << std::format("----- {} -----\n|{}|\n", name, value);
}

// Outputs included in the comments for people that quickly want to see
// what it does without compiling and running the example ;)

int main() {
    constexpr auto str1{R"(hello
        world)"_unindent };
    printTest("str1", str1);
    //----- str1 -----
    //|hello
    //        world|


    const auto str2{ R"( hello    test   

       world
    )"_unindent };
    printTest("str2", str2);
    //----- str2 -----
    //|hello    test
    //
    //      world
    //   |


    constexpr auto str3{ R"(
                hello    test
                        world
            )"_unindent };
    printTest("str3", str3);
    //----- str3 -----
    //|hello    test
    //        world|


    auto str4{ R"-(
        int main() {
            constexpr auto testString1{ R"(
                hello
                world)"_unindent };

            const auto testString2{ R"(
            hello    test   

                world)"_unindent };

            constexpr auto testString3{ R"(
            hello    test
                    world)"_unindent };

            std::cout << testString1 << "\n-----\n"
                << testString2 << "\n-----\n"
                << testString3 << "\n-----\n";
            return 0;
        }
    )-"_unindent };
    printTest("str4", str4);
    //----- str4 -----
    //|int main() {
    //    constexpr auto testString1{ R"(
    //        hello
    //        world)"_unindent };
    //
    //    const auto testString2{ R"(
    //    hello    test
    //
    //        world)"_unindent };
    //
    //    constexpr auto testString3{ R"(
    //    hello    test
    //            world)"_unindent };
    //
    //    std::cout << testString1 << "\n-----\n"
    //        << testString2 << "\n-----\n"
    //        << testString3 << "\n-----\n";
    //    return 0;
    //}|

    constexpr static auto str5{ R"(

          1
         2
        3
       4

    )"_unindent };
    printTest("str5", str5);
    //----- str5 -----
    //|
    //   1
    //  2
    // 3
    //4
    //|

    return 0;
}
