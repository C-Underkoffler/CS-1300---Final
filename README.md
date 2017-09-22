# Final Project for CS 1300


### General Comments
This project was my final project for my CS-1 course at CU Boulder.
My Professor was Dr. Knox and my TA was Erik Holbroock (you might see their names in comments in the code).

I recommend reading through "CS_Project_Carl_Underkoffler.pdf" if you want a better understanding of the project. This will give a more in depth look at the classes I made and how the program is structured. In short: the idea is to input a compound's name and it will spit back to you valid reactions for that compound.

### Running the Program
Right now, the program runs with one of the test cases. To change this, comment out the test case at the top of project_1_main.cpp, and commnt in the call for the getInput() function. This should be located towards the very top of int main(){}.

When manually entering compounds, enter the name of the compound that you're interested in per my naming guidelines (should be explained in the actual write up). Keep in mind, active groups must be in the valid tags text file and implemented in the reaction requirements text file in order for it to work.

### Chemistry Grievances
If you have any knowledge of Chemistry you may be confused by my oversimplification or wrong chemistry especially in the reaction requirements (shown in "reactions.txt"). I have no excuse other than I was fighting to get this finished on time, I only intended this to be seen by CS faculty, and proper Chemistry wasn't terribly important to demonstrating the program could perform the task at hand.

Also, if you're familiar with chemistry, (since you realize this program actually does very little) the major criticism is that just identifying the active groups on the compound is almost as useful as going through this program. The only nice thing about this program is the ability to find out how saturated or unsaturated the carbons are and being able to use that to determine what reactions will work. The general framework should allow someone to add slightly more useful functionality though.

Also, there are a couple of little features that were never finished that got left in. Most notably is the distinction between alkanes, alkenes, and alkynes in the backbone class. The backbone class will accept an alkene or alkyne but nothing is done with that information. For a quick fix, 'ene' and 'yne' couuld be added to the list of valid tags and then be used in the reaction requirements that way.

### Programming Grievances
This project was string hell for me. I probably went about the handling of strings very wrong but I tried my best with what I knew at the time. Going back, this is one of the first things I would change, especially the handling of the inputted compound name. The challenge was how to unpack the compounds name and repack it using a different primary backbone (a result of me messing with the naming system). I realized after the fact I should have done it differently but had no reason to go back and fix it.
