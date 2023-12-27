#include "dictionary.h"
	trienode::trienode() {
		for (int i = 0; i < 26; i++) {
			alphates[i] = nullptr;
		}
		endofword = false;
	}

	Dictionary::Dictionary() {
		num = 0;
		root = new trienode;
		for (int i = 0; i < 10; i++) {
			suggestions[i] = "";
		}
	}
	string Dictionary::meaning1(int index) {
		return suggestions[index - 1];
	}
	trienode*& Dictionary::getroot() {
		//num = 0;
		return root;
	}
	bool Dictionary::existance(char ch) {
		if (ch == '@') {
			if (num == 10) {
				return true;
			}
		}
		else {
			ch = ch - '0';
			if (ch > 0 && ch <= num) {
				return true;
			}
		}
	}
	void Dictionary::insertingwordinadictionary(string word, string meaningofword1) {
		trienode* temporaryroot = root;
		for (int i = 0; i < word.length(); i++) {
			int index = word[i] - 'a';
			if (temporaryroot->alphates[index] == nullptr) {
				temporaryroot->alphates[index] = new trienode;
			}
			if (i == word.length() - 1) {
				temporaryroot->alphates[index]->endofword = true;
				temporaryroot->alphates[index]->meaningofword = meaningofword1;
				break;
			}
			temporaryroot = temporaryroot->alphates[index];
		}
	}
	void Dictionary::deletedictionary(trienode* node) {
		if (node == nullptr) {
			return;
		}
		else {
			for (int i = 0; i < 26; i++) {
				deletedictionary(node->alphates[i]);
			}
			delete node;
		}
	}
	void Dictionary::line()
	{
		cout << endl << endl << endl << endl;
		cout << endl << endl << endl << endl;
		cout << endl << endl << endl << endl;
	}
	void Dictionary::loading()
	{
		line();

		system("color 70");  

		cout << "\t\t\t\t\t||  --------------------------  ||" << endl;
		cout << "\t\t\t\t\t||                              ||" << endl;
		cout << "\t\t\t\t\t||           Dictionary         ||" << endl;
		cout << "\t\t\t\t\t||                              ||" << endl;
		cout << "\t\t\t\t\t||  --------------------------  ||" << endl;
		Sleep(2000);
		system("cls");

		line();
		system("color 70");  

		cout << "\t\t\t\t\t ......... Project By .........." << endl << endl;
		cout << "\t\t\t\t\t|| --------------------------------- ||" << endl;
		cout << "\t\t\t\t\t||                                   ||" << endl;
		cout << "\t\t\t\t\t||    TAIMOUR TARIQ    22F-3874      ||" << endl;
		cout << "\t\t\t\t\t||    FAHAD BALOCH     22F-3442      ||" << endl;
		cout << "\t\t\t\t\t||                                   ||" << endl;
		cout << "\t\t\t\t\t|| --------------------------------- ||" << endl;
		Sleep(3000);
		system("cls");

		line();

		cout << "\t\t\t\t\t\tPlease wait while loading.........." << endl << endl;
		char a = 177, b = 219;
		cout << "\t\t\t\t\t\t";
		for (int k = 0; k <= 15; k++)
			cout << a;
		cout << "\r";
		cout << "\t\t\t\t\t\t";
		for (int l = 0; l <= 15; l++)
		{
			cout << b;
			for (int j = 0; j <= 1e8; j++);
		}
		system("cls");
	}
	int Dictionary::getMenuChoice() {
		int choice;
		string input;

		while (true) {
			cout << "\t\t\t\t\t\t" << UNDERLINE << BOLD << RED << "Menu:\n" << RESET;
			cout << CYAN << "1. Add a word\n";
			cout << "2. Search for a word\n";
			cout << "3. Delete a word\n";
			cout << "4. Update a word\n";
			cout << "5. Exit\n";
			cout << "Enter your choice: ";
			cout << RESET;
			cout << MAGENTA;

			cin >> input;

			stringstream ss(input);
			if (ss >> choice && ss.eof() && choice >= 1 && choice <= 5) {
				// Valid integer input
				break;
			}
			else {
				cout << "Invalid input. Please enter a valid choice.\n";

				cin.clear();

				system("cls");
			}
		}
		return choice;
	}
	void Dictionary::addword(string word, string meaning) {
		trienode* temporaryroot = root;
		for (int i = 0; i < word.length(); i++) {
			int index = word[i] - 'a';
			if (temporaryroot->alphates[index] == nullptr) {
				temporaryroot->alphates[index] = new trienode;
			}
			if (i == word.length() - 1) {
				temporaryroot->alphates[index]->endofword = true;
				temporaryroot->alphates[index]->meaningofword = meaning;

				
				ofstream file("Dictionary.txt", ios::app); 
				if (file.is_open()) {
					file << word << "     " << meaning << endl;
					file.close();
				}
				else {
					cerr << "Error in opening Dictionary file for writing.\n";
				}
			}
			temporaryroot = temporaryroot->alphates[index];
		}
	}
	void Dictionary::updatewordinfile(const string& word, const string& newMeaning) {
		fstream file("Dictionary.txt", ios::in | ios::out);

		if (!file.is_open()) {
			cerr << "Error in opening Dictionary file for updating.\n";
			return;
		}

		string line;
		size_t pos = 0;
		while (getline(file, line)) {
			istringstream iss(line);
			string currentWord, currentMeaning;

			if (iss >> currentWord >> currentMeaning) {
				if (currentWord == word) {
					file.seekp(pos);
					string updatedLine = leftAlign(currentWord, word.length()) + ' ' + leftAlign(newMeaning, newMeaning.length());
					file << updatedLine;
					file << string(line.length() - updatedLine.length(), ' ');
					break;
				}
			}

			pos = file.tellg();
		}

		file.close();
	}

	string Dictionary::leftAlign(const string& str, size_t width){
		stringstream ss;
		ss << left << setw(width) << str;
		return ss.str();
	}


	bool Dictionary::updateword(string word, string meaning) {
		trienode* temporaryroot = root;
		bool check = false;
		for (int i = 0; i < word.length(); i++) {
			int index = word[i] - 'a';
			if (temporaryroot->alphates[index] == nullptr) {
				check = false;
				break;
			}
			else if (i == word.length() - 1) {
				if (temporaryroot->alphates[index]->endofword == true) {
					temporaryroot->alphates[index]->meaningofword = meaning;
					updatewordinfile(word, meaning);
					check = true;
					break;
				}
			}
			temporaryroot = temporaryroot->alphates[index];
		}
		return check;
	}
	bool Dictionary::wordexistornot(string word) {
		trienode* temporaryroot = root;
		bool check = false;
		for (int i = 0; i < word.length(); i++) {
			int index = word[i] - 'a';
			if (temporaryroot->alphates[index] == nullptr) {
				check = false;
				break;
			}
			else if (i == word.length() - 1) {
				if (temporaryroot->alphates[index]->endofword == true) {
					check = true;
					break;
				}
			}
			temporaryroot = temporaryroot->alphates[index];
		}
		return check;
	}
	void Dictionary::searchword(string word) {
		bool check = true;;
		trienode* temporaryroot = root;
		for (int i = 0; i < word.length(); i++) {
			int index = word[i] - 'a';
			if (temporaryroot->alphates[index] == nullptr) {
				check = false;
				break;
			}
			if (i == word.length() - 1 && temporaryroot->alphates[index]->endofword == true) {
				cout << temporaryroot->alphates[index]->meaningofword;
			}
			temporaryroot = temporaryroot->alphates[index];
		}
		if (check == false || temporaryroot->endofword == false) {
			cout << "word not found";
		}
	}
	bool Dictionary::wordexistindictionaryornot(string word) {
		trienode* temporaryroot = root;
		bool check = true;;
		for (int i = 0; i < word.length(); i++) {
			int index = word[i] - 'a';
			if (temporaryroot->alphates[index] == nullptr) {
				check = false;
				break;
			}
			if (i == word.length() - 1) {
				temporaryroot->alphates[index]->endofword = false;
				temporaryroot->alphates[index]->meaningofword = "";
				return true;
			}
			temporaryroot = temporaryroot->alphates[index];
		}
		if (check == false) {
			return false;
		}
	}
	bool Dictionary::deleteWordFromDictionary(string word, trienode*& node) {
		if (wordexistindictionaryornot(word) == true) {
			deleteword(word, node, 0);
			return true;
		}
		else {
			return false;
		}
	}
	void Dictionary::deleteword(string word, trienode*& node, int x) {
		if (x == word.length() - 1) {
			node->endofword = false;
			node->meaningofword = "";
			return;
		}
		else {
			int index = word[x] - 'a';
			deleteword(word, node->alphates[index], x + 1);
			bool check = false;
			for (int j = 0; j < 26; j++) {
				if (node->alphates[index]->alphates[j] != nullptr) {
					check = true;
					break;
				}
			}
			if (check != true) {
				delete node->alphates[index];
				node->alphates[index] = nullptr;
			}
		}
	}
	void Dictionary::deletefromfile(const string& word) {
		ifstream inFile("Dictionary.txt");
		if (!inFile.is_open()) {
			cerr << "Error opening file.\n";
			return;
		}

		ofstream tempFile("temp.txt", ios::app);  // Create a temporary file for writing
		if (!tempFile.is_open()) {
			cerr << "Error opening temporary file.\n";
			inFile.close();
			return;
		}

		string line;
		while (getline(inFile, line)) {
			size_t pos = line.find(word);
			if (pos == string::npos) {
				// Word not found, add the line to the temporary file
				tempFile << line << endl;
			}
		}

		inFile.close();
		tempFile.close();

		// Replace the original file with the temporary file
		if (remove("Dictionary.txt") != 0) {

			return;
		}
		if (rename("temp.txt", "Dictionary.txt") != 0) {

			return;
		}
	}
	void Dictionary::wordsuggestion(string word) {
		trienode* temporaryroot = root;
		for (int i = 0; i < word.length(); i++) {
			int index = word[i] - 'a';
			if (temporaryroot->alphates[index] == nullptr) {
				break;
			}
			temporaryroot = temporaryroot->alphates[index];
		}
		livesuggestions(word, num, temporaryroot);
	}
	void Dictionary::livesuggestions(string word, int& count, trienode* temp) {
		int letter;
		if (temp == nullptr || count == 10) {
			return;
		}
		else if (temp->endofword == true) {
			suggestions[count++] = word;
			if (count < 10) {
				system("cls");
				print(count);
			}
			else if (count == 10) {
				system("cls");
				print(count);
			}
		}
		else {
			for (int i = 0; i < 26; i++) {
				if (temp->alphates[i] != nullptr) {
					char index = 'a' + i;
					string newword = word + index;
					livesuggestions(newword, count, temp->alphates[i]);
					if (count == 10) {
						return;
					}
				}
			}
		}
	}
	string Dictionary::check(string word, string print) {
		char ch = NULL;
		cout << "Enter " << print << " :";
		while (true) {
			if (_kbhit()) {
				ch = _getch();
				if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
					if (ch >= 'A' && ch <= 'Z') {
						ch = tolower(ch);
					}
					// Only add characters to temp if they are digits between 1 and 9, or '@'
					system("cls");
					word += ch;
					cout << "\r";
					cout << string(50, ' ');
					cout << "\r";
					cout << "Enter " << print << " :" << word;
				}
				else if (ch == '\r') {
					if (word != "") {
						break;
					}
					else {

						cout << "Enter " << print << " :" << endl;
						Sleep(500);
						system("cls");
					}
				}
				else if (ch == '\b') {
					if (word.length() > 1) {
						word.pop_back();

						cout << "\r";
						cout << string(50, ' ');
						cout << "\r";

						cout << "Enter " << print << " : " << word;
					}
					else if (word == "") {
						break;
					}
					else {
						word.pop_back();
						system("cls");
					}
				}
			}
		}
		return word;
	}
	void Dictionary::makingsuggestionsempty() {
		num = 0;
	}
	void Dictionary::print(int count) {
		cout << endl;
		for (int i = 0; i < count; i++) {
			cout << i + 1 << ": " << suggestions[i] << endl;
		}
	}
	Dictionary::~Dictionary() {
		deletedictionary(root);
	}