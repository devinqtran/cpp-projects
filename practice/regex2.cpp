#include <thread>
#include <ctime>
#include <regex>
#include <iostream>

void printMatches(std::string str, std::regex reg)
{
    std::smatch matches;
    std::cout << std::boolalpha;
    while (std::regex_search(str, matches, reg))
    {
        std::cout << "Is there a match : " << matches.ready() << "\n";
        std::cout << "Are there no matches : " << matches.empty() << "\n";
        std::cout << "Number of matches : " << matches.size() << "\n";
        std::cout << matches.str(1) << "\n";
        str = matches.suffix().str();
        std::cout << "\n";
    }
}

void printMatches2(std::string str, std::regex reg)
{
    std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
    std::sregex_iterator lastMatch;
    while (currentMatch != lastMatch)
    {
        std::smatch match = *currentMatch;
        std::cout << match.str() << "\n";
        currentMatch++;
    }
    std::cout << "\n";
}

int main()
{
    std::string str = "The ape was at the apex";

    // Search a string for a match
    std::smatch matches;

    // Search for anything but a space
    std::regex reg("(ape[^ ]?)");

    printMatches(str, reg);

    std::string str2 = "I picked the pickle";
    std::regex reg2("(pick([^ ]+)?)");
    printMatches2(str2, reg2);

    std::string str3 = "Cat rat mat fat pat slat";

    std::regex reg3("(([crmfp]|(sl))at)");

    std::regex reg4("([C-Fc-f]at)");

    // Anything without 'C' or 'r'
    std::regex reg5("([^Cr]at)");

    // Replace matches
    std::string str6 = "Cat rat mat fat pat";
    std::regex reg6("([Cr]at)");
    std::string owlFood = std::regex_replace(str6, reg6, "Owl");
    std::cout << owlFood << "\n";

    printMatches2(str3, reg4);

    std::string str7 = "F.B.I. I.R.S. C.I.A.";
    std::regex reg7("([^ ]\\..\\..\\.)");
    printMatches(str7, reg7);

    // Remove white space, detect '\n'
    std::string str8 = "This is a multiline string\n"
                       "that has many lines.";
    std::regex reg8("\n");
    std::string noLBstr = std::regex_replace(str8, reg8, " ");
    std::cout << noLBstr << "\n";
    // Also can replace '\b' : Backspace
    // '\r' : Carriage Return
    //'\f' : Form Feed
    //'\t' : Tab
    //'\v': Vertical Tab

    // Numbers \d : [0-9]
    // \D : Antrhing besides a number [^0-9]
    std::string str9 = "12345";
    std::regex reg9("\\d");
    printMatches2(str9, reg9);

    // Fetch every number 5-7 digits long
    std::string str10 = "123 12345 123456 1234567";
    std::regex reg10("\\d{5,7}");
    printMatches2(str10, reg10);

    // Match any
    std::string str11 = "703-646-4395";
    std::regex reg11("\\w{3}-\\w{3}-\\w{4}");
    printMatches2(str11, reg11);

    // Match whitespace \s find a valid name 2-20 char, space, name 2-20 char
    std::string str12 = "Inaki Williams";
    std::regex reg12("\\w{2,20}\\s\\w{2,20}");
    printMatches2(str12, reg12);

    // Match for any word starting with a that is more than one char
    std::string str13 = "a as ape bug";
    std::regex reg13("a[a-z]+");
    printMatches2(str13, reg13);

    std::string str14 = "db@aol.com m@.com @apple.com db@.com devinqtran@gmail.com jessicaktran@yahoo.com";
    std::regex reg14("(\\w{1,20}@\\w{1,20}\\.(com))");
    std::regex reg15("[\\w._%+-]{1,20}@[\\w.-]{2,20}\\.[A-Za-z]{2,3}");
    printMatches2(str14, reg15);

    return 0;
}