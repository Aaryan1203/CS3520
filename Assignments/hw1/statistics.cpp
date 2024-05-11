#include <iostream>
#include <string>
#include <cctype> // needed for isalpha
using namespace std;

// After given a paragraph, this program will give statistics about the 
// total number of words, vowels, consonents, words with two vowels, and words with 
// punctuation marks. It will then ask for a number and will return the number of words
// that are smaller in length to the number. It will then randomly pick a number between 3 and 9
// and do the same thing
int main() {
    // part 1

    // the paragraph the user inputs
    string paragraph;

    // final values of required statistics
    int total_words = 0;
    int num_vowels = 0; 
    int num_consonants = 0;
    int words_with_two_vowel = 0;
    int words_with_punctuation_marks = 0;

    // valid vowels and punctuation marks
    string vowels = "aeiouAEIOU";
    string punctuation_marks = "!.,;“‘?$";

    cout << "Write me a paragraph and I will give you statistics for it: ";
    getline(cin, paragraph);
    cout << "The paragraph you have written is: " << paragraph << endl;

    int i = 0;
    while (i < paragraph.length()) {
        int vowels_in_current_word = 0;
        bool punctuation_in_word = false;
        // calculating the statistics of each word in the paragraph
        while (i < paragraph.length() && paragraph[i] != ' ') {
            if (vowels.find(paragraph[i]) != string::npos) {
                num_vowels++;
                vowels_in_current_word++;
            }
            else if (isalpha(paragraph[i])) {
                num_consonants++;
            } else {
                punctuation_in_word = true;
            }
            i++;
        }
        
        // incrementing final statistics once the end of the word is reached
        if (i > 0) {
            total_words++;
            if (vowels_in_current_word == 2) {
                words_with_two_vowel++;
            }
            if (punctuation_in_word) {
                words_with_punctuation_marks++;
            }
        }

        // skipping all extra white spaces
        while (i < paragraph.length() && (paragraph[i] == ' ')) {
            i++;
        }
    }

    // printing out statistics
    cout << "Total words: " << total_words << endl;
    cout << "Number of vowels: " << num_vowels << endl;
    cout << "Number of consonants: " << num_consonants << endl;
    cout << "Number of words with two vowels: " << words_with_two_vowel << endl;
    cout << "Number of words with punctuation marks: " << words_with_punctuation_marks << endl << "\n";


    // part 2

    int threshold = 0;
    int words_smaller_than_threshold = 0;
    cout << "Enter a number (I will return all the words with a length less than or equal to it): ";
    cin >> threshold;

    int j = 0;
    while (j < paragraph.length()) {
        // skips leading spaces and punctuation marks
        while (j < paragraph.length() && punctuation_marks.find(paragraph[j]) != string::npos || paragraph[j] == ' ') {
            j++;
        }

        // counts the number of letters in each word not including punctuation marks
        int letters_in_word = 0;
        while (j < paragraph.length() && paragraph[j] != ' ') {
            if (punctuation_marks.find(paragraph[j]) == string::npos) {
                letters_in_word++;
            }
            j++;
        }

        // increments statistics if number of letters is less than threshold
        if (letters_in_word <= threshold) {
            words_smaller_than_threshold++;
        }
    }

    // prints out statistics
    cout << "Words with a length smaller than or equal to " << threshold << ": " << words_smaller_than_threshold << endl << endl;


    // part 3

    // random number from 3-9 inclusive
    int random_threshold = 3 + (rand() % 7);
    int words_smaller_than_random_threshold = 0;

    cout << "The random threshold is: " << random_threshold << endl;

    int k = 0;
    while (k < paragraph.length()) {
        // skips leading spaces
        while (k < paragraph.length() && paragraph[k] == ' ') {
            k++;
        }

        // counts the number of letters/punctuation marks in each word
        int characters_in_word = 0;
        while (k < paragraph.length() && paragraph[k] != ' ') {
            characters_in_word++;
            k++;
        }

        // increments statistics if number of characters is less than random threshold
        if (characters_in_word <= random_threshold) {
            words_smaller_than_random_threshold++;
        }
    }

    // prints out statistics
    cout << "Words with a length smaller than or equal to " << random_threshold << ": " << words_smaller_than_random_threshold << endl;
}
