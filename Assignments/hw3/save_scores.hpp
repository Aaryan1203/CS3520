#include <vector>
#include <string>

vector<int> load_scores(const string& filename);
void save_scores(const vector<int>& scores, const string& filename);
void update_top_ten_scores(vector<int>& scores, int new_score);
void save_top_ten_scores(slider_t *player_one, slider_t *player_two);