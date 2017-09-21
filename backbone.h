// Carl Underkoffler - Erik Holbrook - Project 1

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class backbone
{
    public:
        backbone(std::string, std::string);
        ~backbone();

        void set_bbName(std::string); //("compound", "tags file")

        void load_valTags(std::string);

        bool check_bbname();      // checks name is somewhat valid

        void set_bools();      // sets the bool identifiers of isChain, isAromatic, and isEther from name

        void set_bbSize();       // sets size from name

        void populate_carbons();        // populates group vector based off backbone

        void set_carbons();

        std::string get_bbName();

        std::string get_groups();

        int get_carbSize();

        void load_matrix(std::string[]);       // takes carbon position returns backbone groups at that location

    private:
        std::string groups;

        std::string bbName;

        std::vector <std::string> valTags;

        bool isEther;

        bool isChain;       // true if chain, false if cyclo

        bool isAromatic;        // true if benzene is backbone

        int bbSize;     // size of backbone

        std::vector <std::string> carbons;      // number of carbons in backbone will vary as will the number of groups

        int carbSize;

};
