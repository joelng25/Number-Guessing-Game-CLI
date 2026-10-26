#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include "game.h"
using namespace std;
using namespace game;
const char* HIGHSCORE_FILE="highscore.txt";
int readIntInRange(const string& prompt,int low,int high){string line;while(true){cout<<prompt;if(!getline(cin,line))exit(0);istringstream input(line);int value;char extra;if((input>>value)&&!(input>>extra)&&value>=low&&value<=high)return value;cout<<"Invalid input! Please enter a number between "<<low<<" and "<<high<<"."<<endl;}}
bool readYesNo(const string& prompt){string line;while(true){cout<<prompt;if(!getline(cin,line))exit(0);istringstream input(line);string word,extra;if((input>>word)&&!(input>>extra)){if(word=="y"||word=="Y")return true;if(word=="n"||word=="N")return false;}cout<<"Invalid choice! Please enter Y or N."<<endl;}}
Highscores loadHighscores(){Highscores scores;scores.fill(NO_SCORE);ifstream in(HIGHSCORE_FILE);for(int& s:scores){int value;if(!(in>>value)||value<=0)break;s=value;}return scores;}
void saveHighscores(const Highscores& scores){ofstream out(HIGHSCORE_FILE,ios::trunc);if(!out){cout<<"Warning: Could not save highscores."<<endl;return;}out<<scores[0]<<' '<<scores[1]<<' '<<scores[2];}
Difficulty chooseDifficulty(){cout<<"Please select the difficulty level:\n1. Easy (10 chances)\n2. Medium (5 chances)\n3. Hard (3 chances)\n";auto d=static_cast<Difficulty>(readIntInRange("Enter your choice: ",1,3));cout<<"Great! You have selected the "<<nameOf(d)<<" difficulty level."<<endl;return d;}
void playRound(mt19937& gen,Highscores& scores,int fixedAnswer=0){Difficulty d=chooseDifficulty();int answer=fixedAnswer?fixedAnswer:uniform_int_distribution<int>(MIN_NUM,MAX_NUM)(gen);int hints=0;auto start=chrono::steady_clock::now();cout<<"Let's start the game!"<<endl;
for(int attempt=1;attempt<=attemptsFor(d);++attempt){int guess=readIntInRange("Enter your guess: ",MIN_NUM,MAX_NUM);if(guess==answer){chrono::duration<double> elapsed=chrono::steady_clock::now()-start;cout<<"Congratulations! You guessed the correct number in "<<attempt<<(attempt==1?" attempt.":" attempts.")<<endl<<"Time taken: "<<elapsed.count()<<" seconds."<<endl;if(updateHighscore(scores,d,attempt)){saveHighscores(scores);cout<<"New highscore!"<<endl;}return;}cout<<"Incorrect! The number is "<<(guess<answer?"greater":"less")<<" than "<<guess<<"."<<endl;cout<<"You have "<<attemptsFor(d)-attempt<<" attempts left."<<endl;if(attempt<attemptsFor(d)&&readYesNo("Do you want a hint? (Y/N): ")){if(hints>=MAX_HINTS)cout<<"All hints have been used already!"<<endl;else{auto [low,high]=hintRange(answer,hints++);cout<<"The number is between "<<low<<" and "<<high<<"."<<endl;}}}
cout<<"Game over! The correct number was "<<answer<<"."<<endl;}
int main(int argc,char** argv){int answer=0;if(argc!=1){if(argc!=3||string(argv[1])!="--test-answer")return 2;istringstream input(argv[2]);char extra;if(!(input>>answer)||(input>>extra)||answer<MIN_NUM||answer>MAX_NUM)return 2;}cout<<"Welcome to the Number Guessing Game!"<<endl;mt19937 gen(random_device{}());auto scores=loadHighscores();do{playRound(gen,scores,answer);}while(readYesNo("Want to play again? (Y/N): "));return 0;}
