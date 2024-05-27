#include <vector>
#include <string>

using namespace std;

typedef struct slider slider_t;

/*
 * @brief This function loads the scores from a file.
 *
 * @param filename: The name of the file to load the scores from.
 *
 * @return vector<int>: The scores loaded from the file.
 */
vector<int> load_scores(const string& filename);

/*
 * @brief This function saves the scores to a file.
 *
 * @param scores: The scores to save.
 * @param filename: The name of the file to save the scores to.
 *
 * @return void
 */
void save_scores(const vector<int>& scores, const string& filename);

/*
 * @brief This function updates the top ten scores.
 *
 * @param scores: The top ten scores.
 * @param new_score: The new score to add.
 *
 * @return void
 */
void update_top_ten_scores(vector<int>& scores, int new_score);

/*
 * @brief This function saves the top ten scores.
 *
 * @param player_one: The first player.
 * @param player_two: The second player.
 *
 * @return void
 */
void save_top_ten_scores(slider_t *player_one, slider_t *player_two);
