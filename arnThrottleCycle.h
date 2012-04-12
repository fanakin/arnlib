/***************************************************************************
                          arnThrottleCycle.h  -  description
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

#ifndef ArnThrottleCycleH
#define ArnThrottleCycleH

#include "arnCycle.h"

class arnThrottleCycle : public arnCycle {
    private:
    protected:
		struct stepItem {
			int OpenPerc;
			unsigned int DuringTime;
			};
		unsigned int CycleSize;
		struct stepItem *pCycle;
		QString getOpenPerc(QString line);
		QString getDuringTime(QString line);
    public:
    /*! \brief default constructor\n
    *
    * Ex:\n
    * ...\n
    */
    arnThrottleCycle(void);

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
    arnThrottleCycle(const char* fname);

    /*! \brief destructor\n
    *
    * Ex:\n
    * ...\n
    */
    ~arnThrottleCycle(void);

    /*! \brief returns the Open Percentage of the throttle for the step i\n
    *
    *
	*
	* @param stp cycle step index
    * @return the value of open percentage for cycle step i
    *
    * Ex:\n
    * ...\n
    */
	inline int getOpenPercentage(unsigned int stp) {if (stp < CycleSize) return pCycle[stp].OpenPerc; return 0;}

    /*! \brief returns the Time during in ms of the step i\n
    *
    *
	*
	* @param val raw value
    * @return the value of time during for cycle step i
    *
    * Ex:\n
    * ...\n
    */
	inline unsigned int getTimeStepDuring(unsigned int stp) {if (stp < CycleSize) return pCycle[stp].DuringTime; return 0;}

    /*! \brief returns the Size of the cycle\n
    *
    *
	*
    * @return the cycle size
    *
    * Ex:\n
    * ...\n
    */
	inline unsigned int getCycleSize() {return CycleSize;}

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
