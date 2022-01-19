#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include <vector>

auto swap(std::string text, int number/* 0-15 number of position key in the file "swap" */) ->std::string//swaps letter with other letter in pair from the key
{
    std::ifstream inFile;
    std::ostringstream out;
    std::vector<std::string> key;

    auto pairs = std::vector<std::string>{};
    inFile.open("../swap.txt", std::ios::in);


    if (!inFile) //checking if file exists
    {
        std::cerr << "Unable to open file\n";
        exit(1); // terminate with error
    }
    if(inFile.good()) {
        std::string tmp;
        while(inFile >> tmp) {
            key.push_back(tmp);




        }
    }
    auto chosen_key = std::string{key[number]};

    for (int i = 0; i< chosen_key.size(); i+=2){
        auto x = std::string{chosen_key[i]};
        x += chosen_key[i+1];
        pairs.push_back(x);

    }
    for (int i =0; i< text.size(); i++){
        for (int j = 0; j< pairs.size(); j++){
            auto sylable = pairs[j];
            if (std::toupper(text[i]) == sylable[0]){
                text[i] = sylable[1];

            }
            else if (std::toupper(text[i]) == sylable[1]){
                text[i] = sylable[0];

            }
            else {

                text[i] = toupper(text[i]);
            }

        }





    }
 out<<text;

    return out.str();
}



auto cipher_cesar(std::string text, int number) ->std::string //ciphers into cesar cipher
{
    std::ostringstream out;
    int numb = number;
    auto alphabet = std::string{"abcdefghijklmnopqrstuvwxyz"};
    while(numb>26){
        numb -= 26;
    }
    for (int i = 0; i < text.size(); i++) {
            for (int j = 0; j < alphabet.size(); j++) {
                if (text[i] == alphabet[j]) {
                    if (numb+j >=26){
                        out << alphabet[numb+j-26];

                    }
                    else {
                        out << alphabet[j + numb];
                    }
                }
            }
    }

 return out.str();

}

auto decipher_cesar(std::string text, int number) ->std::string //deciphers cesar cipher
{
    std::ostringstream out;
    int numb = number;
    auto alphabet = std::string{"abcdefghijklmnopqrstuvwxyz"};
    while(numb>26){
        numb -= 26;
    }


    for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < alphabet.size(); j++) {
            if (alphabet[j]==text[i]) {
                if(numb>j){
                    out << alphabet[alphabet.size() - numb + j];

                }
                else {
                    out << alphabet[j - numb];
                }
            }
        }
    }

    return out.str();

}





auto cipher_morse(std::string const text) ->std::string// codes text into morse
{
    std::ifstream inFile;
    std::ostringstream out;
    std::map<char, std::string> letters;

    inFile.open("../morse.txt", std::ios::in);
    if (!inFile) //checking if file exists
    {
        std::cerr << "Unable to open file\n";
        exit(1); // terminate with error
    }
    if(inFile.good()) {
        std::string tmp;
        while(inFile >> tmp) {
            letters.insert(std::make_pair(tmp[0], tmp.substr(1)));
        }
    }


    for (int i = 0; i < text.size(); i++) {
        out << letters[toupper(text[i])] <<"/";
    }
    inFile.close();
    out << "/";
    return out.str();
}

auto decipher_morse(std::string const text) ->std::string// deciphers text from morse code
{
    std::ifstream inFile;
    std::ostringstream out;
    std::map<char, std::string> letters;
    std::ostringstream container;
    inFile.open("../morse.txt", std::ios::in);
    if (!inFile) //checking if file exists
    {
        std::cerr << "Unable to open file\n";
        exit(1); // terminate with error
    }
    if(inFile.good()) {
        std::string tmp;
        while(inFile >> tmp) {
            letters.insert(std::make_pair(tmp[0], tmp.substr(1)));
        }
    }

    for (int i = 0; i < text.size(); i++) {


      if(text[i] == '/') {
          if( container.str() == " ") {
            out<<" ";
          }else {

              for (auto const &el: letters) { //gets cipher translated into a letter
                  if (el.second == container.str()) {
                      out << el.first;
                  }


              }
              container.str(" ");
          }

        }
      else{

            container<< text[i];

        }


    }
    inFile.close();

    return out.str();
}






int main() {
    std::cout<<swap("Hello there~!",12);
    return 0;
}
