#include <iostream>
#include <cctype>

using namespace std;

int main() {
  
  //declarations
  int choice;
  int points = 100;
  enum choiceNum {
    displayLeft = 1,
    displayRight = 2,
    guess = 3,
    change = 4,
    exit = 5
  };
  bool valid;
  string name;
  // Ask for their name and store it
  cout << "What is your name? " << endl;
  getline(cin, name);

  //making sure name is valid
  do{
    valid = true;
    for(int i = 0; i < name.length(); i++){
      if(!(isalpha(name[i])) && name[i] != ' '){
        valid = false;
      } 
    }
    if(!valid){
      // edited to make sure the user knows it can only be letters and spaces. Then record new name.
      cout << "Name can only contain letters and spaces." << endl << "Please enter a valid name: " << endl;
      getline(cin, name);
      valid = false;
    }
      // check for name length and set the first  letter to uppercase. change senior to Sr. and junior to Jr. Set valid to true. Do while until correct name is implemented.
      else{
        for(int x = 0; x < name.length(); x++){
          name[x] = tolower(name[x]);
        }
        name[0] = toupper(name[0]);
        if(name.find("senior") != string::npos){
          name.replace(name.find("senior"), 6, "Sr");     
        }
        if(name.find("junior") != string::npos){
          name.replace(name.find("junior"), 6, "Jr");     
        }
        int space = name.find(' ');
        name[space + 1] = toupper(name[space + 1]);
        cout << "Welcome " << name << endl;
        valid = true;
      }
    }
  while(!valid);

  //getting random numbers for left and right and keeping left less than right from 150-250 inclusive.
  srand(time(NULL));
  int left = rand() % 101 + 150;
  int right = rand() % 101 + 150;
  while(left >= right){
   left = rand() % 101 + 150;
  }
  //initializing displaying numbers that the user sees
  int num1 = -1;
  int num2 = -1;
  cout << num1 << "  " << num2 << endl << endl;

  //the game loop
  
  //the menu
  do {
  cout << "Menu: " << endl;
  cout << "1. Display Left Number" << endl;
  cout << "2. Display Right Number" << endl;
  cout << "3. Guess a number in between" << endl;
  cout << "4. Change numbers" << endl;
  cout << "5. Exit" << endl;
  cout << "What do you want to do? " << endl;
  cin >> choice;
  //making choice a valid input for the enum
  //making strings invalid
  bool isInt = true;
  if(isdigit(choice)){
   isInt = true;
    }
     else{
       cin.clear();
       cin.ignore();
       isInt = false;
       cout << "Invalid input. Please enter a number." << endl;
       cin >> choice;
       }
  choice = static_cast<choiceNum>(choice);
  cout << "Your choice: " << choice << endl;

    //switch case for game options
    switch (choice){
      //display the left number
      case displayLeft:
        //keeping user from seeing both numbers
        if(num1 == -1 && num2 == -1){
          num1 = left;
          cout << "You will only get one point for guessing correctly and lose ten points for guessing incorrectly, now." << endl;
          cout << num1 << "  " << num2 << endl;
        }
          //stop them from seeing both numbers
        else{
          cout << "You have already displayed the a number. You cannot display both" << endl;
          cout << num1 << "  " << num2 << endl;
        }
      break;
      //display the right number
      case displayRight:
        if(num2 == -1 && num1 == -1){
          num2 = right;
          cout << "You will only get one point for guessing correctly and lose ten points for guessing incorrectly, now." << endl;
          cout << num1 << "  " << num2 << endl;
        }
          //stop them from seeing both numbers
        else{
          cout << "You have already displayed the a number. You cannot display both" << endl;
          cout << num1 << "  " << num2 << endl;
        }
      break;
      // let them guess the number
      case guess:
        int guess;
        cout << "Enter your guess: " << endl;
        cin >> guess;
        //Checking to make sure it's a correct guess. If true add points.
        if(guess >= left && guess <= right){
          cout << "You guessed correctly!" << endl;
          // check if they got a cheat on one of the numbers if not add 5 and print out points.
          if(num1 == -1 && num2 == -1){
            points += 5;
            cout << "You get five points!" << endl;
            cout << "Your total points: " << points << endl;
          }
          // if they used a cheat then only add 1 point and print out total points.
          else{
            points += 1;
            cout << "You get one points!" << endl;
            cout << "Your total points: " << points << endl;
          }
        }
          // tell them they missed and deduct points accordingly and printout the total points.
        else{
          cout << "You guessed incorrectly!" << endl;
          if(num1 == -1 && num2 == -1){
            points -= 5;
            cout << "You lose five points" << endl;
            cout << "Your total points: " << points << endl;
          }
          else{
            points -= 10;
            cout << "You lose ten points!" << endl;
            cout << "Your total points: " << points << endl;
          }
        }
      break;
      case change:
      //giving left and right new random numbers and keeping left below right
      left = rand() % 101 + 150;
      right = rand() % 101 + 150;
      while(left >= right){
        left = rand() % 101 + 150;
      }
      num1 = -1;
      num2 = -1;
      points -= 1;
      cout << "Your remaining points: " << points << endl;
      cout << "Generating new numbers..." << endl;
      cout << num1 << "  " << num2 << endl;
      break;
      // let them leave the game option and tell them their total points.
      case exit:
        cout << "Bye " << name << "!!!" << endl;
        cout << "Your final points balance is: " << points << endl;
      break;
      default:
      //in case user enters a number that is not an option
        cout << "Invalid choice. Press enter to continue" << endl;
      break;
    }
  }
  //breaks the loop when user enters 5 or points fall below 0
  while(choice != 5 && points >= 0);
  
  return 0;
}
