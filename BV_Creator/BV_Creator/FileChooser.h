#pragma once
#include <string>
using namespace std;

class FileChooser{
public:
	FileChooser(void);
	~FileChooser(void);
	string chooseFile(int type, string filter, string name);

};