// Carl Underkoffler - Erik Holbrook - Project 1

#include <iostream>
#include <string>

#include <fstream>
#include <sstream>

#include <vector>

class reaction
{
    public:
        reaction(std::string, std::string);     // takes in file input name and output name
        ~reaction();

        void load_carbons(int, std::string[]);      // takes in file name of reaction inputs

        void set_reaction(int, std::string);       // takes reaction line num and output file name

        void set_info(int);     // takes reaction index and sets current reaction index, requirements, and blocks

        void check_tags();   //takes the current reaction index a

        void write_info();

        int get_totLines();
        int get_firstRXNline();

    private:
        int currentRxnIndex;

        std::vector <std::string> carbons;      // internal version of the carbons vector
        int vCarbSize;      //size of carbons vector

        std::string inFilename;
        std::string outFilename;

        std::vector <std::string> iReactions;       //inputted reactions

        std::vector <int> valReactions;     // the list of valid reactions as identified by check_tags()

// For use in the output:
        std::string reacName;       // name of reaction
        std::string description;    // long description of reaction
        std::string strlogicals;       // what makes the reaction work or not work
        std::string output;     // what gets printed

// All of the tags
        std::vector <std::string> fblocks;
        std::vector <std::string> freqs;
        std::vector <std::string> rblocks;
        std::vector <std::string> rreqs;
//

// Used in the constructor for creating the reaction index
        int firstRXNline;
        int totLines;
};
