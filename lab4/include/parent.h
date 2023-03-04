#ifndef _PARENT_H
#define _PARENT_H

#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> ParentRoutine(char const *pathToChild1, char const *pathToChild2,
                                       const std::vector<std::string> &input);

#endif