/***************************************************************************
                          arnCycle.h  -  description
                             -------------------
    begin                : gio ott 21 2004
    copyright            : (C) 2004 by fabio giovagnini
    email                : fabio.giovagnini@aurion-tech.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef ArnCycleH
#define ArnCycleH

#include <qstring.h>


class arnCycle {
    private:
    protected:
		FILE *pfile;
		QString filename;
		QString cyclename;
		unsigned int numoflines;
		bool isSeparator(char c);
		QString getLine(FILE *pf);
    public:
    /*! \brief default constructor\n
    *
    * Ex:\n
    * ...\n
    */
    arnCycle(void);

    /*! \brief constructor using filename for filtering using a table\n
    *
    * This constructor works loading a cycle for automating a job from a text file.\n
    * The file is a sequenze of lines, it has cle extention of the name and\n
    * it  has the following format:\n
    * Filename: the same with extension as the real name of the file; ex. acycle.cle;\n
    * cycle name;\n
	* number of steps of the cycle (NSTEPS);\n
	* the number of the lines into the file will be  (3 + NSTEPS) lines,\n
    * value of the step 0, time of during of step 0 in ms;\n
    * value of the step 1, time of during of step 1 in ms;\n
    * value of the step 2, time of during of step 2 in ms;\n
    * ...
    * ...
    * value of the step (NSTEPS - 1), time of during of step (NSTEPS - 1) in ms;\n
    *
    *
    * @param fname file name without path: ex: acycle.cle
    * Ex:\n
    * ...\n
    */
    arnCycle(const char* fname);

    /*! \brief destructor\n
    *
    * Ex:\n
    * ...\n
    */
    ~arnCycle(void);

    /*! \brief returns the name of the file storing the cycle\n
    *
    *
    *
    * @return the name of the file
    *
    * Ex:\n
    * ...\n
    */
	inline const char* getFileName(void) {return filename.latin1();}

	/*! \brief it filters linearlly the value\n
    *
    *
    * This function overloaded function allows to filter val linearlly\n
    * keeping in count the size of val and so its physically\n
    * dimension.\n
    *
    * @param val raw value
    * @param min value in the scaled range.
    * @param max value in the scaled range.
    * @return the scaled value
    *
    * Ex:\n
    * ...\n
    */
	};
#endif
