/***************************************************************************
                          arnNumericFilter.h  -  description
                             -------------------
    begin                : gio mar 6 2003
    copyright            : (C) 2003 by fabio giovagnini
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

#ifndef ArnNumericFilterH
#define ArnNumericFilterH


class arnNumericFilter {
    private:
    protected:
    public:
    /*! \brief default constructor\n
    *
    * Ex:\n
    * ...\n
    */
    arnNumericFilter(void);

    /*! \brief destructor\n
    *
    * Ex:\n
    * ...\n
    */
    ~arnNumericFilter(void);

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
    static double linear(unsigned char val, double min = 0, double max = 255);

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
    static double linear(unsigned short val, double min = 0, double max = 65535);

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
    static double linear(unsigned long val, double min = 0, double max = (2147483647.0 + 2147483648.0));

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
    static double linear(signed char val, double min = -128, double max = 127);

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
    static double linear(signed short val, double min = -32768, double max = 32767);

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
    static double linear(signed long val, double min = -2147483648.0, double max = 2147483647.0);

    /*! \brief it filters with a 3 degree polynom the value\n
    *
    *
    * This function filters the val using a polynom of 3 th degree\n
    * y = c0 * x^0 + c1 * x^1
    *
    * @param val raw value
    * @param c0 coefficient for 0 degree term.
    * @param c1 coefficient for 1 degree term.
    * @return the filtered value
    *
    * Ex:\n
    * ...\n
    */
    static double polinom1(double val, double c0 = 0, double c1 = 1);

    /*! \brief it filters with a 3 degree polynom the value\n
    *
    *
    * This function filters the val using a polynom of 3 th degree\n
    * y = c0 * x^0 + c1 * x^1 + c2 * x^2
    *
    * @param val raw value
    * @param c0 coefficient for 0 degree term.
    * @param c1 coefficient for 1 degree term.
    * @param c2 coefficient for 2 degree term.
    * @return the filtered value
    *
    * Ex:\n
    * ...\n
    */
    static double polinom2(double val, double c0 = 0, double c1 = 1, double c2 = 0);

    /*! \brief it filters with a 3 degree polynom the value\n
    *
    *
    * This function filters the val using a polynom of 3 th degree\n
    * y = c0 * x^0 + c1 * x^1 + c2 * x^2 + c3 * x^3
    *
    * @param val raw value
    * @param c0 coefficient for 0 degree term.
    * @param c1 coefficient for 1 degree term.
    * @param c2 coefficient for 2 degree term.
    * @param c3 coefficient for 3 degree term.
    * @return the filtered value
    *
    * Ex:\n
    * ...\n
    */
    static double polinom3(double val, double c0 = 0, double c1 = 1, double c2 = 0, double c3 = 0);

    /*! \brief it converts a linear scaled value the the correspondig raw value\n
    *
    *
    * This functions gets a scaled value, the min and max value for scaling \n
    * and return the corresponding unsigned char raw value\n
    *
    * @param sclval scaled value
    * @param sclmin min value for scaling.
    * @param sclmax nax value for scaling.
    * @return the raw unsigned char value
    *
    * Ex:\n
    * ...\n
    */
    static unsigned char toRawUnsignedChar(double sclval, double sclmin, double sclmax);
    
    /*! \brief it converts a linear scaled value the the correspondig raw value\n
    *
    *
    * This functions gets a scaled value, the min and max value for scaling \n
    * and return the corresponding unsigned short raw value\n
    *
    * @param sclval scaled value
    * @param sclmin min value for scaling.
    * @param sclmax nax value for scaling.
    * @return the raw unsigned short value
    *
    * Ex:\n
    * ...\n
    */
    static unsigned short toRawUnsignedShort(double sclval, double sclmin, double sclmax);
    
    /*! \brief it converts a linear scaled value the the correspondig raw value\n
    *
    *
    * This functions gets a scaled value, the min and max value for scaling \n
    * and return the corresponding unsigned long raw value\n
    *
    * @param sclval scaled value
    * @param sclmin min value for scaling.
    * @param sclmax nax value for scaling.
    * @return the raw unsigned long value
    *
    * Ex:\n
    * ...\n
    */
    static unsigned long toRawUnsignedLong(double sclval, double sclmin, double sclmax);

    /*! \brief it converts a linear scaled value the the correspondig raw value\n
    *
    *
    * This functions gets a scaled value, the min and max value for scaling \n
    * and return the corresponding signed char raw value\n
    *
    * @param sclval scaled value
    * @param sclmin min value for scaling.
    * @param sclmax nax value for scaling.
    * @return the raw signed char value
    *
    * Ex:\n
    * ...\n
    */
    static signed char toRawSignedChar(double sclval, double sclmin, double sclmax);

    /*! \brief it converts a linear scaled value the the correspondig raw value\n
    *
    *
    * This functions gets a scaled value, the min and max value for scaling \n
    * and return the corresponding signed short raw value\n
    *
    * @param sclval scaled value
    * @param sclmin min value for scaling.
    * @param sclmax nax value for scaling.
    * @return the raw signed short value
    *
    * Ex:\n
    * ...\n
    */
    static signed short toRawSignedShort(double sclval, double sclmin, double sclmax);

    /*! \brief it converts a linear scaled value the the correspondig raw value\n
    *
    *
    * This functions gets a scaled value, the min and max value for scaling \n
    * and return the corresponding signed long raw value\n
    *
    * @param sclval scaled value
    * @param sclmin min value for scaling.
    * @param sclmax nax value for scaling.
    * @return the raw signed long value
    *
    * Ex:\n
    * ...\n
    */
    static signed long toRawSignedLong(double sclval, double sclmin, double sclmax);
    };
#endif
