// Carl Underkoffler - Erik Holbrook - Project 1
#include <iostream>
#include <string>

#include "allNames.cpp"
#include "backbone.cpp"
#include "reaction.cpp"

int main()
{
    // std::string inputStr = getInput();
 //   std::string inputStr = "1-({4} 4-(<benzene>)-4-hydroxyl<butane>)-3-nitro<propane>";
 //   std::string inputStr = "1-halide<hexane>";
 //   std::string inputStr = "1-hydroxyl-1-carbonyl<pentane>";
    std::string inputStr = "5-carbonyl-5-hydroxyl<pentane>";


    allNames nmtest(inputStr);

/*    for (unsigned int i = 0; i < nmtest.get_namesSize() ; i++)
    {
    std::cout << nmtest.get_name(i) << std::endl;
    }
*/
    std::string iReacts = "reactions.txt";
    std::string oReacts = "OUTPUT.txt";
    reaction reacClass(iReacts, oReacts);

    for (int j = 0; j < nmtest.get_namesSize(); j++)
    {
        backbone bbclass(nmtest.get_name(j), "valTags.txt" );

        std::cout << bbclass.get_groups() << "::" << bbclass.get_bbName() << std::endl;

        int extCSize = bbclass.get_carbSize();

        std::string extCarbons[extCSize];

        bbclass.load_matrix(extCarbons);

        for (int k = 0; k < extCSize; k++)
        {
            std::cout << k << "<:" << extCarbons[k] << ":>" << std::endl;
        }



        reacClass.load_carbons(extCSize, extCarbons);
    }

    reacClass.write_info();

    std::cout << "Check OUTPUT.TXT for result...\n";

    return 0;
}



std::string getInput()
{
    std::string userInput;

    std::cout << "Please Input a compound:" << std::endl;

    std::cin >> userInput;

    return userInput;
}
