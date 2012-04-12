/***************************************************************************
                          arnThermoPacketItem.h  -  description
                             -------------------
    begin                : ven Mag 22 2009
    copyright            : (C) 2009 by fabio giovagnini
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
#ifndef ArnThermoPackectItemH
#define ArnThermoPackectItemH

#include <qlabel.h>
#include <qwidget.h>
#include <qlcdnumber.h>
#include <qlayout.h>
#include <qmenu.h>

#include "arnlibtypes.h"
#include "qwt_thermo.h"


class arnThermoPacketItem : public QWidget {
	Q_OBJECT

	private:
		void init(const QString& label,double value);
	private slots:
		void Nascondi_Hndl(void);
	protected:
		arnPacketItemType_t tpe;
		QLabel* Name;
		QLabel* NumValue;
		QGridLayout *pGLayout;
		QMenu *pPopUp;
		QwtThermo *Value;

		//virtual void mousePressEvent(QMouseEvent *e) = 0;
	public:
		QAction *Nascondi;

        /*! \brief constructor in QT style \n
        *
        */
        arnThermoPacketItem(QWidget *parent = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnThermoPacketItem(const QString& label = "",double value = 0, QWidget *parent = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnThermoPacketItem(void);

    public slots:
        /*! \brief overloaded function : get the name of the channel \n
        *
        * @return name of the channel\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline QString name(void) {return Name->text();}

        /*! \brief overloaded function : set the name of the channel \n
        *
        * @param name is the name to set\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline void setName(const QString& name) {Name->setText(name);}

        /*! \brief overloaded function : get the name of the channel \n
        *
        * @return value of the channel\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline double value(void) {return Value->value();}

        /*! \brief overloaded function : set the value of the channel \n
        *
        *
        * @param val is the name to set\n
        *
        * Ex:\n
        * ...\n
        */
        inline void setValue(double val) {Value->setValue(val);NumValue->setText(QString::number(Value->value(),'f',1));}

        /*! \brief overloaded function : set the value for the channel of a fixed index\n
        *
        * @return type of the channel\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
		inline arnPacketItemType_t type(void) {return tpe;}
        
		/*! \brief It sets the name alignment\n
		*
		* @param a is the alignment as Qt::AlignmentFlags\n
		*
		* This function uses a bitwised OR of Qt::AlignmentFlags to aling the name\n
		* See Qt::AlignmentFlags documentation.
		*
		* Ex:\n
		* ...\n
		* a->alignName(Qt::AlignVCenter | Qt::AlignHCenter); // H and V center alignment
		*/
		inline void alignName(int a) {Name->setAlignment(a);}

		/*! \brief It sets the name alignment\n
		*
		* @param a is the font size as in QFont::setPointSize(int)\n
		*
		* This function sets the point size for the font of the Name label\n
		* See QFont documentation.
		*
		* Ex:\n
		* ...\n
		* a->setFontSize(24); // set the point size feature of the font to 24
		*/
		inline void setNameFontSize(int a) {
			QFont F(Name->font());
			F.setPointSize(a);
			Name->setFont(F);
			}

		inline void setRange(double vmin, double vmax, bool lg = false) { Value->setRange(vmin,vmax,lg);}
                inline void setBorderWidth(int m) { Value->setBorderWidth(m);}
		inline void setAlarmLevel(double v) {Value->setAlarmLevel(v);}
		inline double alarmLevel() const {return Value->alarmLevel();}
		inline void setAlarmEnabled(bool tf) {Value->setAlarmEnabled(tf);}
		inline bool alarmEnabled() const {return Value->alarmEnabled();}
		inline void setPipeWidth(int w) {Value->setPipeWidth(w);}
		inline int pipeWidth() const {return Value->pipeWidth();}
		inline void setMaxValue(double v) {Value->setMaxValue(v);}
		inline double maxValue() const {return Value->maxValue();}
		inline void setMinValue(double v) {Value->setMinValue(v);}
		inline double minValue() const {return Value->minValue();}
};


#endif
