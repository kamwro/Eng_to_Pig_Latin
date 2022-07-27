#include <iostream>
#include <string>
#include <cstdlib>

using std::string; using std::cout; using std::cin; using std::endl;

class Alphabet {
    char vowels[13] = {'a', 'e', 'y', 'u', 'i', 'o',
                       'A', 'E', 'Y', 'U', 'I', 'O'};
    string Text;
    int Text_length;

public:
    void setText (){
        cout << "\nEnter your text in English: " <<endl;
        cin.clear(); cin.sync(); Text.clear(); // flushing the buffer and
        // making sure that nothing is written in the Text
        std::getline(cin, Text);
        Text_length = Text.size();
    };
    string getText()
    {
        return Text;
    };

    void prepareText(){ // cleaning text and setting text length
        for (int i = 0; i < Text_length; i++)
        {
            if (Text[i] == ',' || Text[i] == '.' || Text[i] == '?' || Text[i] == '!'
                || Text[i] == ';');
            else if (!(isalpha(Text[i])) && (!(isblank(Text[i])))) {
                Text.erase(i, 1);
                Text_length--;
                i--;
            }
        }

    };

    bool is_vowel(char c)
    {
        for (char vowel : vowels)
        {
            if (c == vowel) return true;
        }
        return false;
    };

};

class Vowels: public Alphabet
{
    string Text;
    int Convention_number;
public:
    string getWord (string text, int convention_number) {
        Text = text;
        Convention_number = convention_number;
        return add_at_the_end();
    };
    string add_at_the_end()
    {
        switch(Convention_number)
        {
            case 1: Text.append("yay"); break;
            case 2: Text.append("way"); break;
            case 3: Text.append("hay"); break;
            default: cout << "something went terribly wrong." <<endl; break;
        }
        return Text;
    };

};

class Consonants: public Alphabet
{
    string cluster;
    string Text;
    int Text_length;
public:
    string getWord(string text, string mode) {
        Text = text;
        Text_length = Text.size();
        cluster += Text[0];
        cluster += Text[1];
        if (mode == "one_consonant_one") return one_consonant_mode();
        return consonant_cluster_mode();
    };
    string one_consonant_mode()
    {
        Text += Text[0];
        Text.append("ay");
        Text.erase(0, 1);
        return Text;
    };

    string consonant_cluster_mode()
    {
        for (int i = 2; i < Text_length; i++)
        {
            if (is_vowel(Text[i])) break;
            else cluster += Text[i];
        }
        Text.append(cluster);
        Text.append("ay");
        Text.erase(0, cluster.length());
        return Text;
    };

};

class WordConverter {
    string Text;
public:
    string getWord(string word, string mode)
    {
        Text = word;
        bool first_letter_was_upper = isupper(Text[0]);
        if (first_letter_was_upper) Text[0] = tolower(Text[0]);
        if (mode == "vowel_one")
        {
            Vowels vow;
            int case_number = rand()%3+1; //1 - yay at the end, 2 - way, 3 - hay
            Text = vow.getWord(Text, case_number);
        }

        else if (mode == "one_consonant_one" || mode == "consonant_cluster_one")
        {
            Consonants cons;
            Text = cons.getWord(Text, mode);
        }

        else if (mode == "just_add_ay") {
            Text.append("ay"); return Text;
        }

        if (first_letter_was_upper) Text[0] = toupper(Text[0]);
        return Text;

    };
    string which_mode(string word) {
        Alphabet alpha;
        if (word.length() >= 2) {
            if (alpha.is_vowel(word[0])) return "vowel_one";
            else if (!(alpha.is_vowel(word[0])) && alpha.is_vowel(word[1])) return "one_consonant_one";
            else if (word.length() == 2) return "just_add_ay";
            else return "consonant_cluster_one";
        } else if (word.length() == 0) return "empty";
        else {
            if (alpha.is_vowel(word[0])) return "vowel_one";
            else return "just_add_ay";
        }
    };

};

class TextConverter {
    string newWord;
    string Text;
    string piggyText;
    string mode;
    int Text_length;
public:
    TextConverter()
    {
        convert_to_piggy_text();
    }
    void convert_to_piggy_text()
    {
        piggyText.clear();
        Alphabet alpha; WordConverter conv;
        alpha.setText();
        alpha.prepareText();
        Text = alpha.getText() + " ";
        Text_length = Text.length();
        while(!(std::empty(Text))) {
            char to_append = words_extraction(); mode = conv.which_mode(newWord);
            piggyText.append(conv.getWord(newWord, mode)); piggyText += to_append;
        }
        showText();
        repeat_the_program();
    };
    char words_extraction()
    {
        newWord.clear();
        for (int i = 0; i < Text_length; i++){
            if (Text[i] == ',' || Text[i] == '.' || Text[i] == '?' || Text[i] == '!'
                || Text[i] == ';' || isblank(Text[i])) {
                char mark = Text[i]; Text.erase(0, i+1); Text_length = Text.length();
                return mark;
            }
            newWord += Text[i];
        }
    };

    void showText()
    {
        cout << "\nYour english sentence in pig latin: \n";
        system("Color D");
        cout << piggyText << endl;
        system("Color 0");
    };

    void repeat_the_program()
    {
        system ("Color 1");
        cout << "\nWhat do you want to do (enter number): \n"
                "1. Convert another sentence\n"
                "2. Leave the program\n";
        int repeat_choice;
        cin >> repeat_choice;
        switch(repeat_choice)
        {
            case 1: convert_to_piggy_text();
            case 2: break;
            default: repeat_the_program();
        }

    };

};

void welcome()
{
    system ("Color 1");
    cout << "Hi! This is English to Pig Latin converter. For vowels "
            "it randomly chooses the convention (yay, way or hay at the end)."
            "\nEnjoy my program!\n" <<std::endl;
    system ("Color 0");
};

void goodbye ()
{
    system ("Color 1");
    cout << "\nThank you for using my program.\nPlease leave your feedback "
            "on my github in case you want to help me improve my programming "
            "skills:\n"
            "https://github.com/kamwro" <<std::endl;
    system ("Color 0");
};



int main() {
    welcome();
    TextConverter();
    goodbye();
    return 0;
}

