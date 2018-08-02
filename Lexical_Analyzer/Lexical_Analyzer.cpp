// Lexical Analyzer | Ehsan Mohammadi | mohammadi.ehsan1994@gmail.com

#include<iostream>
#include<conio.h>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

const int MAX_COUNT = 100;
typedef struct NumberTable
{
	double num;
	int lineNum;
} NumRecord;
void ShowHeader()
{
	cout << "Lexical Analyzer (Version 1.0)\n"
		<< "___________________________________________________\n\n";
}
string LoadFilePath()
{
	string path;
	cout << "Enter file path: ";
	getline(cin, path);

	return path;
}
void SplitLexemes(string path, string lexemes[MAX_COUNT][2])
{
	ifstream file(path);
	string fileLine;

	if (!file.is_open()) // if file doesn't exist
	{
		lexemes[0][0] = "Error";
		lexemes[0][1] = "* Error: File doesn't exist... *";
	}
	else // Otherwise
	{
		int i = 0; // i: Current row of lexemes array
		int fileRow = 1; // Current row of file

		while (getline(file, fileLine))
		{
			for (int j = 0; j < fileLine.length(); j++) // j: Current column of fileLine string
			{
				// Check splitters
				if (fileLine[j] != ' ' && fileLine[j] != '\t')
				{
					if (fileLine[j] == '>' || fileLine[j] == '<')
					{
						if (lexemes[i][1] != "\0")
						{
							lexemes[i][0] = fileRow + 48;
							i++;
						}
						lexemes[i][1] += fileLine[j];

						if (j + 1 < fileLine.length() && fileLine[j + 1] == '=')
						{
							lexemes[i][1] += fileLine[j + 1];
							j++;
						}

						lexemes[i][0] = fileRow + 48;
						i++;
					}
					else if (fileLine[j] == '!')
					{
						if (j + 1 < fileLine.length() && fileLine[j + 1] == '=')
						{
							if (lexemes[i][1] != "\0")
							{
								lexemes[i][0] = fileRow + 48;
								i++;
							}
							lexemes[i][1] += fileLine[j];
							lexemes[i][1] += fileLine[j + 1];
							j++;

							lexemes[i][0] = fileRow + 48;
							i++;
						}
						else
							lexemes[i][1] += fileLine[j];
					}
					else if (fileLine[j] == '=' || fileLine[j] == '[' || fileLine[j] == ']' || fileLine[j] == '{' 
						|| fileLine[j] == '}' || fileLine[j] == '(' || fileLine[j] == ')' || fileLine[j] == ';')
					{
						if (lexemes[i][1] != "\0")
						{
							lexemes[i][0] = fileRow + 48;
							i++;
						}
						lexemes[i][1] += fileLine[j];
						lexemes[i][0] = fileRow + 48;
						i++;
					}
					else
						lexemes[i][1] += fileLine[j];
				}
				else if (lexemes[i][1] != "\0") // When arrive to splitter
				{
					lexemes[i][0] = fileRow + 48;
					i++;
				}
			}

			// Increase i when lexemes[i] is not empty
			if (lexemes[i][1] != "\0")
			{
				lexemes[i][0] = fileRow + 48;
				i++;
			}
			fileRow++;
		}

		// Check file content is empty or not
		if (lexemes[0][1] == "\0")
		{
			lexemes[0][0] = "Error";
			lexemes[0][1] = "* Error: File content is empty... *";
		}
	}
}
void FindToken(string lexemes[MAX_COUNT][2], NumRecord numTable[MAX_COUNT])
{
	string strRelation = "<=>";
	string strSign = "+-";
	string strAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string strNumber = "0123456789";

	cout << "\n\nLexemes:\n\n";
	int i = 0; // i: Current row of lexemes array 
	int numTableRow = 0; // row: Current row of numTable

	while (lexemes[i][0] != "\0")
	{
		string lex = lexemes[i][1];

		//Find token
		if (strRelation.find(lex[0]) != string::npos || (lex[0] == '!' && lex[1] == '=')) // Relation
			cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Relation" << endl;
		else if (strSign.find(lex[0]) != string::npos) // Signed integer or Decimal or Unknown
		{
			if (strNumber.find(lex[1]) == string::npos)
				cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Unknown" << endl;
			else
			{
				bool isNumber = true, isDecimal = false;
				for (int j = 2; j < lex.length(); j++) // j: Current column of lex string
				{
					if (lex[j] == '.')
					{
						if (!isDecimal && strNumber.find(lex[j + 1]) != string::npos)
						{
							isDecimal = true;
							isNumber = false;
						}
						else
						{
							isDecimal = false;
							isNumber = false;

							cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Unknown" << endl;
							break;
						}
					}
					else if (strNumber.find(lex[j]) != string::npos)
					{
						if (!isDecimal)
							isNumber = true;
					}
					else
					{
						isDecimal = false;
						isNumber = false;

						cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Unknown" << endl;
						break;
					}
				}

				if (isNumber)
				{
					cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Signed integer" << endl;
					numTable[numTableRow].num = stod(lexemes[i][1]);
					numTable[numTableRow].lineNum = stoi(lexemes[i][0]);
					numTableRow++;
				}
				else if (isDecimal)
				{
					cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Decimal number" << endl;
					numTable[numTableRow].num = stod(lexemes[i][1]);
					numTable[numTableRow].lineNum = stoi(lexemes[i][0]);
					numTableRow++;
				}
			}
		}
		else if (strNumber.find(lex[0]) != string::npos) // Unsigned integer or Decimal or SCientific or String or Unknown
		{
			bool isNumber = true, isDecimal = false, isScientificNumber = false, isString = false;
			for (int j = 1; j < lex.length(); j++)
			{
				if (lex[j] == '.')
				{
					if (!isDecimal && !isScientificNumber && !isString && strNumber.find(lex[j + 1]) != string::npos)
					{
						isDecimal = true;
						isNumber = false;
						isScientificNumber = false;
						isString = false;
					}
					else
					{
						isDecimal = false;
						isNumber = false;
						isScientificNumber = false;
						isString = false;

						cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Unknown" << endl;
						break;
					}
				}
				else if (lex[j] == 'e' && strSign.find(lex[j + 1]) != string::npos)
				{
					if (!isString && !isScientificNumber)
					{
						isScientificNumber = true;
						isDecimal = false;
						isNumber = false;
						isString = false;
						++j;
					}
					else
					{
						isDecimal = false;
						isNumber = false;
						isScientificNumber = false;
						isString = false;

						cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Unknown" << endl;
						break;
					}
				}
				else if (strAlphabet.find(lex[j]) != string::npos)
				{
					if (!isDecimal && !isScientificNumber)
					{
						isString = true;
						isDecimal = false;
						isNumber = false;
						isScientificNumber = false;
					}
				}
				else if (strNumber.find(lex[j]) != string::npos)
				{
					if (!isDecimal && !isScientificNumber && !isString)
					{
						isNumber = true;
						isDecimal = false;
						isNumber = false;
						isScientificNumber = false;
					}
				}
				else
				{
					isDecimal = false;
					isNumber = false;
					isScientificNumber = false;
					isString = false;

					cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Unknown" << endl;
					break;
				}
			}
			if (isNumber && !isDecimal && !isScientificNumber && !isString)
			{
				cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Unsigned integer" << endl;
				numTable[numTableRow].num = stod(lexemes[i][1]);
				numTable[numTableRow].lineNum = stoi(lexemes[i][0]);
				numTableRow++;
			}
			else if (isDecimal && !isNumber && !isScientificNumber && !isString)
			{
				cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Decimal number" << endl;
				numTable[numTableRow].num = stod(lexemes[i][1]);
				numTable[numTableRow].lineNum = stoi(lexemes[i][0]);
				numTableRow++;
			}
			else if (isScientificNumber && !isDecimal && !isNumber && !isString)
			{
				cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Scientific number" << endl;
				numTable[numTableRow].num = stod(lexemes[i][1]);
				numTable[numTableRow].lineNum = stoi(lexemes[i][0]);
				numTableRow++;
			}
			else if (isString && !isDecimal && !isNumber && !isScientificNumber)
				cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", String" << endl;
		}
		else if (strAlphabet.find(lex[0]) != string::npos) // Name or Unknown
		{
			bool isName = true;
			for (int j = 1; j < lex.length(); j++)
			{
				if (strAlphabet.find(lex[j]) == string::npos && strNumber.find(lex[j]))
				{
					isName = false;

					cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Unknown" << endl;
					break;
				}
			}
			if (isName)
			{
				cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Name" << endl;
			}
		}
		else
		{
			cout << lexemes[i][1] << ", " << "Line " << lexemes[i][0] << ", Unknown" << endl;
		}

		i++;
	}
}
void ShowNumbers(NumRecord numTable[MAX_COUNT])
{
	double sum = 0;

	// Count numbers
	int i = 0; // i: Current row of numTable
	while (numTable[i].lineNum > 0)
	{
		sum += numTable[i].num;
		i++;
	}
	
	// Sum of numbers
	cout << "\n\n" << i << " numbers found\n"
		<< "SUM= "; cout << fixed << setprecision(6) << sum;
	
	// Content of number table
	cout << "\n\nContents of Number Table\n";
	for (int j = 0; j < i; j++)
	{
		cout << "\t" << j << "\tL" << numTable[j].lineNum << "\t" << numTable[j].num << "\n";
	}
}

int main()
{
	ShowHeader();
	string filePath = LoadFilePath();
	string lexemes[MAX_COUNT][2];
	NumRecord numTable[MAX_COUNT];

	SplitLexemes(filePath, lexemes);
	if (lexemes[0][0] == "Error") // if file doesn't exist or content is empty
	{
		cout << "\n" << lexemes[0][1];
	}
	else
	{
		FindToken(lexemes, numTable);
		ShowNumbers(numTable);
	}
	_getch();
	return 0;
}