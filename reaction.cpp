#include "reaction.h"

reaction::reaction(std::string ifilename, std::string ofilename)
{
    // setting up file names
    inFilename = ifilename;
    if (inFilename != ofilename) {outFilename = ofilename;}
    else {std::cout << "ERROR - Output filename can't be the same as Input filename" << std::endl;}

    // making sure the vectors are clear out (not sure if this is necessary)
    iReactions.clear();
    valReactions.clear();

    output = "";        // initializing output

    // inputting the lines form reactions.txt individually to iReactions
    firstRXNline = 100;

    totLines = 0;

    std::ifstream InData;
    InData.open( inFilename.c_str() );

    if (!InData.is_open() ){std::cout << "ERROR - reactions class couldn't open input reactionrs" << std::endl;}

    std::string rxn;

    while( std::getline(InData, rxn))
    {

        totLines++;
        if (rxn[0] == '-') { firstRXNline = totLines +1; }      // making sure it reads before the template line

        if (totLines >= firstRXNline)
        {
            iReactions.push_back(rxn);
        }
    }

    InData.close();
};

void reaction::load_carbons(int csize, std::string carbs[])
{
    vCarbSize = csize;
// populating the local carbons vector
    for (int i = 0; i < csize; i++)
    {
        carbons.push_back( carbs[i] );
    }

// TODO comment out once done
    for (int n = 0; n < iReactions.size(); n++)
    {
  //      std::cout << "\nReaction: " << n << ":::\n";
        set_info(n);

        check_tags();
    }

}

reaction::~reaction(){}

void reaction::set_info(int rxnIndex)
{
    currentRxnIndex = rxnIndex;

// need to reset requirements and blocks for each reaction
    freqs.clear();
    fblocks.clear();
    rreqs.clear();
    rblocks.clear();

    std::string rxn = iReactions.at(currentRxnIndex);      // getting reaction from the inputted reactions vector

    reacName = rxn.substr(0, rxn.find(';') );       // most of this will rely on the properly syntax-ed reaction input text file. I didn't want to input validate for every little thing so I left a template in their for me to remember

    rxn = rxn.erase(0, rxn.find(';')+1 );

    strlogicals = rxn.substr(0, rxn.find(';') );        // this is the middle section ('name; logicals; description') that tells me what indicates the reaction does or does not take place

    std::string lowmidsec = strlogicals.substr(0, strlogicals.find("->")-1 );
    std::string upmidsec = strlogicals.substr(strlogicals.find("->")+3, strlogicals.length()-1);

    while (ispunct(lowmidsec[0]) || lowmidsec[0] == ' ')
    {
        lowmidsec.erase(0, 1);
    }

    while (ispunct(upmidsec[0]) || upmidsec[0] == ' ')
    {
        upmidsec.erase(0, 1);
    }
/*
    I created a funky way to get the requirements and blocks.
    The algorithm reads the input left to right and records the characters to a string whether if recReqs (recording requirements) or recBlocks is true.
    This string is this shipped out to its appropriate list based off whether it is a requirement or a block, and whether or not it is going forward or reverse
*/
    bool recReqs = true;
    bool recBlock = false;



    std::string reqstr = "";
    std::string blostr = "";

    bool forwrd;

    for (int i = 0; i < strlogicals.length(); i++)
    {
        if (i < strlogicals.find('>')) {forwrd = true;}
        else {forwrd = false;}


        char let = strlogicals[i];

        if (recReqs)
        {
            if (isalpha(let) ) { reqstr += let;}
            else if (forwrd) {freqs.push_back(reqstr); reqstr = "";}
            else {rreqs.push_back(reqstr); reqstr = "";}
        }

        if (recBlock)
        {
            if (isalpha(let) ) { blostr += let;}
            else if (forwrd) {fblocks.push_back(reqstr); reqstr = "";}
            else {rblocks.push_back(reqstr); reqstr = "";}
        }

        if (let == '!' ) {recReqs = false; recBlock = true;}
        else if ( let == '(')
        {
            if ( !recBlock ) {recReqs = true; }
            else {recReqs = false;}
        }
        else if ( ispunct(let) ) {recReqs = false; recBlock = false;}

    }

    rxn = rxn.erase(0, rxn.find(';')+1);
    description = rxn.substr(0, rxn.length());

    while (description[0] == ' '){ description.erase(0, 1); }

//    std::cout << reacName << "**" << strlogicals << "**" << description << "**";

// Erasing all empty reqs that slipped through the req/block implementation
    for (int i = 0; i < freqs.size(); i++)
    {
        if (freqs.at(i) == "") {freqs.erase(freqs.begin()+i); i--;}
    }

    for (int i = 0; i < rreqs.size(); i++)
    {
        if (rreqs.at(i) == "") {rreqs.erase(rreqs.begin()+i); i--;}
    }

    for (int i = 0; i < fblocks.size(); i++)
    {
        if (fblocks.at(i) == "") {fblocks.erase(fblocks.begin()+i); i--;}
    }

    for (int i = 0; i < rblocks.size(); i++)
    {
        if (rblocks.at(i) == "") {rblocks.erase(rblocks.begin()+i); i--;}
    }
// Making sure all the requirements and blocks were correct:
/*
    std::cout << "F Req start:\n";

    for (int i = 0; i < freqs.size(); i++)
    {
        std::cout << "<<<" << freqs.at(i) << ">>>";
    }

    std::cout << "F Req end:\n";

    std::cout << "R Req start:\n";

    for (int i = 0; i < rreqs.size(); i++)
    {
        std::cout << "<<<" << rreqs.at(i) << ">>>";
    }

    std::cout << "R Req end:\n";
//             ///                       ////
    std::cout << "F Block start:\n";

    for (int i = 0; i < fblocks.size(); i++)
    {
        std::cout << "<<<" << fblocks.at(i) << ">>>";
    }

    std::cout << "F Block end:\n";

    std::cout << "R Block start:\n";

    for (int i = 0; i < rblocks.size(); i++)
    {
        std::cout << "<<<" << rblocks.at(i) << ">>>";
    }

    std::cout << "R Block end:\n";
*/
    return;
}

void reaction::check_tags()
{
    for (int i = 1; i < vCarbSize; i++)         // carbons start at 1 not zero
    {
        bool isValidForward = true;

        for (int j = 0; j < fblocks.size(); j++)
        {
            std::string tmpstr = fblocks.at(j);
            if (carbons.at(i).find(tmpstr) != std::string::npos) { isValidForward = false; /*std::cout << "<fblock:" << tmpstr << ">";*/}
        }

        if (isValidForward)
        {

        bool hasAllFReqs = true;

            for (int k = 0; k < freqs.size(); k++)
            {
                std::string tmpstr = freqs.at(k);
                if (carbons.at(i).find(tmpstr) == std::string::npos) { hasAllFReqs = false;}
             //   else { std::cout << "<freq:" << tmpstr << ">"; }
            }
// std::cout << "Has all Fres:" << hasAllFReqs << std::endl;
        if (hasAllFReqs) { valReactions.push_back(currentRxnIndex);/*std::cout << "HERE"; for (int i = 0; i < valReactions.size(); i++){std::cout << valReactions.at(i);}*/}

        }
    }
/*
Now we try all the reverse blocks and requirements
*/
    for (int i = 1; i < vCarbSize; i++)
    {
        bool isValidReverse = true;

        for (int j = 0; j < rblocks.size(); j++)
        {
            std::string tmpstr = rblocks.at(j);
            if (carbons.at(i).find(tmpstr) != std::string::npos) { isValidReverse = false; /*std::cout << "<rblock:" << tmpstr << ">";*/ }
        }

        if (isValidReverse)
        {

        bool hasAllRReqs = true;

            for (int k = 0; k < rreqs.size(); k++)
            {
                std::string tmpstr = rreqs.at(k);
                if (carbons.at(i).find(tmpstr) == std::string::npos) { hasAllRReqs = false;}
               // else { std::cout << "<rreq:" << tmpstr << ">"; }
            }
// std::cout << "Has all Rres:" << hasAllRReqs << std::endl;
        if (hasAllRReqs) { valReactions.push_back(currentRxnIndex);/* std::cout << "HERE"; for (int i = 0; i < valReactions.size(); i++){std::cout << valReactions.at(i);}*/}

        }
    }
    return;
}

void reaction::write_info()
{
// getting rid of valid reactions that appear twice or more

    std::vector <int> tempVec;


    for (int i = 0; i < valReactions.size(); i++)
    {
        bool isRepeat = false;

        for (int j = 0; j < tempVec.size(); j++)
        {
            if (tempVec.at(j) == valReactions.at(i) ){isRepeat = true;}
        }

        if (!isRepeat){tempVec.push_back( valReactions.at(i) );}
    }

    valReactions.clear();       // wiping valid reactions to get rid of repeats

  //  std::cout << "Val reactions: ";
    for (int k = 0; k < tempVec.size(); k++)
    {
        std::cout << tempVec.at(k);

        valReactions.push_back( tempVec.at(k) );
    }

 //   std::cout << std::endl;

// adding valid information all together

    for (int j = 0; j < valReactions.size(); j++)
    {
        set_info( valReactions.at(j) );
        output = output + "\n" + reacName + "\n" + strlogicals + "\n" + description + "\n ------------------------------------\n";
    }
// writing to output file

    std::ofstream DataOut;
    DataOut.open(outFilename.c_str());

    if ( !DataOut.is_open() ) {std::cout << "ERROR- could not write to output file" << std::endl;}

    DataOut << output;

    DataOut.close();

    return;
}

int reaction::get_totLines() {return totLines;}

int reaction::get_firstRXNline() {return firstRXNline;}

