#include <iostream>
#include <string>
#include <vector>

//Function mentioned in project description
int NumberOfCharactersOverlap(std::string
  const & first, std::string
  const & second) {

  int overlaping_chars = 0;
  std::string x = first, y = second;

  if (y.empty() || x.empty()) {
    return overlaping_chars;
  }

  if (y.find(x.at(x.length() - 1)) == std::string::npos) {
    return overlaping_chars;
  } else if (x.length() > y.length()) {

    while (x.length() != y.length()) {
      x.erase(0, 1);
    }

  } else if (x.length() < y.length()) {

    while (x.length() != y.length()) {
      y.erase(y.length() - 1, 1);
    }
  }

  while (x != y) {
    x.erase(0, 1);
    y.erase(y.length() - 1, 1);
  }

  overlaping_chars = x.length();

  return overlaping_chars;

}

//This Function Counts the number of words that a sentence has
int NumberOfWords(std::string sentence) {
  int counter = 0;

  for (auto x: sentence) {
    if (x == ' ') {
      counter++;
    }
  }

  return counter;
}

//This function splits a string into a vector
void SplitString(std::string s, std::vector < std::string > & v) {

  std::string temp = "";
  for (int i = 0; i < s.length(); ++i) {

    if (s.at(i) == ' ') {
      v.push_back(temp);
      temp = "";
    } else {
      temp.push_back(s.at(i));
    }

  }
  v.push_back(temp);

}

//This function sqeueezes a sentence once
std::string SqueezeOneSentence(std::vector < std::string > v) {
  std::string new_sentence = "", temp_word = "", temp_word2 = "";

  //iterate through a vector and compare each word with each other
  //depending on the comparison, squeeze them together
  for (int j = 0; j < v.size() - 1; j++) {

    temp_word = v.at(j + 1), temp_word2 = v.at(j);

    int num = NumberOfCharactersOverlap(temp_word2, temp_word);

    if (num > 0) {
      temp_word.erase(0, num);
      new_sentence = new_sentence + " " + temp_word2 + temp_word;
      j++;

    } else {
      new_sentence = new_sentence + " " + temp_word2;
    }

  }

  //add the rest of the sentence when the last two words are squeezable or not

  if (v.size() >= 3) {
    if (NumberOfCharactersOverlap(v.at(v.size() - 3), v.at(v.size() - 2)) > 0) {
      new_sentence = new_sentence + " " + v.at(v.size() - 1);
    } else {
      new_sentence = new_sentence + " " + temp_word;
    }
  } else {
    if (NumberOfCharactersOverlap(v.at(0), v.at(1)) == 0) {
      new_sentence = new_sentence + " " + temp_word;
    }
  }

  new_sentence.erase(0, 1);
  return new_sentence;
}

//Main function
int main() {
  std::string user_input = "";

  //while loop to get input until EOF
  while (getline(std::cin, user_input)) {

    if (user_input.empty()) {
      break;
    }

    //cannot squeeze one word so just output the same string
    else if (NumberOfWords(user_input) == 0) {
      std::cout << user_input << std::endl;
    } else {
      std::string new_sentence = "", sentence = user_input;
      std::vector < std::string > v;
      bool overlap = true;

      //while loop to keep squeezing the sentence 
      //until you can't squeeze it anymore or until it is one word
      while (overlap == true) {
        v.clear();
        SplitString(sentence, v);
        new_sentence = SqueezeOneSentence(v);

        if (new_sentence != sentence) {
          sentence = new_sentence;
          overlap = true;
        } else {
          overlap = false;
        }

        if (NumberOfWords(new_sentence) == 0) {
          break;
        }

      }

      std::cout << new_sentence << " " << std::endl;

    }
  }
  return 0;
}