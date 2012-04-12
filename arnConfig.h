/***************************************************************************
                          arnConfig.h  -  description
                             -------------------
    begin                : lun gen 27 2003
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
//---------------------------------------------------------------------------
#ifndef ArnConfigH
#define ArnConfigH
//---------------------------------------------------------------------------

#include <sys/param.h>
#include <stdio.h>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

class arnConfig {
    private:
        QDomNode _findkeyonchildren(const QDomNode &cur,const char *key);    
        //xmlNodePtr _findkey(xmlNodePtr cur,const char *key);
    protected:
        QDomDocument *doc;
        char* filename;

        /*! \brief check the error in errno.\n
        *
        * @param if defined __DEBUG__, the string to put out.
        * @return always false.
        *
        * Ex:\n
        * ...\n
        */
        //virtual bool errorcheck(const char* str);

        /*! \brief to convert betwwen diffent encoded formats.\n
        *
        * @param the string to manipulate and convert.
        * @param the string containing the encoding format we like.
        * @return the encoded out buffer screen.
        *
        * This function has to allocate the output buffer memory\n
        * and return it with the encoded string.\n
        * The application has to free the encoded string when it doesn't\n
        * need anyumore.
        *
        * Ex:\n
        * ...\n
        */
        virtual unsigned char *convert(unsigned char *in, char *convert);
    public:

        /*! \brief default constructor\n
        *
        */
        arnConfig(void);

        /*! \brief default destructor\n
        *
        */
        virtual ~arnConfig(void);

        /*! \brief load the configuration from a file\n
        *
        * @param absdir is the absolute path where search filename\n
        * @param filename is the filename to load configuration from\n
        * @return true if filename exists and loading has been successfull, false otherwise\n
        * Ex:\n
        * ...\n
        */
        virtual bool loadfile(const char* absdir, const char* filename) = 0;

        /*! \brief \n
        *
        * @param \n
        * @return \n
        * Ex:\n
        * ...\n
        */
        virtual bool createfile(const char* absdir, const char* filename) = 0;

        /*! \brief \n
        *
        * @param \n
        * @return \n
        * Ex:\n
        * ...\n
        */
        virtual bool savefile(void);

        /*! \brief \n
        *
        * @param \n
        * @return \n
        * Ex:\n
        * ...\n
        */
        virtual QString findkey(const char *key);

        /*! \brief \n
        *
        * @param \n
        * @return \n
        * Ex:\n
        * ...\n
        */
        virtual bool modifykey(const char *key,const char *newvalue);

	/*! \brief This function transfers into the doc structure the config data\n
        *
        * @param \n
        * @return \n
        * Ex:\n
        * ...\n
        */
        virtual bool updateDoc(void) {return false;}

	QDomNode addTextNode (QDomNode &node, const QString &tag, const QString &value);
};
#endif

