#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

bool isSquare(int n) {
    int root = sqrt(n);
    return root * root == n;
}

int sumDigits(int n) {
    int sum = 0;
    while (n > 0) { sum += n % 10; n /= 10; }
    return sum;
}

void giveHint(int number, int guessNum, int totalGuesses, int minRange, int maxRange, int hintLevel) {
    vector<string> vagueHints;
    vector<string> directHints;

    // Vague Hints
    vagueHints.push_back(number % 2 == 0 ? "Hint: The number is even." : "Hint: The number is odd.");
    vagueHints.push_back(isPrime(number) ? "Hint: The number is prime." : "Hint: The number is not prime.");
    vagueHints.push_back(isSquare(number) ? "Hint: The number is a perfect square." : "Hint: The number is not a perfect square.");
    vagueHints.push_back("Hint: The number is a multiple of " + to_string((number % 5 == 0 ? 5 : 3)) + ".");
    // Divisible by list
    if(!isPrime(number)){
    string divHint = "Hint: The number is divisible by:";
    bool found = false;
    for (int i = 2; i <= 9; ++i) {
        if (number % i == 0) {
            divHint += " " + to_string(i);
            found = true;
        }
    }
    if (!found) divHint += " none between 2-9";
    vagueHints.push_back(divHint);
}

    // Direct Hints
    directHints.push_back(number <= (minRange + maxRange) / 2 ? "Hint: The number is in the bottom half of the range." : "Hint: The number is in the top half of the range.");

    directHints.push_back("Hint: The number has " + to_string(to_string(number).length()) + " digits.");
    
    string numberStr = to_string(number);
// Only if number > 10, push last digit hint
if (number > 10) {
    int lastDigit = numberStr.back() - '0';
    directHints.push_back("Hint: The last digit is " + string((lastDigit % 2 == 0) ? "even." : "odd."));
}
// Only if number > 10, push first digit hint
if (number > 10) {
    int firstDigit = numberStr.front() - '0';
    directHints.push_back("Hint: The first digit is " + string((firstDigit % 2 == 0) ? "even." : "odd."));
}
directHints.push_back("Hint: Sum of digits is " + to_string(sumDigits(number)) + ".");


// Show appropriate hint based on user choice (distinct per guess)
if (hintLevel == 1) {
    // Only vague hints, 5 distinct
    if (guessNum - 1 < vagueHints.size())
        cout << vagueHints[guessNum - 1] << endl;
} else if (hintLevel == 2) {
    // Only direct hints, 5 distinct
    if (guessNum - 1 < directHints.size())
        cout << directHints[guessNum - 1] << endl;
}
}


int main() {
    srand(time(0));
    int minVal, maxVal, difficulty;

    // Input range
    cout << "System will generate a random number between a user-defined range, you have to guess the number.\n";
    cout << "Enter minimum guess value (>= 10): ";
    cin >> minVal;
    if (minVal < 1) {
    cout << "Minimum value too low. Auto-setting to 10.\n";
    minVal = 1;
}

    cout << "Enter maximum guess value (>15,<= 1000): ";
    cin >> maxVal;
    if (maxVal >1000) {
    cout << "Maximum value too high. Auto-setting to 1000\n";
    minVal = 10;
}

    if (minVal >= maxVal || minVal < 1 || maxVal > 1000 || maxVal - minVal < 5) {
        cout << "Invalid range. Exiting.";
        return 0;
    }

    // Choose difficulty
    cout << "Choose hint level (1 = vague hints , 2 = direct hints): ";
    cin >> difficulty;
    if(difficulty < 1 || difficulty > 2) {
        cout << "Invalid difficulty level, Auto-setting to 2.";
        difficulty = 2;
    }



    // Generate number
    int target = minVal + rand() % (maxVal - minVal + 1);
    int guess, tries = 0;
    const int maxTries = 6;

    cout << "\nYou have 5 guesses to find the number!\n\n";

    while (tries < maxTries-1) {
        // Give hint
        giveHint(target, tries + 1, maxTries, minVal, maxVal, difficulty);

        cout << "Guess #" << (tries + 1) << ": ";
        cin >> guess;

        if (guess == target) {
            cout << " Correct! You guessed the number!\n";
            break;
        }

        // Closeness hint
        int diff = abs(guess - target);
        if (diff < 25) cout << " Very close!\n";
        else if (diff < 100) cout << " Close.\n";
        else cout << " Far away.\n";

        ++tries;
    }

    if (guess != target)
        cout << "\n Out of guesses. The number was: " << target << "\n";

    return 0;
}
