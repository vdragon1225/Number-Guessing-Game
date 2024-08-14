#include <iostream>
#include <string>
#include <cstdlib> // For rand()
#include <ctime> // For time()
#include <climits> // For INT_MAX
#include <chrono> // For high-resolution clock and duration

using namespace std;
using namespace std::chrono;

// Function prototypes
void guessNumber(int number, int maxGuesses, int& lowestGuesses, duration<double>& shortestTime, int& score);

int main() {
    // Variable declarations
    int randomNumber; // Declare a variable to store the random number
    srand(time(0)); // Seed the random number generator
    int userGuess; // Declare a variable to store the user's guess
    string difficulty; // Declare a variable to store the difficulty level
    char playAgain; // Declare a variable to store if the user wants to play again
    int score = 0; // User score
    int maxGuesses;
    int lowestGuesses = INT_MAX; // Initialize with the maximum int value
    duration<double> shortestTime = duration<double>::max();
    
    
    
    // Main game loop
    do {
        // Check if valid difficulty input
        bool validDifficulty = false;

        while(!validDifficulty) {
            // Determine the difficulty
            cout << "Enter difficulty level (easy, medium, hard): ";
            cin >> difficulty;

            if (difficulty == "easy") { // Random number between 1 and 10
                validDifficulty = true;
                randomNumber = rand() % 10 + 1;
                cout << endl; // Break line
                cout << "Guess the number between 1 and 10!" << endl;
                maxGuesses = 5;
                cout << "You have " << maxGuesses << " guesses." << endl;
            } else if (difficulty == "medium") { // Random number between 1 and 100
                validDifficulty = true;
                randomNumber = rand() % 100 + 1;
                cout << endl; // Break line
                cout << "Guess the number between 1 and 100!" << endl;
                maxGuesses = 7;
                cout << "You have " << maxGuesses << " guesses." << endl;
            } else if (difficulty == "hard") { // Random number between 1 and 1000
                validDifficulty = true;
                randomNumber = rand() % 1000 + 1;
                cout << endl; // Break line
                cout << "Guess the number between 1 and 1000!" << endl;
                maxGuesses = 10;
                cout << "You have " << maxGuesses << " guesses." << endl;
            } else { // Invalid level
                cout << endl; // Break line
                cout << "Invalid difficulty level!" << endl;
            }
        }

        // Proceed to guessing
        guessNumber(randomNumber, maxGuesses, lowestGuesses, shortestTime, score);
        
        // Ask user if they want to play again
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }
    while(playAgain == 'y' || playAgain == 'Y');
    
    
    cout << endl; // break line
    cout << "Results:" << endl;
    cout << "Final Score: " << score << endl; // Output the final score
    if (shortestTime.count() == std::numeric_limits<double>::max()) {
        cout << "No games won." << endl;
    } else {
        cout << "Shortest time: " << shortestTime.count() << " seconds." << endl;
    }
    
    // Output game with lowest guesses
    if (lowestGuesses != INT_MAX) {
        cout << "Your best game took " << lowestGuesses << " guesses." << endl;
    } else {
        cout << "No games won." << endl;
    }

    return 0;
}

void guessNumber(int number, int maxGuesses, int& lowestGuesses, duration<double>& shortestTime, int& score) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::seconds;
    
    int userGuess;
    int guessCount = 0;

    auto startTime = high_resolution_clock::now(); // Start the timer

    do {
        cout << "Enter your guess: ";
        cin >> userGuess;
        
        if (cin.fail()) { // Check if the input was not an integer
            cin.clear(); // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Ignore the rest of the input line
            cout << "\nPlease enter a valid number!" << endl;
            continue; // Skip the rest of the loop and prompt for input again
        }
        guessCount++; // Increase guessCount
        
        if (userGuess == number) {
            auto endTime = high_resolution_clock::now(); // Stop the timer
            auto timeTaken = duration_cast<duration<double>>(endTime - startTime);
            cout << "\nYou guessed correctly!" << endl;
            cout << "Time taken: " << timeTaken.count() << " seconds." << endl;
            
            // Find shortest time
            if(timeTaken < shortestTime) {
                shortestTime = timeTaken;
            }
            
            // Find lowestGuesses
            if (guessCount < lowestGuesses) {
                lowestGuesses = guessCount;
            }
            
            score++;
            cout << "Score: " << score << "\t" << "Number of Guesses: " << guessCount << endl; // Output user's current score and number of guesses
            break; // Exit loop if guessed correctly
        } else if (userGuess > number) {
            cout << "\nTry a lower number!" << endl;
        } else if (userGuess < number) {
            cout << "\nTry a higher number!" << endl;
        } else {
            cout << "\nTry again!" << endl;
        }

        int guessesLeft = maxGuesses - guessCount;
        cout << "You have " << guessesLeft << " guesses left." << endl;
        cout << endl; // Break line

        if (guessCount == maxGuesses) {
            cout << "You've run out of guesses. The number was " << number << "." << endl;
            break; // Exit loop if max number of guesses reached
        }
    }
    while(true); // Loop indefinitely until break is called

}