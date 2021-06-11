#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

using namespace std;

typedef unsigned int uint;
typedef map <string, vector<uint> > MAP; 

bool In_String(MAP& map_of_words, string& val);
void Increase(MAP & Words, string & word, uint & index);
vector<string> FaindURL();
void chouse_URL(string line, vector<string>& URLS);
MAP Read();

int main()
{
    try
    {
        MAP Words = Read();
        MAP::iterator it = Words.begin();

        ofstream R("Rezultatai.txt");
		for(const auto& a : Words)
		{
			if (a.first.size() >= 1) 
            {
				R << "Word |" << a.first + " \t\t" << "| have been repeated " << a.second.size() << " times "; 
                if(a.second.size() > 1) R << " In lines: ";
				cout <<"Word |"<< a.first+" \t\t" << "| have been repeated " << a.second.size() << " times "; 
                if(a.second.size() > 1) cout << " In lines: ";
				for (const auto& b : a.second) 
                {
                    if(b > 1)
                    {
                        R << b << " ";
                        cout << b << " ";                        
                    }
				}
				R << endl;
				cout << endl;
			}
		}
        cout << string(100, '=') << endl;
		cout << "\t\t\t\tURL:" << endl;
		cout << string(100, '=') << endl;

        R << string(100, '=') << endl;
		R << "\t\t\t\tURL:" << endl;
		R << string(100, '=') << endl;

		vector<string> URL = FaindURL();
		if (URL.empty()) 
        {
			cout << "Error" << endl;
		}
		else 
        {
			for (const auto& url : URL)
			{
				cout << url << endl;
				R << url << endl;
			}
		}
		cout << string(100, '=') << endl;
        R << string(100, '=') << endl;
    }
    catch(const exception& e)
    {
        cout << e.what() << '\n';
    }
}

void Increase(MAP & Words, string & word, uint & index) 
{
	MAP::iterator it = Words.begin();
	while (it != Words.end())
	{
		if (it -> first == word) 
        {
			it -> second.push_back(index + 1);
			break;
		}
		++it;
	}
}

MAP Read()
{
	ifstream D;
    D.open("failas.txt");
    cout << "\n Fail info: \n\n";
	cout << string(100, '=') << endl;
	MAP Words;
	string line;
	for (uint i = 0; !D.eof(); ++i) 
    {
		getline(D, line, '\n');       

		transform(line.begin(), line.end(), line.begin(), ::tolower);Increase;
		regex reg("\\W");
		line = regex_replace(line, reg, " ");                                                             

		stringstream ss(line);
		string word;
		while (ss >> word) 
        {
			if (In_String(Words, word)) Increase(Words, word, i);	
			else 
			{                                       
				vector<uint> init{ 1 };
				Words.insert(MAP::value_type(word, init));
			}

		}
		line.clear();
	}
	return Words;
}


bool In_String(MAP& map_of_words, string& val)
{
	MAP::iterator it = map_of_words.begin();
	while (it != map_of_words.end())
	{
		if (it -> first == val)
			return true;
		++it;
	}
	return false;
}

vector<string> FaindURL() 
{

	ifstream failas("failas.txt");
	vector<string> URL;
	string line;
	for (uint i = 0; !failas.eof(); ++i) 
    {
		getline (failas, line, '\n');
		chouse_URL(line, URL);
	}
	return URL;
}

void chouse_URL(string line, vector<string>& URLS) 
{
	try 
    {
		regex reg("((http|https):\\/\\/)?(www\\.)?(\\w+\\.(com|org|lt)){1}");
		sregex_iterator next(line.begin(), line.end(), reg);
		sregex_iterator end;
		while (next != end)
        {
			smatch match = *next;
			if (match.str() != "")
				URLS.push_back(match.str());
			next++;
		}
	}
	catch (regex_error & e) 
    {
		cout << e.what() << endl;
	}
}
