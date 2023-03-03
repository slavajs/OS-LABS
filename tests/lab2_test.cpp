#include <gtest/gtest.h>
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
namespace fs = std::filesystem;
extern "C" {
    #include <parent.h>
    #include <utils.h>
}
TEST(LAB2, test_text) {
    std::vector<std::string> input;
    std::vector<std::string> expectedOutput;
    input = {
        "abcdAD            ...",
        "ABVC___     sfS....",
        "MORE test DSF ___   fdsf",
        "Hello World!",
        "we are Here",
        "88005553535   dsfsdf...///*84324",
        "________________________              AAAA",
        "!?+-*/_;",
        "A",
        "BBBBBBBBBBBBBB                      AAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
        " "
    };


    expectedOutput = {
            "abcdad____________...",
            "advc________sfs....",
            "more_test_Ddsf_______fdsf",
            "hello_world!",
            "we_are_here",
            "88005553535___dsfsdf...///*84324",
            "______________________________________AAAA",
            "",
            "a",
            "_"
    };
    {
        auto inFile = std::ofstream("input.txt");

        for (const auto& line : input) {
            inFile << line << '\n';
        }
    }
    FILE *ifs = fopen("input.txt", "r");
    FILE *ofs = fopen("output.txt", "w");
    fclose(ofs);
    fclose(ifs);
    ParentRoutine(ifs, ofs);
    std::ifstream readData;
    readData.open("output.txt",std::ifstream::out);

    std::string line;
    int i = 0;
    if (readData.is_open()) {
        while (getline(readData, line)) {
            std::cout << line << std::endl; 
            EXPECT_EQ(line, expectedOutput[i]);
            ++i;
        }
    }
    auto removeIfExists = [](const char* path) {
        if (fs::exists(path)) {
            fs::remove(path);
        }
    };
    readData.close();
    removeIfExists("input.txt");
    removeIfExists("output.txt");
}