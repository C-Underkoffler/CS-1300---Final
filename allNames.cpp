#include "allNames.h"

allNames::allNames(std::string input)
{
    names.clear();

 //   std::cout << input << std::endl;

    inputName = clean_name(input);

    invert_names();

    strip_names();

    return;
}

allNames::~allNames(){}

std::string allNames::clean_name(std::string input)
{
    for (int i = 0; i < input.length(); i++)
    {
        if ( ispunct(input[i]) || input[i] == ' ' )      // sees if it is punctuation or space;
        {
// replacing brackets
            if (input[i] == '[') { input.replace(i, 1, 1, '(' ); continue;}      // this helps clean names that have been inverted by the invert function
            else if (input[i] == ']') { input.replace(i, 1, 1, ')' ); continue;}
// deleting spaces
            if (input[i] == ' ')
            {
                input.erase(i, 1); // at this point it will erase blank spaces and non approved punctuation
                i--;        // without this, there will be errors with back to back spaces
            }
// adding implicit {1} to secondaries
            if (input[i] == '(' && input[i+1] != '{')     // makes sure the implicit {1} is included
            {
                input.insert(i+1, "{1}-");
            }
// getting rid of unnecessary hyphens

            if (input[i] == '-' && input[i+1] == '-')     // gets rid of double "--"
            {
                input = input.erase(i, 1);
                i--;
                continue;
            }

            if (input[i] == '-' && input[i+1] == '>')     // gets rid of double "->"
            {
                input = input.erase(i, 1);
                i--;
                continue;
            }


        }
        else        // since it is not punctuation or a space it is likely a letter
        {
            if ( isupper(input[i]) )        // identifies upper case
            {
                input[i] = tolower( input[i] );     // changes to lower case
            }
        }

// checking things have a pair

        int openMinusClosed = 0;
        int omcB = 0;
        int omcT = 0;

        for (unsigned int i = 0; i < input.length(); i++)
        {
            if (input[i] == '(') {openMinusClosed++;}
            else if (input[i] == ')') {openMinusClosed--;}
            else if (input[i] == '[') {omcB++;}
            else if (input[i] == ']') {omcB--;}
            else if (input[i] == '<') {omcT++;}
            else if (input[i] == '>') {omcT--;}

        }

        if (openMinusClosed != 0 || omcB != 0)
        {
            if (omcT != 0)
            {
                std::cout << "ERROR in allNames::Invert. Unmatched parenthesis, bracket, or angled bracket in compound" << std::endl;
                return "";
            }
        }

    }

    return input;
}

void allNames::invert_names()
{
        names.push_back(inputName);    // first element is original name

//    std::cout << inputName << std::endl;

    std::string tempname = inputName;        // need temp name for erasing and chopping up

//    if (tempname.find('(') == std::string::npos) { return; }        // if there are no secondary backbones than it will just return

    while ( tempname.find('(') != std::string::npos )       // if there are no secondary backbones than it will end
    {
 //       std::cout << inputName << std::endl;

        int openParenIndex = tempname.find('(');    // location of open parenthesis
        int closeParenIndex = 0;        // location of the closed parenthesis that matches the first open parenthesis
        int openMinusClosed = 0;        // for use finding the matching parenthesis

        for (std::size_t i = openParenIndex; i < tempname.length(); i++)
        {
            if (tempname[i] == '(') {openMinusClosed++;}
            else if (tempname[i] == ')') {openMinusClosed--;}

            if (openMinusClosed == 0) {closeParenIndex = i-1; break;}
        }

        int digits = 0;     // size of primary location integer
        bool digswitch = false;     // for use find when the number has ended after it has begun

        int secbegin = 0;       // the location of the integer that relates to the location of the secondary backbone

        for (int i = openParenIndex; i > -1; i--)
        {
            if ( isdigit(tempname[i]) )
            {
                digswitch = true;   // shows that we are currently looking at a number

                digits++;
            }
            else if (digswitch)  // since there is no longer a digit but there were adjacent digits, this is the beginning of the number
            {
                secbegin = i+1;     // because we are moving in negative i direction, num begins one to the right
                break;     // crudely breaks out of loop
            }
        }

//std::cout << digits << std::endl << openMinusClosed << std::endl << openParenIndex << std::endl << closeParenIndex << std::endl << secbegin << std::endl;


        std::string secDigstring = tempname.substr(secbegin, digits); // the location of the new secondary (old primary)

        std::string newPrimary = tempname.substr(openParenIndex+1, closeParenIndex - openParenIndex);

        std::string newSecondary = tempname.erase(secbegin, closeParenIndex + 1 - (secbegin-1) );      // getting rid of secondary location information

        newSecondary += ']';      // adding "]" to the end as a stand in parenthesis (not to interfere with while loop)

        newSecondary = "[{" + secDigstring + "}-" + newSecondary;  // add secondary location string in proper format

        std::string priDigstring = newPrimary.substr(newPrimary.find('{')+1, newPrimary.find('}')-newPrimary.find('{')-1);

        newSecondary = priDigstring + "-" + newSecondary + "-";

        newPrimary = newPrimary.erase(newPrimary.find('{'), newPrimary.find('}')-newPrimary.find('{')+1);

//        std::cout << newSecondary << std::endl;
//       std::cout << newPrimary << std::endl;

        std::string altName = newSecondary + newPrimary;

        tempname = altName;     // while inverting I swapped a pair of parenthesis for brackets so this loop can be broken

        altName = clean_name(altName);      // puts parenthesis back in

        names.push_back(altName);
    }

    namesSize = names.size();

    return;
}

void allNames::strip_names()
{
    for (unsigned int k = 0; k < namesSize ; k++)      //cycling through the names
    {
        std::string currentname = names.at(k);

        int openMinusClosed = 0;        // for counting pairs of parenthesis

        int oMCA = 0;

        for (std::size_t i = 0; i < currentname.length(); i++)
        {
            if (currentname[i] == '(')
            {
                openMinusClosed++;
            }
            else if (currentname[i] == ')')
            {
                openMinusClosed--;
            }
            if (currentname[i] == '<')
            {
                oMCA++;
            }
            else if (currentname[i] == '>')
            {
                oMCA--;
            }
//          //
            if ( openMinusClosed == 1)
            {
                if (oMCA == 0 )
                {
                    currentname.erase(i, 1);
                    i--;
                }
            }
            else if (openMinusClosed > 1)
            {
                currentname.erase(i, 1);
                i--;
            }

        }

        bool firstOpenAngle = true;
        bool firstCloseAngle = true;
// /*
        for (int j = currentname.length(); j > 0; j--)
        {

            if(currentname[j] == '<')
            {
                if (firstOpenAngle)
                {
                    firstOpenAngle = false;
                }
                else
                {
                    currentname.erase(j, 1);
                    j++;
                }
            }

            if(currentname[j] == '>')
            {
                if (firstCloseAngle)
                {
                    firstCloseAngle = false;
                }
                else
                {
                    currentname.erase(j, 1);
                    j++;
                }
            }

            if(currentname[j] == '(') {currentname.erase(j, 1);} // there should never be (( so no need for j++

            if (currentname[j] == ')') {currentname.erase(j, 1);} // ""
        }
//*/
        names.at(k) = currentname;
//        std::cout << currentname << std::endl;
    }


}


std::string allNames::get_name(unsigned int i)
{
    return names.at(i);
}

void allNames::set_namesSize() { namesSize = names.size(); }
unsigned int allNames::get_namesSize() {return namesSize;}

std::string allNames::get_inputName() {return inputName;}


