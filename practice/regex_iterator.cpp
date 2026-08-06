#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string str14 = "db@aol.com m@.com @apple.com db@.com devinqtran@gmail.com";

    // Notice the \\. before [A-Za-z] to correctly escape the literal dot in C++
    std::regex reg15("[\\w._%+-]{1,20}@[\\w.-]{2,20}\\.[A-Za-z]{2,3}");

    // 1. Create an iterator starting at the beginning of the string
    auto matches_begin = std::sregex_iterator(str14.begin(), str14.end(), reg15);

    // 2. Create an empty iterator which acts as the "end" condition
    auto matches_end = std::sregex_iterator();

    std::cout << "Found the following emails:\n";

    // 3. Loop from the beginning until you hit the end iterator
    for (std::sregex_iterator i = matches_begin; i != matches_end; ++i)
    {
        std::smatch match = *i; // Dereference the iterator to get the match object
        std::cout << "- " << match.str() << '\n';
    }

    return 0;
}