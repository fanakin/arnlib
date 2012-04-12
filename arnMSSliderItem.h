/***************************************************************************
                          arnMSSliderItem.h  -  description
                             -------------------
    begin                : gio Feb 9 2006
    copyright            : (C) 2006 by Aurion s.r.l.
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

#ifndef ArnMSSliderItemH
#define ArnMSSliderItemH

#include <qframe.h>
#include <qslider.h>
#include <qlayout.h>
#include <QMenu>
#include <qaction.h>
#include "arnqlabel.h"
#include "arnqslider.h"

class arnMSSliderItem : public QFrame {
	Q_OBJECT

	private:
		void init(void);
	private slots:
		void doValueChange(int val) {emit valueChanged(val);}
		void Nascondi_Hndl(void);
		void Connetti_Hndl(bool tg);
	protected:
		QLabel* Name;
		arnQLabel* Value;
		arnQSlider* Slider;
		QHBoxLayout *pHLayout;
		QMenu *pPopUp;

		virtual void mousePressEvent(QMouseEvent *e);
	public:
		QAction *Nascondi;
		QAction *Connetti;
        /*! \brief constructor in QT style \n
        *
        */
        arnMSSliderItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnMSSliderItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnMSSliderItem(const QString& label = "", const QString& value = "0", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnMSSliderItem(const QString& label = "", int value = 0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnMSSliderItem(void);

    signals:
        void valueChanged(int val);

    public slots:
        /*! \brief overloaded function : set the value for the channel of a fixed index\n
        *
        * @param index is the index in the list of the channels\n
        * @param val is the value to set\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline QString name(void) {return Name->text();}

        /*! \brief overloaded function : set the value for the channel of a fixed index\n
        *
        * @param index is the index in the list of the channels\n
        * @param val is the value to set\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline void setName(const QString& name) {return Name->setText(name);}

        inline void setSliderMin(int min) {Slider->setMinValue(min);}

        inline void setSliderMax(int max) {Slider->setMaxValue(max); }

        inline int SliderMin(void) {return Slider->minValue();}
 
        inline int SliderMax(void) {return Slider->maxValue();}

        inline void setSliderValue(int val) {Slider->setValue(val);}

        inline double sliderValue(void) {return ((double) (Slider->value()));}

        inline void setValueSize(NumericFixedFormat_t sz, char f = 'f' ,int pr = 3) {Value->setSize(sz,f,pr);}

        inline void setValueMin( double min) {Value->setMin(min);}

        inline void setValueMax( double max) {Value->setMax(max);}

        inline double ValueMin( void ) {return Value->Min();}

        inline double ValueMax( void ) {return Value->Max();}

		double value(void);
		
		inline QString text(void) {return Value->text();}
		
		inline bool isConnected(void) {return ((Connetti != 0) ? Connetti->isOn(): false);}
		        
		inline void setMulSelKeyUP(Qt::Key K) {Slider->setMulSelKeyUP(K);}
		
		inline void setMulSelKeyDOWN(Qt::Key K) {Slider->setMulSelKeyDOWN(K);}
		
		inline Qt::Key getMulSelKeyUP(void) {return Slider->getMulSelKeyUP();}
		
		inline Qt::Key getMulSelKeyDOWN(void) {return Slider->getMulSelKeyDOWN();}
		
		inline int lineStep(void) {return Slider->lineStep();}
		
		inline int pageStep(void) {return Slider->pageStep();}
};

#endif
