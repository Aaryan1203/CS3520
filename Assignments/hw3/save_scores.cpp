#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "slider.hpp"
using namespace std;

vector<int> load_scores(const string &filename)
{
    ifstream file(filename);
    vector<int> scores;
    int score;

    // Skip the first line
    string first_line;
    getline(file, first_line);

    while (file >> score)
    {
        scores.push_back(score);
    }
    return scores;
}

void save_scores(const vector<int> &scores, const string &filename)
{
    ofstream file(filename);
    file << "These are the top ten highest total scores:" << endl;
    for (int score : scores)
    {
        file << score << endl;
    }
}

void update_top_ten_scores(vector<int> &scores, int new_score)
{
    scores.push_back(new_score);
    sort(scores.begin(), scores.end(), greater<int>()); // Sort in descending order
    if (scores.size() > 10)
    {
        scores.resize(10); // Keep only the top 10 scores
    }
}

void save_top_ten_scores(slider_t *player_one, slider_t *player_two)
{
    const string filename = "./saves/save_best_10.game";

    // Load current scores from the file
    vector<int> scores = load_scores(filename);

    // Update the scores with the new scores from player_one and player_two
    update_top_ten_scores(scores, player_one->total_score);
    update_top_ten_scores(scores, player_two->total_score);

    // Save the updated scores back to the file
    save_scores(scores, filename);
}
