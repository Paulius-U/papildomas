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

void CleanString(string& eil);
bool In_String(MAP& map_of_words, string& val);
MAP Read();
void Increase(MAP & Words, string & word, uint & index);
vector<string> FaindURL();
void chouse_URL(string line, vector<string>& URLS);

int main()
{
    int random = 1;
    try
    {
        MAP Words = Read();
        MAP::iterator it = Words.begin();

        ofstream out("Rezultatai.txt");
		for(const auto& x : Words)
		{
			if (x.first.size() >= random) 
            {
				out << "Word |" << x.first + " \t\t" << "| have been repeated " << x.second.size() << " times "; 
                if(x.second.size() > 1) out << " In lines: ";
				cout <<"Word |"<< x.first+" \t\t" << "| have been repeated " << x.second.size() << " times "; 
                if(x.second.size() > 1) cout << " In lines: ";
				for (const auto& a : x.second) 
                {
                    if(a != 1)
                    {
                        out << a << " ";
                        cout << a << " ";                        
                    }
				}
				out << endl;
				cout << endl;
			}
		}
        cout << string(100, '=') << endl;
		cout << "\t\t\t\tURLS:" << endl;
		cout << string(100, '=') << endl;

        out << string(100, '=') << endl;
		out << "\t\t\t\tURLS:" << endl;
		out << string(100, '=') << endl;

		vector<string> URLS = FaindURL();
		if (URLS.empty()) 
        {
			cout << "Error" << endl;
		}
		else 
        {
			for (const auto& url : URLS)
			{
				cout << url << endl;
				out << url << endl;
			}
		}
		cout << string(100, '=') << endl;
        out << string(100, '=') << endl;
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
		if (it->first == word) 
        {
			it->second.push_back(index + 1);
			break;
		}
		++it;
	}
}

void CleanString(string& eil)
{
	transform(eil.begin(), eil.end(), eil.begin(), ::tolower);Increase;
	regex reg("\\W");
	eil = regex_replace(eil, reg, " ");

}

MAP Read()
{
	ifstream in;
    in.open("failas.txt");
    cout << "\n Fail info: \n\n";
	cout << std::string(100, '=') << endl;
	MAP Words;
	string line;
    int url = 1;
	for (uint i = 0; !in.eof(); ++i) 
    {
		getline(in, line, '\n');                                                   
		CleanString(line);                                                              

		stringstream ss(line);
		string word;
		while (ss >> word) 
        {
			if (!In_String(Words, word)) 
            {                                       
				vector<uint> init{ 1 };
				Words.insert(MAP::value_type(word, init));
			}
			else 
            {
				Increase(Words, word, i);
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
		if (it->first == val)
			return true;
		++it;
	}
	return false;
}

vector<string> FaindURL() 
{

	ifstream failas("failas.txt");;
	vector<string> URLS;
	string line;
	for (uint i = 0; !failas.eof(); ++i) 
    {
		getline (failas, line, '\n');
		chouse_URL(line, URLS);
	}
	return URLS;
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