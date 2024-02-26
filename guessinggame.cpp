#include <cctype>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

int main() {
  // declarations
  int choice; //user input from menu
  int points = 100;
  enum choiceNum {
    displayLeft = 1,
    displayRight = 2,
    guess = 3,
    change = 4,
    exit = 5
  };
  bool validName;
  string name;
  // Ask for their name and store it
  cout << "What is your name? " << endl;
  getline(cin, name);

  // making sure name is valid
  do {
    validName = true;
    //every character in name must be a letter or space
    for (int i = 0; i < name.length(); i++) {
      if (!(isalpha(name[i])) && name[i] != ' ') {
        validName = false;
        break;
      }
    }
    if (!validName) {
      //getting user to reenter name if contain invalid characters
      cout << "Name can only contain letters and spaces." << endl;
      cout << "Please enter a valid name: " << endl;
      getline(cin, name);
      validName = false;
    }
    // adding uppercases where need be and including the name suffix
      else {
        //lowercase every character in name
        for (int x = 0; x < name.length(); x++) {
         name[x] = tolower(name[x]);
       }
        //uppercase first character
        name[0] = toupper(name[0]);
        //adding suffix
       if (name.find("senior") != string::npos) {
        name.replace(name.find("senior") - 1, 7, ", Sr");
       }
        //adding suffix
       if (name.find("junior") != string::npos) {
          name.replace(name.find("junior") - 1, 7, ", Jr");
       }
       //uppercase everywhere after space
       for(int y = 0; y < name.length(); y++){
        if(name[y] == ' ') {
           name[y + 1] = toupper(name[y + 1]);
         }
       }
       cout << "Welcome " << name << endl;
        //breaking loop if name is valid
        validName = true;
     }
   } while (!validName);

  // getting random numbers for left and right and keeping left less than right
  // from 150-250 inclusive.
  srand(time(NULL));
  int left = rand() % 101 + 150;
  int right = rand() % 101 + 150;
  while (left >= right) {
    left = rand() % 101 + 150;
  }
  
  // initializing display numbers that the user sees
  int num1 = -1;
  int num2 = -1;
  cout << num1 << "  " << num2 << endl << endl;
  
  // the game loop
  do {
    // the menu
    cout << "Menu: " << endl;
    cout << "1. Display Left Number" << endl;
    cout << "2. Display Right Number" << endl;
    cout << "3. Guess a number in between" << endl;
    cout << "4. Change numbers" << endl;
    cout << "5. Exit" << endl;
    cout << "What do you want to do? " << endl;
    
    //making choice fit neccesary parameters and clearing invalid inputs
    while (!(cin >> choice) || choice < 1 || choice > 5) {
      cin.clear();
      while (cin.get() != '\n');
      cout << "Invalid input. Please enter a number between 1 and 5." << endl;
    }
    
    //making choice valid for the enum
    choice = static_cast<choiceNum>(choice);
    cout << "Your choice: " << choice << endl;
    
    // switch case for game options
    switch (choice) {
    // display the left number
    case displayLeft:
      if (num1 == -1 && num2 == -1) {
        num1 = left;
        cout << "You will only get one point for guessing correctly and lose "
                "ten points for guessing incorrectly, now."
             << endl;
        cout << num1 << "  " << num2 << endl;
      }
      // stop them from seeing both numbers
        else {
          cout << "You have already displayed the a number. You cannot display both" << endl;
          cout << num1 << "  " << num2 << endl;
        }
      break;
    // display the right number
    case displayRight:
      if (num2 == -1 && num1 == -1) {
        num2 = right;
        cout << "You will only get one point for guessing correctly and lose "
                "ten points for guessing incorrectly, now."
             << endl;
        cout << num1 << "  " << num2 << endl;
      }
      // stop them from seeing both numbers
        else {
         cout << "You have already displayed the a number. You cannot display both" << endl;
         cout << num1 << "  " << num2 << endl;
        } 
      break;
    // let them guess the number
    case guess:
      int guess;
      cout << "Enter your guess: " << endl;
      cin >> guess;
      // Checking to make sure it's a correct guess. If true add points.
      if (guess >= left && guess <= right) {
        cout << "You guessed correctly!" << endl;
        // adding points if user did not display either number and printing total points
        if (num1 == -1 && num2 == -1) {
          points += 5;
          cout << "You get five points!" << endl;
          cout << "Your total points: " << points << endl;
        }
          // adding a point if user did display either number and printing total points
          else {
           points += 1;
           cout << "You get one points!" << endl;
           cout << "Your total points: " << points << endl;
          }
      }
      // user guessed incorrectly
        else {
          cout << "You guessed incorrectly!" << endl;
          // subtracting points if user did not display either number and printing total points
          if (num1 == -1 && num2 == -1) {
            points -= 5;
            cout << "You lose five points" << endl;
           cout << "Your total points: " << points << endl;
          } 
            else {
            // subtracting 10 points if user did display either number and printing total points
            points -= 10;
            cout << "You lose ten points!" << endl;
            cout << "Your total points: " << points << endl;
           }
        }
      break;
    case change:
      // giving left and right new random numbers and keeping left below right
      left = rand() % 101 + 150;
      right = rand() % 101 + 150;
      while (left >= right) {
        left = rand() % 101 + 150;
      } 
      //reassigning num1 and num2 to -1 to reset them
      num1 = -1;
      num2 = -1;
      points -= 1;
      cout << "Your remaining points: " << points << endl;
      cout << "Generating new numbers..." << endl;
      cout << num1 << "  " << num2 << endl;
      break;
    // let them leave the game  and tell them their total points.
    case exit:
      cout << "Bye " << name << "!!!" << endl;
      cout << "Your final points balance is: " << points << endl;
      break;
    default:
      // in case user input is not an option
      cout << "Invalid choice. Press enter to continue" << endl;
      break;
    }
  } while (choice != 5 && points >= 0); //breaks the loop if user exits or runs out of points

return 0;
}
