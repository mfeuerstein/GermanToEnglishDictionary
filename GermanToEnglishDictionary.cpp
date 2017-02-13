// German to English Dictionary
// Michael Feuerstein
// 10/10/2015

#include "GermanToEnglishDictionary.h"

void main()
{
	const int SIZE = 5;
	int choice, lSize = 0;
	bool fileExists = false;
	GermanToEnglishWord dictionary[SIZE];
	const char * file = "dictionary.dat";
	char temp;

	if (_access(file, 00) == 0){
		loadDictionary(dictionary, SIZE, file);
		fileExists = true;
	}

	while (true)
	{
		printMenu();
		cin >> choice;   cin.ignore(80, '\n');

		if (choice == 1 && fileExists)
			cout << "\n\t\t       Error. Dictionary file already exists.\n"; 
		else if (choice > 1  && !fileExists)
			cout << "\n\t\t       Error. Dictionary file does not exist. Please create a new list.\n";
		else
		{
			system("cls");
			switch (choice)
			{
				case 1: fileExists = loadGtEWordsArray(dictionary, SIZE);   sortDictionary(dictionary, SIZE);  saveDictionary(dictionary, SIZE, file);   break;
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7: printDictionary(dictionary, SIZE, choice - 1);   break;
				case 8: lookUpDefinition(dictionary, SIZE);   break;
				case 9: cout << "\n\n\n\n\n\t\t       Exit program? (y/n): "; 
					    temp = _getch();  
					    if (temp == 'Y' || temp == 'y')   
						    exit(0);
						break;
				default: cout << "Incorrect. Please enter a choice(1 - 9): ";
			}
		}
		cout << "\n\nPress any key to get back to menu...";
		system("pause>nul");
		system("cls");
	}
	_getch();
}

void printMenu()
{
	cout << "\n\n\n\n"
		 << "\t\t       1. Create the word list\n"
		 << "\t\t       2. German to English nouns\n"
		 << "\t\t       3. German to English verbs\n"
		 << "\t\t       4. German to English prepositions\n"
		 << "\t\t       5. German to English adjectives\n"
		 << "\t\t       6. German to English adverbs\n"
		 << "\t\t       7. German to English cardinal numbers\n"
		 << "\t\t       8. Search for a word\n"
		 << "\t\t       9. Quit\n"
		 << "\n\t\t       Enter your choice(1 - 9): ";
}

bool loadGtEWordsArray(GermanToEnglishWord dict[], int size)
{
	int lSize;

	for (lSize = 0; lSize < size; lSize++){
		dict[lSize] = getGtEW();
		system("cls");
	}
	return true;
}

GermanToEnglishWord getGtEW(){  

	int wordType;
	string eng, ger;

	GermanToEnglishWord word;

	cout << "\n\n\n\n"
		 << "\t\t       1. Nouns\n"
		 << "\t\t       2. Verbs\n"
		 << "\t\t       3. Prepositions\n"
		 << "\t\t       4. Adjectives\n"
		 << "\t\t       5. Adverbs\n"
		 << "\t\t       6. Cardinal numbers\n\n"
		 << "\t\t       Enter part of speech(1 - 6): ";
	cin >> wordType;  cin.ignore(80, '\n');

	cout << "\n\t\tF1 : " << char(132) << ", F2 : " << char(142) << ", F3 : " << char(148) << ", F4 : " << char(153) << ", F5 : " << char(129) << ", F6 : " << char(154);
	cout << "\n\n\t\t       Enter German word: ";
	ger = getGermanWord();

	cout << "\n\n\t\t       Enter English translation: ";
	getline(cin, eng);

	word.wordType = wordType;
	word.germanTrans = ger;       
	word.englishTrans = eng;      

	return word;
}

string getGermanWord()
{
	unsigned char key1, key2, letter;
	string word = "";

	while ((key1 = _getch()) != '\r')
	{
		if (key1 == 0)
		{
			key2 = _getch();

			switch (int(key2))
			{
				case 59: letter = char(132);   break;
				case 60: letter = char(142);   break;
				case 61: letter = char(148);   break;
				case 62: letter = char(153);   break;
				case 63: letter = char(129);   break;
				case 64: letter = char(154);   break;
			}
			word += letter;
			cout << letter;
		}
		else
		{
			switch (key1)
			{
				// enables backspacing for german word entry - array keys not accounted for
				case '\b': if (word != "")
						   {
							   cout << '\b';// << char(255) << '\b';
								word.erase(word.end() - 1);
				            }break;

				default:  letter = key1;
						  cout << letter;
						  word += letter;
			}
		}
	}

	return word;
}

void sortDictionary(GermanToEnglishWord dict[], int size)
{
	GermanToEnglishWord temp;

	for (int i = 0; i < size - 1; i++){
		for (int j = i + 1; j < size; j++)
		{
			if (cleanGermanWord(dict[i].germanTrans, dict[i].wordType) > 
				cleanGermanWord(dict[j].germanTrans, dict[j].wordType) )
			{
				temp = dict[i];
				dict[i] = dict[j];
				dict[j] = temp;
			}
		}
	}
}

void saveDictionary(GermanToEnglishWord dict[], int size, const char *file)
{
	ofstream fout(file, ios_base::out | ios_base::app | ios_base::binary);

	for (int i = 0; i < size; i++)
	{
		fout.write( (char *)&dict[i], sizeof dict[i] );
	}

	fout.close();
}

void loadDictionary(GermanToEnglishWord dict[], int size, const char *file)
{
	ifstream fin(file, ios_base::in | ios_base::binary);


		for (int i = 0; i < size; i++)
		{
			fin.read((char *)&dict[i], sizeof dict[i]);

		}
	fin.close();
}

string cleanGermanWord(string word, int type){ 

	if (type == 1)
	{
		word = ignoreArticle(word);
	}

	return exchangeGermanLettering(word);
}

string ignoreArticle(string word)
{
	return word.substr(4, word.length());
}

string exchangeGermanLettering(string word){

	for (int i = 0; i < word.length(); i++)
	{
		switch (int(word[i]))
		{
			case 132: word[i] = 'a';   break;
			case 142: word[i] = 'A';   break;
			case 148: word[i] = 'o';   break;
			case 153: word[i] = 'O';   break;
			case 129: word[i] = 'u';   break;
			case 154: word[i] = 'U';   break;
		}
	}

	return word;
}

void lookUpDefinition(GermanToEnglishWord dict[], int size){

	string word = "";
	int index; 

	cout << "\n\n\n\n\t\t       Enter a word: ";
	getline(cin, word);

	index = getWordIndex(dict, size, word);

	if (index == -1)
		cout << "\n\t\t       Definition not found.";
	else
		printDefinition(dict, index);
}

int getWordIndex(GermanToEnglishWord dict[], int size, string word){

	for (int i = 0; i < size; i++)
	{
		if (dict[i].wordType == 1)
			if (word == ignoreArticle(dict[i].germanTrans))
				return i;
		if (word == dict[i].germanTrans)
			return i;
	}

	return -1;

}

void printDictionary(GermanToEnglishWord dict[], int size, int type)
{
	system("cls");

	cout << right
		<< "\n\n" << setw(21) << "German Word" << setw(25) << "Part of speech" << setw(25) << "English meaning" << "\n"
		<< setw(21) << "-----------" << setw(25) << " --------------" << setw(25) << "---------------" << "\n\n";
	for (int i = 0; i < size; i++)
	{
		if (dict[i].wordType == type || type == 0)
			cout << addSpaces(10) << dict[i].germanTrans << addSpaces(22 - dict[i].germanTrans.length()) << wordTypes[dict[i].wordType - 1] 
			<< addSpaces(24 - wordTypes[dict[i].wordType - 1].length()) << dict[i].englishTrans << "\n";
	}
}

void printDefinition(GermanToEnglishWord dict[], int i)
{
	cout << right
		<< "\n\n" << setw(21) << "German Word" << setw(25) << "Part of speech" << setw(25) << "English meaning" << "\n"
		<< setw(21) << "-----------" << setw(25) << " --------------" << setw(25) << "---------------" << "\n\n";
	cout << addSpaces(10) << dict[i].germanTrans << addSpaces(22 - dict[i].germanTrans.length()) << wordTypes[dict[i].wordType - 1]
		<< addSpaces(24 - wordTypes[dict[i].wordType - 1].length()) << dict[i].englishTrans << "\n";
}

string addSpaces(int numSpaces)
{
	string spaces = "";

	for (int i = 0; i < numSpaces; i++)
	{
		spaces += " ";
	}

	return spaces;
}
