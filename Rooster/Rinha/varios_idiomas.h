#ifndef __INGLES_INTERMEDIARIO
#define __INGLES_INTERMEDIARIO

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class LANGUAGE {

private:

	vector<string> GAME_TEXT;
	int __lang = 0;
	int __last_lang = 1;


	static const char* file_path(int lang) {

		if (lang == Lang::ENGLISH) {
			return "lang/english.txt";
		}

		if (lang == Lang::PORTUGUESE) {
			return "lang/pt-br.txt";
		}
	}
	 
public:

	~LANGUAGE() {
		GAME_TEXT.clear();
	}

	enum  Lang {

		ENGLISH,
		PORTUGUESE

	};


	enum Line {

		MAIN_MENU,
		START,
		SETTINGS,
		QUIT,
		BACK,
		SINGLE,
		MULTI,
		RESUME,
		AIM_COLOR,
		SENSI,
		MINI,
		MODE,
		SELECT_LANG,
		LANG,
		RESTART_GAME,
		YES, 
		NO, 
		SCORE
	};

	LANGUAGE() {
		
	}

	Lang getLastLang() {
		return (Lang) this->__last_lang;
	}
	Lang getLang() {
		return (Lang) __lang;
	}
	void readLines(ifstream& file, string & line) {
		if (file.eof()) {
			return;
		}
		getline(file, line);
		this->GAME_TEXT.push_back(line);
		readLines(file, line);
	}

	void startAllTexts(Lang lang) {
		ifstream readfile(file_path(lang));
		string line;
		readLines(readfile, line);
		readfile.close();
	}

	void update(Lang lang) {

		ofstream file("lang/start_lang.ini", ios::out | ios::trunc);
		file << lang << " " << this->__lang;
		file.close();
		__last_lang = __lang;
		__lang = lang;
		GAME_TEXT.clear();
		this->startAllTexts(lang);
	}

	string getLine(Line line) {
		return GAME_TEXT.at(line);
	}

};

#endif
