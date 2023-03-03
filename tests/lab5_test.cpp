#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <dlfcn.h>
extern "C" {
    #include <contracts.h>
}


TEST(Lab5, DynamicTest)
{
    const std::vector<std::string> FUNCT_NAMES = {"GCD", "E"};
    const char firstRealization[] = "/home/dmimalek/labs/OS/build/lab5/libd1_dynamic.so";
    const char secondRealization[] = "/home/dmimalek/labs/OS/build/lab5/libd2_dynamic.so";
    std::vector<std::vector<int>> GCD_INPUT = {{1, 10}, {20, 100}, {107, 3}, {23, 7}, {10, 4}};
    std::vector<int> GCD_OUTPUT = {1, 20, 1, 1, 2};
    std::vector<int> E_INPUT = {0, 1, 5, 20, 30};
    std::vector<double> E_OUTPUT1 = {1, 2, 2.48832, 2.6533, 2.67432};
    std::vector<double> E_OUTPUT2 = {1, 2, 2.71667, 2.71828, 2.71828};

    int (*GCD_ONE)(int a, int b);
    double (*E_ONE)(int x);
    void *first = dlopen(firstRealization, RTLD_LAZY);

    GCD_ONE =  ((int (*)(int, int))dlsym(first, FUNCT_NAMES[0].c_str()));
    E_ONE = ((double (*)(int))dlsym(first, FUNCT_NAMES[1].c_str()));

    int (*GCD_TWO)(int a, int b);
    double (*E_TWO)(int x);
    void *second = dlopen(secondRealization, RTLD_LAZY);
    GCD_TWO = ((int (*)(int, int))dlsym(second, FUNCT_NAMES[0].c_str()));
    E_TWO = ((double (*)(int))dlsym(second, FUNCT_NAMES[1].c_str()));

    for (size_t i = 0; i < GCD_INPUT.size(); i++)
    {
        auto gcd_1 = GCD_ONE(GCD_INPUT[i][0], GCD_INPUT[i][1]);
        auto gcd_2 = GCD_TWO(GCD_INPUT[i][0], GCD_INPUT[i][1]);
        EXPECT_EQ(gcd_1, GCD_OUTPUT[i]);
        EXPECT_EQ(gcd_2, GCD_OUTPUT[i]);
    }

    for (size_t i = 0; i < E_INPUT.size(); i++)
    {
        auto E_1 = E_ONE(E_INPUT[i]);
        auto E_2 = E_TWO(E_INPUT[i]);
        EXPECT_NEAR(E_1, E_OUTPUT1[i], 0.001);
        EXPECT_NEAR(E_2, E_OUTPUT2[i], 0.001);
    }
}

TEST(Lab5Test, StaticTest)
{

    std::vector<std::vector<int>> GCD_INPUT = {{1, 10}, {20, 100}, {107, 3}, {23, 7}, {10, 4}};
    std::vector<int> GCD_OUTPUT = {1, 20, 1, 1, 2};
    std::vector<int> E_INPUT = {0, 1, 5, 20, 30};
     std::vector<double> E_OUTPUT = {1, 2, 2.48832, 2.6533, 2.67432};

    for (size_t i = 0; i < GCD_INPUT.size(); i++)
    {
        auto gcd_1 = GCD(GCD_INPUT[i][0],GCD_INPUT[i][1]);
        EXPECT_EQ(gcd_1, GCD_OUTPUT[i]);
    }

    for (size_t i = 0; i < E_INPUT.size(); i++)
    {
        auto E_1 = E(E_INPUT[i]);
        EXPECT_NEAR(E_1, E_OUTPUT[i], 0.001);
    }
}
