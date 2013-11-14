#ifndef _LOG_H_
#define _LOG_H_

#ifdef USE_CONSOLEKIT
#include "Ck.h" 
#endif
#ifdef USE_PAM
#include "PAM.h"
#endif
#include "const.h"
#include <fstream>
#include <iostream>

using namespace std;

static class LogUnit {
	ofstream logFile;
public:
	bool openLog(const char * filename);
	void closeLog();

	~LogUnit() { closeLog(); }

	template<typename Type>
	LogUnit & operator<<(const Type & text) {
		if (logFile.is_open()) {
			logFile << text; logFile.flush();
		} else {
			cerr << text;
		}
		return *this;
	}

	LogUnit & operator<<(ostream & (*fp)(ostream&)) {
		if (logFile.is_open()) {
			logFile << fp; logFile.flush();
		} else {
			cerr << fp;
		}
		return *this;
	}

	LogUnit & operator<<(ios_base & (*fp)(ios_base&)) {
		if (logFile.is_open()) {
			logFile << fp; logFile.flush();
		} else {
			cerr << fp;
		}
		return *this;
	}
} logStream;

#endif /* _LOG_H_ */
