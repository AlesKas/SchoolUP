#include "pch.h"
#include <iostream>
#include "Datum.cpp"
#include <regex>
using namespace std;

const char *months[] = { "1.", "2.", "3.", "4.", "5.", "6.", "7.", "8.", "9.", "10.", "11.", "12." };

bool isValid(const char* date)
{
	regex r("([[:digit:]]{1,2})\\. ([[:digit:]]{1,2}\\.|[a-z]+) ([[:digit:]]{4})");
	cmatch match;
	int index = -1;

	regex_match(date, match, r);

	if (match.size() == 0) 
		return false;
	for (int i = 0; i < 24; i++) {
		if (match[2].compare(mmm[i]) == 0) {
			index = i / 2;
		}
	}
	for (int i = 0; i < 12; i++) {
		if (match[2].compare(months[i]) == 0) {
			index = i;
		}
	}
	if (index == -1) 
		return false;
	else
		return (atoi(match[1].str().c_str()) <= d[index]);
}

int main()
{

	for (auto date : datum)
	{
		cout << date << " => ";
		if (isValid(date))
			cout << "valid" << endl;
		else
			cout << "invalid" << endl;
	}
}
