#include "dictionary.h"
int main()
{
	system("color 70");
	Dictionary d1;
	trienode*& temp = d1.getroot();
	string word = "", meaning = "", line;
	int choice;
	ifstream f1("Dictionary.txt");
	d1.loading();
	if (!f1.is_open()) {
		cerr << "error in opening Dictionary file";
		return 0;
	}
	//cout << "dictionary is loading";
	while (!f1.eof()) {
		getline(f1, line);
		istringstream s1(line);
		s1 >> word >> meaning;
		d1.insertingwordinadictionary(word, meaning);
	}
	f1.close();
	system("cls");
	do {
		choice = d1.getMenuChoice();
		//cin >> choice;
		system("cls");
		if (choice == 1) {
			word = "";
			meaning = "";
			word = d1.check(word, "word");
			if (word != "") {
				cout << "\n";
				if (d1.wordexistornot(word) == false) {
					while (meaning == "") {
						system("cls");
						meaning = d1.check(meaning, "meaning");
					}
					d1.addword(word, meaning);
					cout << "\nWord added successfully.\n";
					Sleep(1000);
					system("cls");
				}
				else {
					cout << "\nWord already exists";
					Sleep(1000);
					system("cls");
				}
			}
			else {
				cout << "\nyou have pressed enter without entering word";
				Sleep(1000);
				system("cls");
			}
		}
		else if (choice == 2) {
			string word1 = "";
			string temp = "";
			char ch;
			cout << "Enter 1 to 9 any number to select any suggestion from 1 to 9 and @ form 10th suggestion" << endl;
			while (true) {
				if (_kbhit()) {
					ch = _getch();
					if (temp != "" && ch >= '1' && ch <= '9' || ch == '@') {   //suggesstions selection
						if (d1.existance(ch) == true) {
							if (ch == '@') {
								word1 = d1.meaning1(10);
							}
							else {
								word1 = d1.meaning1(ch - '0');
							}
							d1.makingsuggestionsempty();
							cout << endl << "meaning of word= ";
							d1.searchword(word1);
							system("pause");
							system("cls");
							break;
						}
					}
					else if (ch == '\r') {
						if (temp != "") {
							break;
						}
						else {
							cout << "enter some word" << endl;
							Sleep(500);
							system("cls");
						}
					}
					else if (ch == '\b') {
						if (temp.length() > 1) {
							temp.pop_back();
							d1.makingsuggestionsempty();
							d1.wordsuggestion(temp);
							cout << "\r";
							cout << string(50, ' ');
							cout << "\r";
							cout << "Enter a temp: " << temp;
						}
						else if (temp == "") {
							break;
						}
						else {
							temp.pop_back();
							system("cls");
						}
					}
					else {
						if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
							if (ch >= 'A' && ch <= 'Z') {
								ch = tolower(ch);
							}
							system("cls");
							temp += ch;
							d1.makingsuggestionsempty();
							d1.wordsuggestion(temp);
							cout << "\r";
							cout << string(50, ' ');
							cout << "\r";
							cout << "Enter a temp: " << temp;
						}
					}
				}
			}
			if (ch == '\r' && temp != "") {
				d1.makingsuggestionsempty();
				cout << "meaning of word = ";
				d1.searchword(temp);
			}

		}
		else if (choice == 3) {
			word = "";
			cout << "Enter word to delete: ";
			word = d1.check(word, "word");
			if (word != "") {
				bool check = d1.deleteWordFromDictionary(word, temp);
				d1.deletefromfile(word);
				if (check == true) {
					cout << "word is deleted successfully" << endl;
				}
				else {
					cout << "\nword is not found in a dictionary";
				}
			}

		}
		else if (choice == 4) {
			word = "", meaning = "";
			cout << "\nEnter word you want to update:\n ";
			word = d1.check(word, "word");
			if (word != "") {
				if (d1.wordexistornot(word) == true) {
					while (meaning == "") {
						system("cls");
						meaning = d1.check(meaning, "meaning");
					}
					bool check = d1.updateword(word, meaning);
					if (check == true) {
						cout << "\nWord is updated successfully \n";
						Sleep(600);
						system("cls");
					}
					else {
						cout << "\nWord you are is not updated in dictionary\n";
						Sleep(600);
						system("cls");
					}
				}
				else {
					cout << "\nword not found in dictionary";
					Sleep(600);
					system("cls");
				}
			}
			else {
				cout << "\nyou have pressed enter without entering word";
				Sleep(600);
				system("cls");
			}

		}
		else if (choice == 5) {
			cout << "Exiting program.\n";
			break;
		}

	} while (true);
}
