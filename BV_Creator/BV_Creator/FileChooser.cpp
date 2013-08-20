#include "stdafx.h"
#include "FileChooser.h"

string FileChooser::chooseFile(int type, string filter, string name){
	// Create the file chooser, and show it
	Fl_File_Chooser chooser(".",                        // directory
		filter.c_str(),                        // filter
		type,     // chooser type
		name.c_str());        // title
	chooser.show();

	// Block until user picks something.
	//     (The other way to do this is to use a callback())
	//
	while(chooser.shown())
	{ Fl::wait(); }

	// User hit cancel?
	if ( chooser.value() == NULL )
	{ fprintf(stderr, "(User hit 'Cancel')\n"); return ""; }

	return chooser.value(0);
}