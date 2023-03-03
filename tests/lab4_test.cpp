#include <gtest/gtest.h>

#include <array>
#include <memory>
#include <parent.h>
#include <vector>


TEST(FirstLabTests, SimpleTest) {


    std::vector<std::string> input;
    input = {
        "ABCABC",
        "QWERTY QWERTY",
        "MORE   ___",
        "HeLlo    WOrld",
        "Aboba   $#@$",
        " ",
        "A"
    };

    std::vector<std::string> expectedOutput;
     expectedOutput = {
        "abcabc",
        "qwerty_qwerty",
        "more______",
        "hello____world",
        "aboba___$#@$",
        "_",
        "a"
    };


    auto result = ParentRoutine(
            "/home/dmimalek/labs/OS/build/lab4/child1_4",
            "/home/dmimalek/labs/OS/build/lab4/child2_4",
            input);
    for (size_t i = 0; i < result.size(); i++) {
            EXPECT_EQ(result[i], expectedOutput[i]);
    }
}