// Carl Underkoffler - Erik Holbrook - Project 1


#include "backbone.h"

backbone::backbone(std::string inputtedName, std::string tagFilename)     // true "ifChain" or true "ifAromatic"
{
    set_bbName(inputtedName);

    if ( check_bbname() )
    {
        load_valTags(tagFilename);

        set_bools();

        set_bbSize();

        populate_carbons();

        set_carbons();
    }
    else
    {
        std::cout << "ERROR: backbone class could not be properly constructed - given name did not pass 'backbone::check_name()' \n";
    }

//    std::cout << check_bbname() << std::endl;
//    std::cout << bbName << isChain << isAromatic << isEther << "\n";
/*    for (int k = 0; k < carbSize; k++ )
    {
        std::cout << carbons.at(k) << ";:";
    }

    std::cout << std::endl;
*/
    return;
}


backbone::~backbone(){}

void backbone::set_bbName(std::string compound)
{
    int fOAI = 0;   // first open angled bracket index (from the right)

    for (int j = compound.length(); j > 0; j--)
    {
        if(compound[j] == '<')
        {
            fOAI = j;
            break;
        }
    }

    bbName = compound.substr(fOAI+1, compound.length()-2-fOAI);

    groups = compound.erase(fOAI, compound.length() - fOAI);

    return;
}


bool backbone::check_bbname()
{
    // TODO change to comply with standard of adding group strings to carbon matrix

    /*
    Works off the assumption it is valid
    1) if the entire string is just "benzene" than it is valid
    2) if it has a cyclo in it, remove it. It can be valid with or without "cyclo"
    3) if it has one of the words that relates to its size, note that it must have a size and then remove it
    4) the remainders of the string must be the end of the backbone ("ane", "ene" or "yne") - if this is true it is validated
    5) if the string contains all valid phrase but has no size, it is not valid
    6) print error if there is an error
    */

    std::string tempName = bbName;
    bool isValid = false;

    bool hasSize = false;

    if ( tempName == "ether") { isValid = true; hasSize = true;}
    if ( tempName == "benzene"){ isValid  = true; hasSize = true; }     // has inherent size of 6 if benzene

    if ( tempName.find( "cyclo" ) != std::string::npos ){ tempName.erase(0, 5); }

    if ( tempName.find("meth") != std::string::npos ){ tempName.erase(0, 4); hasSize = true; }
    else if ( tempName.find("eth") != std::string::npos ){ tempName.erase(0, 3); hasSize = true; }
    else if ( tempName.find("prop") != std::string::npos ){ tempName.erase(0, 4); hasSize = true; }
    else if ( tempName.find("but") != std::string::npos ){ tempName.erase(0, 3); hasSize = true; }
    else if ( tempName.find("pent") != std::string::npos ){ tempName.erase(0, 4); hasSize = true; }
    else if ( tempName.find("hex") != std::string::npos ){ tempName.erase(0, 3); hasSize = true; }
    else if ( tempName.find("hept") != std::string::npos ){ tempName.erase(0, 4); hasSize = true; }
    else if ( tempName.find("oct") != std::string::npos ){ tempName.erase(0, 3); hasSize = true; }
    else if ( tempName.find("non") != std::string::npos ){ tempName.erase(0, 3); hasSize = true; }

    if ( tempName == "ane" ){ isValid = true; }
    else if ( tempName == "ene" ){ isValid = true; }
    else if ( tempName == "yne" ){ isValid = true; }

    if ( !hasSize ){ isValid = false; }

    return isValid;
}


void backbone::set_bools()
{
    if ( bbName.find( "cyclo" ) != std::string::npos ){ isChain = false; isAromatic = false; isEther = false; }     // if cyclo is in the name than it is not a chain
    else if ( bbName.find( "benzene" ) != std::string::npos ){ isChain= false; isAromatic = true; isEther = false; }     // if it is benzene base than it is aromatic
    else if ( bbName.find( "ether" ) != std::string::npos ){ isEther = true; isAromatic = false; isChain = false; }
    else {isChain = true; isAromatic = false; isEther = false;}
    return;
}


void backbone::set_bbSize()
{

    if ( isAromatic ){ bbSize = 6; }      // the whole thing will be benzene when it is any benzene based compound ( for my naming system )
    else if ( isEther ){bbSize = 1; }
    else if ( bbName.find( "meth" ) != std::string::npos ){ bbSize = 1; }     // "if it can find meth in the bbName, the size of the back bone is 1
    else if ( bbName.find( "eth" ) != std::string::npos ){ bbSize = 2; }     // if it can't find meth, but can find eth, size = 2
    else if ( bbName.find( "prop" ) != std::string::npos ){ bbSize = 3; }        // " "
    else if ( bbName.find( "but" ) != std::string::npos ){ bbSize = 4; }        // " "
    else if ( bbName.find( "pent" ) != std::string::npos ){ bbSize = 5; }        // " "
    else if ( bbName.find( "hex" ) != std::string::npos ){ bbSize = 6; }        // " "
    else if ( bbName.find( "hept" ) != std::string::npos ){ bbSize = 7; }        // " "
    else if ( bbName.find( "oct" ) != std::string::npos ){ bbSize = 8; }        // " "
    else if ( bbName.find( "non" ) != std::string::npos ){ bbSize = 9; }        // " " - I've never used a carbon chain longer than 10 carbons so I am stopping here

    return;
}


void backbone::populate_carbons()
{
    carbons.push_back("CARBON ZERO"); // initializing ether carbons with blank carbon zero

    if (!isEther)
    {
        for (int i = 1; i <= bbSize; i++)
        {
            carbons.push_back("C-C");
        }
    }
    else
    {
        carbons.push_back(" ");
    }

    if( isChain )
    {

        for ( int i = 2; i < bbSize; i++)
        {
            carbons.at(i) += " C-C ";
        }

    }
    else if (!isEther)     // all cyclo compound
    {

        for ( int i = 1; i <= bbSize; i++)
        {
            carbons.at(i) += " C-C ";
        }

    }

    if ( isAromatic )
    {
        for ( int i = 1; i <= bbSize; i++)       // starts on 1 because there is no carbon 0
        {
            carbons.at(i) += " C-C ";
        }
    }

    for (int k = 0; k < carbons.size(); k++)
    {
        if (carbons.at(k) == "") {carbons.erase(carbons.begin()+k); }
    }


    carbSize = carbons.size();

    return;
}

void backbone::set_carbons()
{
//    std::cout << groups << std::endl;

    for (int i = 0; i < valTags.size(); i++)
    {
        int gloc = -1;

//        std::cout << valTags.at(i) << "-";

        if (groups.find(valTags.at(i)) != std::string::npos)
        {


            for (int j = groups.find(valTags.at(i)); j > -1; j--)
            {
                char dig = groups[j];

                if ( isdigit(dig) )
                {
                    gloc = dig - 48;

                    carbons[gloc] += " " + valTags[i];

                    break;
                }
            }
        }
    }

    for (int k = 1; k < carbSize; k++)      // no need to mark carbon zero
    {
        std::string temp = carbons.at(k);

        std::string numGroups[3];

        int num = 0;

        numGroups[0] = "ene";
        numGroups[1] = "ane";
        numGroups[2] = "C-C";


        for (int j = 0; j < 3; j++)
        {
            while (temp.find(numGroups[j]) != std::string::npos)
            {
               num++;
               temp.erase( temp.find(numGroups[j]), 3 );
            }
        }



        if (num < 1){ carbons.at(k) += "LESS THAN ZERO CARBON BONDS";}

        if (num == 1){ carbons.at(k) += " primary";}
        else if (num == 2){ carbons.at(k) += " secondary";}
        else if (num == 3){ carbons.at(k) += " tertiary";}
        else if (num == 4){ carbons.at(k) += " FULLSAT";}

        if (num > 4){carbons.at(k) += ":ERROR: MORE THAN FOUR CARBON BONDS";}

    }


    return;
}

void backbone::load_valTags(std::string filename)
{
    std::ifstream InData;
    InData.open(filename.c_str());

    if ( !InData.is_open()) {return;}

    std::string tag;

    while ( getline(InData, tag) )
    {
        valTags.push_back(tag);
    }

    InData.close();

    return;
}

void backbone::load_matrix(std::string extcarbs[])
{
    for (int i = 0; i < carbSize; i++)
    {
        extcarbs[i] = carbons.at(i);
    }
}

std::string backbone::get_bbName() {return bbName;}
std::string backbone::get_groups() {return groups;}
int backbone::get_carbSize() {return carbSize;}

