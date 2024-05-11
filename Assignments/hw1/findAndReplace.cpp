#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// This function takes in two inputs from the user, a paragraph and a sentance that needs to be replaced
// it will find all of the occurances of the inputted sentance in the paragraph and replace them with the
// reversed version of the sentance
int main() {

    // initialize the inputted paragraph sentance and number of occurances
    string paragraph, sentance;
    int num_occurances = 0;
    vector <int> all_occurances;

    cout << "Type in a pragraph: ";
    getline(cin, paragraph);
    cout << "Type in a sentance you wish to be found (case sensitive): ";
    getline(cin, sentance);

    // looking for all occurances of the sentance in the paragraph
    int indexFoundAt = 0;
    while(indexFoundAt != string::npos) {
        // check if the given sentance appears in the paragraph
        indexFoundAt = paragraph.find(sentance, indexFoundAt);
        if (indexFoundAt != string::npos) {
            num_occurances++;
            cout << "Occurance " << num_occurances << " found at index: " << indexFoundAt << endl;
            all_occurances.push_back(indexFoundAt);
            indexFoundAt++;
        }
    }

    // reverses the origonal sentance inputted by the user
    string reverse_sentance = "";
    for (int i = sentance.length() - 1; i >= 0; i--) {
        reverse_sentance += sentance[i];
    }
    
    // creates a new paragraph with all of the occurances of the sentance replaced with the reversed version of the sentance
    string new_paragrah = paragraph;
    for (int i = 0; i < all_occurances.size(); i++) {
        new_paragrah.replace(all_occurances[i], sentance.length(), reverse_sentance);
    }

    cout << "Old paragraph: " << paragraph << endl;
    cout << "New paragraph: " << new_paragrah << endl;
}