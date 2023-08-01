#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <ctime>

using std::string;
const int NUM = 3;
const string wordlist[NUM] = {"apiary", "beetle", "zippy"};

int main(void)
{
    using std::cout;
    using std::cin;
    using std::tolower;
    using std::endl;
    srand(time(0));

    char play;
    cout << "will you play a word game? <y/n>: ";
    cin >> play;
    play = tolower(play);
    while (play == 'y')             //开始猜某个随机单词
    {
        string target = wordlist[rand() % NUM];  //生成目标单词
        int length = target.length();            //获取目标长度
        string attempt(length, '-');             //猜测结果（一直更新）
        string badchars;                         //猜错的字符累积成串
        int guesses = 6;                         //剩余猜测次数

        cout << "Guess word: it has " << length <<" letters.\n"
             << "You get " << guesses << " wrong guesses.\n";
        cout << "Your word: " << attempt << endl;
        while (guesses > 0  &&  attempt != target)  //还能猜，而且还没猜对，则继续猜字符
        {
            char letter;
            cout << "Guess a letter: ";
            cin >> letter;

            if (attempt.find(letter) != string::npos  ||  badchars.find(letter) != string::npos)//如果猜过：猜对或猜错
            {
                cout << "Already guessed,try again.\n";
                continue;                          //猜下一轮，此时剩余猜测次数不减
            }

            int loc = target.find(letter);         //获取该字符第一个位置
            if (loc == string::npos)               //若单词不含该字符
            {
                cout << "Bad guess!\n";
                --guesses;                         //剩余猜测次数-1
                badchars += letter;                //猜错字符附加到串上
            }
            else                                   //若单词含该字符
            {
                cout << "Good gusses!\n";
                attempt[loc] = letter;             //该位置替换为已知字符
                loc = target.find(letter, loc + 1);//从该已知字符后面继续尝试获取该字符第二个位置
                while (loc != string::npos)        //若仍含该字符
                {
                    attempt[loc] = letter;         //继续替换
                    loc = target.find(letter, loc + 1);  //继续尝试获取下一个位置
                }
            }
            cout << "Your word: " << attempt << endl; //显示处理该字符后的猜测结果，此时该字符在串中的位置已知
            if (attempt != target)                 //若猜测结果还不是目标结果
            {
                if (badchars.length() > 0)         //有猜错的字符就显示
                    cout << "Bad choices: " << badchars << endl;
                cout << guesses <<" bad guesses left.\n";  //显示剩余猜测次数
            }
        }

        if (guesses > 0)                        //次数耗尽前猜对了
            cout << "That's right!\n";
        else                                    //次数耗尽，还没猜对
            cout << "Sorry, the word is " << target << ".\n"; //显示正确结果

        cout << "will you try another round? <y/n>: ";  //获取下轮游戏的单词
        cin >> play;
        play = tolower(play);
    }

    cout << "Bye.\n";
    return 0;
}