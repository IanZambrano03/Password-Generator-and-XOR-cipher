#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

std::set<std::string> wordsInPass;
std::string RANDOMLYGENPASSWORD;

void list()
{
    while(true)
    {
        std::string word;
        std::cout << "Please enter the word you want to use in your password: \n";
        std::cin >> word;
        wordsInPass.insert(word);

        std::string choice;
        std::cout << "Would you like to add another word? (yes/no):\n";
        std::cin >> choice;

        if (choice == "no")
        {
            break;
        } else if (choice != "yes")
        {
            std::cout << "Please enter a valid choice\n";
            break;
        }
    }
}

void PASSWORDGENERATOR()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    const char* numbers[] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20",};

    int index = std::rand() % 20;
    const char* randomNumber = numbers[index];


    const char* Char[] = {"@", "$", "^" , "&", "!"};
    int index1 = std::rand() % 5;
    const char* randomChar = Char[index1];

    auto it = wordsInPass.begin();
    std::advance(it, std::rand() % wordsInPass.size());
    std::string randomWord = *it;

    RANDOMLYGENPASSWORD = randomChar + randomWord + randomNumber;

    std::cout << "Your generated password is: " << RANDOMLYGENPASSWORD << "\n";
}

void xor_CIPHER(const std::string& key)
{

    std::vector<uint8_t> keyBytes(key.begin(), key.end());

    std::string extendedKey;
    extendedKey.reserve(RANDOMLYGENPASSWORD.size());


    while (extendedKey.size() < RANDOMLYGENPASSWORD.size()) {
        extendedKey.insert(extendedKey.end(), keyBytes.begin(), keyBytes.end());
    }


    extendedKey.resize(RANDOMLYGENPASSWORD.size());

    std::string result;
    for (size_t i = 0; i < RANDOMLYGENPASSWORD.size(); i++) {
        result += static_cast<char>(RANDOMLYGENPASSWORD[i] ^ extendedKey[i]);
    }

    std::cout << "Your encrypted password is: " << result << "\n";
}

int main()
{
    std::cout << "Hello welcome to your personal password generator! \n";
    std::cout << "------------------------------------------------- \n";

    std::cout << "There is some criteria your password will follow. Your password will have one number from 0-9, and one special character. It will use a word you wish to be implemented into the password. \n";

   list();

    std::cout << "\nWords added to your password set:\n";
    for (const auto& word : wordsInPass) {
        std::cout << word << "\n";
    }

    PASSWORDGENERATOR();

    while(true)
    {
        std::string choice2;
        std::cout << "You know have your own personal password. Now for another level of security would you like to cipher your password? (yes/no):";
        std::cin >> choice2;

        if(choice2 == "yes")
        {
            std::string key;
            std::cout << "Please enter key for encryption:\n";
            std::cin >> key;
            xor_CIPHER(key);
        } else if(choice2 == "no")
        {
            std::cout << "Enjoy your new password!\n";
            break;
        } else
        {
            std::cout << "Please enter a valid choice\n";
        }
    }


    return 0;
}
