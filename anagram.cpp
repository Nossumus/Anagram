/* The algorithm used in this app, propably not the best, but working and figured out by myself :)

1. Show to user purpose of this app
2. Ask for 3-letter word
3. If the word is valid move to next point, if not ask user again for 3-letter word
4. Ask user for full address of the file to read, if it is in the same file as .exe file, you can pass only name of the file ex. ListOfWords.txt
5. If address is invalid ask user for address again.
6. If address is valid, add one letter to 3-letter word move to check if there is any 4-letter word on in the list that have the same four letters and the same length
7. Iterate throw all the letters and words from the list
8. If there is any derivation, first check if it is unique, if didn't happend already 
8. If it is unique, add it to the vector, ex. ail+s=sail
9. Check which is the longest derivation in vector, ex. lets say that snali+e=aliens is the longest
10. Get first word from the longest derivation, ex. if the longest derivation is snali+e=aliens get the word "snail"
11. Check in the vector of all derivations, derivations that is shorter and contains word "snail"
12. Lets say that you find: nail+s=snail, now you will be looking for derivations which have word: "nail" and is shorter
13. You are doing this until you get to derivarion with your typed 3-letter word
14. You store all those derivation in the vector and print them.
15. Congrats, you have printed one of the longest chain of derivation

The method of checking if two words are anagrams used in this app
1. Check if both words are the same size, if yes procced next to the next point, if not they are not anagrams
2. Sort both words alphabetically
3. Check if every single letter of one word is equal to the letter on the same position in another word
4. If yes, they are anagrams, if not they, are not :(

*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

vector <string> fileContent;
vector <string> anagrams;
vector <string> longestChainVector;
vector <string> addedLetterVector;

vector <string> appendedChainToDisplay;
bool firstAnagramEver = true;


int howManyLettersHaveTheLongestWord;
bool anagramsFind = false;
bool firstWord = true;

string coreWord;
vector <string> coreWordVector;
int coreWordVectorPosition = 0;
int chainToDisplayPosition = 0;
vector <string> chainToDisplay;

void welcome(){

    cout << endl;
    cout << "----------------------------< ANAGRAM >----------------------------" << endl;
    cout << endl;
    cout << "This program is finding the longest derivation chain of anagrams, \nbased on 3-letter word typed by user and the list of words \npointed out by user" << endl;
    cout << endl;
}

bool checkIfTheChainIsUnique(string temp){

    for(auto e: chainToDisplay){
        if(e == temp){
            return false;
        }
    }
    return true;
}

string typeFileAddress() {

    string address;

    cout << "Please, enter the full file address: ";
    cin >> address;

    return address;
}

void readTheFile(string fileName){

    fstream file;
    
    file.open(fileName);
    while(file.fail()){
        cout << "Invalid address!" << endl << endl;
        file.open(typeFileAddress());
    }
    cout << "Address correct!" << endl << endl;
    
    string oneLine;

    while (getline(file, oneLine))
    {
        fileContent.push_back(oneLine);
    }
    
}

bool isCoreWordValid(){

string word;

cout << "Please enter the 3-letter word for your anagram: ";
cin >> word;

switch(word.length()){

    case 3:
    cout << "Word is valid!" << endl << endl;
    coreWord = word;
    return true;
    break;

    default:
    cout << "Word is invalid!" << endl << endl; 
    return false;
    break;
}
}

void checkTheCoreWord(){ 

    while(isCoreWordValid() == false);

}



void checkIfThereIsTheAnagram(string providedThreeLetterWord, string wordFromTheList){
    
    char addedLetter = 'a';
    bool isAnagramFlag = false;
    string originalWordFromTheList = wordFromTheList;

    coreWordVector.push_back(providedThreeLetterWord);
   
    do {

    int modifiedThreeLetterWordLength, wordFromTheListLength;
    string modifiedThreeLetterWord;

    //adding one letter to 3 letter word
    modifiedThreeLetterWord = providedThreeLetterWord + addedLetter;

    modifiedThreeLetterWordLength = modifiedThreeLetterWord.length();
    wordFromTheListLength = wordFromTheList.length();

    if(modifiedThreeLetterWordLength != wordFromTheListLength){
        addedLetter++;
        continue;
    } else {
        string unsortedModifiedThreeLetterWord = modifiedThreeLetterWord;

        sort(modifiedThreeLetterWord.begin(), modifiedThreeLetterWord.end());
        sort(wordFromTheList.begin(), wordFromTheList.end());

        for(int i = 0; i < modifiedThreeLetterWordLength; i++){

            if(modifiedThreeLetterWord[i] != wordFromTheList[i]){
                isAnagramFlag = false;
                break;
            } else {
                isAnagramFlag = true;
            }
        }
        if(isAnagramFlag == true){
        string temporary = coreWordVector[coreWordVectorPosition] + " + " + addedLetter + " = " + originalWordFromTheList + " ";
        coreWordVectorPosition++;
        
        if(firstWord == true){
            coreWordVector.push_back(originalWordFromTheList);
            chainToDisplay.push_back(temporary);
            chainToDisplayPosition++;
            firstWord = false;
        } else { 
        
        coreWordVector.push_back(originalWordFromTheList);
        if(checkIfTheChainIsUnique(temporary)){
            chainToDisplay.push_back(temporary);
            chainToDisplayPosition++;
        }
        }
        
        anagramsFind = true;

    }
    }
    
    addedLetter++;

} while(addedLetter <= 'z');
}




void checkAllDerivations(){

        for(auto e: fileContent){
        checkIfThereIsTheAnagram(coreWordVector[coreWordVectorPosition], e); 
    }


    if(anagramsFind == true){
        anagramsFind = false;
        checkAllDerivations();
        
    }
}

void findFirstAnagram(string providedThreeLetterWord, string wordFromTheList){

    char addedLetter = 'a';
    bool isThereAnagram = false;

    /* Save the original word from the list */
    string originalWordFromTheList = wordFromTheList;
    /* Save the core word*/
    coreWordVector.push_back(providedThreeLetterWord);

    /* Main loop */

    do {

        int modifiedThreeLetterWordLength, wordFromTheListLength;
        string modifiedThreeLetterWord;

        /* Add one letter to 3 letter word */
        modifiedThreeLetterWord = providedThreeLetterWord + addedLetter;

        modifiedThreeLetterWordLength = modifiedThreeLetterWord.length();
        wordFromTheListLength = wordFromTheList.length();

        /* If the length word from the list does not match 4 stop whole loop */
        if(modifiedThreeLetterWordLength != wordFromTheListLength){
        addedLetter++;
        continue;
        
        } else {
        
        /* Store unsorted 4 letter word */
        string unsortedModifiedThreeLetterWord = modifiedThreeLetterWord;
        
        /* Sort both words alphabetically */
        sort(modifiedThreeLetterWord.begin(), modifiedThreeLetterWord.end());
        sort(wordFromTheList.begin(), wordFromTheList.end());

        for(int i = 0; i < modifiedThreeLetterWordLength; i++){

            if(modifiedThreeLetterWord[i] != wordFromTheList[i]){
                isThereAnagram = false;
                break;
            } else {
                isThereAnagram = true;
            }
        }

        /* Check if program have found the anagram */
        if(isThereAnagram == false){
            /* There is no anagram so leave the main loop */
            addedLetter++;
            continue;
        } else if(isThereAnagram == true){

            string chain = providedThreeLetterWord + "+" + addedLetter + "=" + originalWordFromTheList;

            string addedLetterString = string(1, addedLetter); 
            
            /* Check if it is the first anagram ever */
            if(firstAnagramEver == true){
                
            /* Save the anagram from the list */
            anagrams.push_back(originalWordFromTheList);

            /* Save the added letter */
            addedLetterVector.push_back(addedLetterString);

            /* Save the chain to display */
            chainToDisplay.push_back(chain);

            /* Clear the flag */
            firstAnagramEver = false;

            } else {

                /* Check if it is unique */
                if(checkIfTheChainIsUnique(chain)){

                    /* Save the anagram from the list */
                    anagrams.push_back(originalWordFromTheList);

                    /* Save the added letter */
                    addedLetterVector.push_back(addedLetterString);
                    
                    /* Save the chain to display */
                    chainToDisplay.push_back(chain);
                }
            }
        }

        }

    /* Increment the letter */
    addedLetter++;

    } while(addedLetter <= 'z');

}



void findAndStoreLastElementOfTheLongestChain(){

    int lengthOfTheLongestChain = 0;
    int indexOfTheLongestChain;

    /* Find the longest chain */
    for(auto e: chainToDisplay){

        if(e.length() > lengthOfTheLongestChain){
            lengthOfTheLongestChain = e.length(); 
        }
    }
    /* Find all of the last elements of the longest chains, store them in vector */
    for(auto e: chainToDisplay){
        if(e.length() == lengthOfTheLongestChain){
            longestChainVector.push_back(e);
        }
    }
}



void getTheLongestChainVector(vector <string> chainVector){

        vector <string> chain;

        string temp = chainVector[0];
        size_t temp_pos = temp.find("=");
        temp_pos++;

        string lastWord = temp.substr(temp_pos);
        
        
        size_t temp_pos_first = temp.find("+");
        string theFirstWord = temp.substr(0,temp_pos_first);
        
        for(auto v: chainToDisplay){
            if((v.find(theFirstWord) != std::string::npos) && (v.length() < chainVector[0].length())){


                appendedChainToDisplay.push_back(v);
                chain.push_back(v);
                getTheLongestChainVector(chain);
                break;
            }
        }
    
}

template <typename T>
void reverse_print(const vector<T> & vec)
{
    // Iterate from end to start
    for (auto it = vec.rbegin(); it != vec.rend(); it++)
    {
        // Print each element
        cout << *it << " -> ";
    }
    
}


int main(int argc, char const *argv[])
{
    
    welcome();
    checkTheCoreWord();
    readTheFile(typeFileAddress());
    
    for(auto e: fileContent){
    findFirstAnagram(coreWord, e);
    }

    if(!anagrams.empty()){
    
    for(int i = 0; i < anagrams.size(); i++){

        for(auto e: fileContent){
        findFirstAnagram(anagrams[i], e);
    }
    }

    findAndStoreLastElementOfTheLongestChain();
    getTheLongestChainVector(longestChainVector);

    cout << "The longest derivation chain from 3-letter word: \"" + coreWord + "\" is: " << endl;
    reverse_print(appendedChainToDisplay);
    cout << longestChainVector[0] << endl << endl;
    system("pause");

    } else {
        cout << "There is no anagrams " << endl << endl;
        system("pause");
    }
    
    return 0;
}
