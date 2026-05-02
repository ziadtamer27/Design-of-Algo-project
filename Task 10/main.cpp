#include <iostream>
#include <vector>
#include <string>
using namespace std;
// printing current board 
void current_board( string& coin,  vector<bool>& removed) {
    for (int i = 0; i < coin.length(); i++) {
        if (removed[i]) cout << "_";
        else  cout << coin[i] << " ";
    }
    cout << endl;
}
// the main logic of the puzzle
bool puzzel(string coin, vector<bool> removed, int coins_Left, vector<int>& sequence) {
    if (coins_Left == 0) return true;
    for (int i = 0; i < coin.length(); i++) {
        if (!removed[i] && coin[i] == 'H') {
            string next_coin = coin;
            vector<bool> remove_Next = removed;
            remove_Next[i] = true;
            if (i > 0 && !remove_Next[i - 1]) 
                next_coin[i - 1] = (next_coin[i - 1] == 'H' ? 'T' : 'H');
            if (i < coin.length() - 1 && !remove_Next[i + 1]) 
                next_coin[i + 1] = (next_coin[i + 1] == 'H' ? 'T' : 'H');
            sequence.push_back(i);
            if (puzzel(next_coin, remove_Next, coins_Left - 1, sequence)) 
                return true;
            sequence.pop_back();
        }
    }
    return false;
}
// main
int main() {
    string initial_Seq;
    cout << "Enter a sequence of coins: ";
    cin >> initial_Seq;
    int n = initial_Seq.length();
    vector<bool> removed(n, false);
    vector<int> sequence;
    cout << "Solving (" << initial_Seq << ")" << endl;
    if (puzzel(initial_Seq, removed, n, sequence)) {
        cout << "Solution....Sequence of coins to remove:" << endl;
        string currentCoins = initial_Seq;
        vector<bool> currentRemoved(n, false);
        current_board(currentCoins, currentRemoved);
        for (int index : sequence) {
            cout << "Removing coin at index " << index << endl;
            currentRemoved[index] = true;
            if (index > 0 && !currentRemoved[index - 1]) 
                currentCoins[index - 1] = (currentCoins[index - 1] == 'H' ? 'T' : 'H');
            if (index < n - 1 && !currentRemoved[index + 1]) 
                currentCoins[index + 1] = (currentCoins[index + 1] == 'H' ? 'T' : 'H');
            current_board(currentCoins, currentRemoved);
        }
    } else  
        cout << "No solution for this sequence." << endl;
    return 0;
}
