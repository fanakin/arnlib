TARGET = arn
TEMPLATE = lib
DESTDIR  = .
#VERSION = 0.0.1.0

#CONFIG += qt debug staticlib thread create_prl
CONFIG += qt release staticlib thread create_prl

QT += qt3support opengl xml svg

# if we want idps, uncomment the following line:
#
CONFIG += idps
#

OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc

#win32:DESTDIR = ..\win32\ktool
debug:CONFIG += console

INCLUDEPATH += ../qwt/src
INCLUDEPATH += ../qwt3d/include



HEADERS += ./arnParametric.h
HEADERS += ./arnCarriedParametric.h
HEADERS += ./arnSAParametric.h
HEADERS += ./arnParViewItem.h
HEADERS += ./arnPVIObjectContainer.h
HEADERS += ./arnPVIArray.h
HEADERS += ./arnPVIMatrix.h
HEADERS += ./arnPVIVariable.h
HEADERS += ./arnPVINumericArray.h
HEADERS += ./arnPVIStringArray.h
HEADERS += ./arnPVINumericMatrix.h
HEADERS += ./arnPVIStringMatrix.h
HEADERS += ./arnPVIMiscArray.h
HEADERS += ./arnPVIMiscMatrix.h
HEADERS += ./arnPVINumericVariable.h
HEADERS += ./arnPVIStringVariable.h
HEADERS += ./arnPVI8BitValueMatrix.h
HEADERS += ./arnPVI8BitExpandValueMatrix.h
HEADERS += ./arnPVI16BitValueMatrix.h
HEADERS += ./arnSObjectContainer.h
HEADERS += ./arnSVariable.h
HEADERS += ./arnSNumericVariable.h
HEADERS += ./arnSStringVariable.h
HEADERS += ./arnSArray.h
HEADERS += ./arnSStringArray.h
HEADERS += ./arnSNumericArray.h
HEADERS += ./arnSMiscNumericArray.h
HEADERS += ./arnSMiscMarkNumericArray.h
HEADERS += ./arnSMatrix.h
HEADERS += ./arnSNumericMatrix.h
HEADERS += ./arnSMiscNumericMatrix.h
HEADERS += ./arnSMiscMarkNumericMatrix.h
HEADERS += ./arnSMiscMarkTraceNumericMatrix.h

HEADERS += ./arnColorTableItem.h
HEADERS += ./arnGLVector.h
HEADERS += ./arnGLMultipleVector.h
HEADERS += ./arnGLArray.h
HEADERS += ./arnGLMultipleArray.h
HEADERS += ./arnGLArrayViewer.h
HEADERS += ./arnGLMultipleArrayViewer.h
HEADERS += ./arnGLMatrix.h
HEADERS += ./arnGLTable.h
HEADERS += ./arnGLMatrixViewer.h
HEADERS += ./arnNumericArrayViewer.h
HEADERS += ./arnStringArrayViewer.h
HEADERS += ./arnCompositeArrayViewer.h
HEADERS += ./arnEnCompositeArrayViewer.h
HEADERS += ./arnNumericMatrixViewer.h
HEADERS += ./arnNumericVariableViewer.h
HEADERS += ./arnStringVariableViewer.h
HEADERS += ./arnCompositeMatrixViewer.h
HEADERS += ./arnEnCompositeMatrixViewer.h
HEADERS += ./arnMiscMatrixViewer.h
HEADERS += ./arnBitValueMatrixViewer.h
HEADERS += ./arnStringMatrixViewer.h
HEADERS += ./arnObjectViewer.h
HEADERS += ./arnConfig.h
HEADERS += ./arn44monitor.h
HEADERS += ./arnCarrier.h

unix {
	HEADERS += ./arnComPort.h
	SOURCES += ./arnComPort.cpp
	HEADERS += ./arnSocketPort.h
	SOURCES += ./arnSocketPort.cpp
	HEADERS += ./arnDeviceLoader.h
	SOURCES += ./arnDeviceLoader.cpp

}
win32 {
	HEADERS += winComPort.h
	SOURCES += winComPort.cpp
	HEADERS += winSocketPort.h
	SOURCES += winSocketPort.cpp
	HEADERS += winDeviceLoader.h
	SOURCES += winDeviceLoader.cpp

}

HEADERS += ./arnConfig.h
HEADERS += ./arnNumericFilter.h
HEADERS += ./arnqlabel.h
HEADERS += ./arnqslider.h
HEADERS += ./arnSerialInterface.h

HEADERS += ./arnWTmonitor.h
HEADERS += ./arnz4monitor.h
HEADERS += ./CommonFunctions.h
HEADERS += ./Dispatchers.h
HEADERS += ./Protocols.h
HEADERS += ./arnLibversion.h
HEADERS += ./arnlibtypes.h

HEADERS += ./arnGenericLogger.h
#HEADERS += ./arnThermoPacketItem.h
HEADERS += ./arnPacketItem.h
HEADERS += ./arnSimplePacketItem.h
HEADERS += ./arnNumPacketItem.h
HEADERS += ./arnNumEnPacketItem.h
HEADERS += ./arnNumEnColorTrackPacketItem.h
HEADERS += ./arnStringPacketItem.h
#HEADERS += ./arnThermoPacketVisualizer.h
HEADERS += ./arnPacketVisualizer.h
HEADERS += ./arnNumEnPacketVisualizer.h
HEADERS += ./arnNumEnColorTrackPacketVisualizer.h
HEADERS += ./arnStringPacketVisualizer.h
HEADERS += ./arnThrottleCycleVisualizer.h
HEADERS += ./arnPacketVisualizerSelectPanel.h
#HEADERS += ./arnTimeBasedVectorPlot.h
#HEADERS += ./arnVectorPlot.h
#HEADERS += ./arnMulVectorPlot.h
HEADERS += ./arnSliderItem.h
HEADERS += ./arnMSSliderItem.h
HEADERS += ./arnSliderGroup.h
HEADERS += ./arnEngineAppSliderItem.h
HEADERS += ./arnEngineAppMSSliderItem.h
HEADERS += ./arnEngineAppMSSliderGroup.h
HEADERS += ./arnEngineAppSliderGroup.h
HEADERS += ./arnEngineZAppSliderItem.h
HEADERS += ./arnEngineZAppSliderGroup.h
HEADERS += ./arnEngineAppMSTraceSliderItem.h
HEADERS += ./arnEngineAppMSTraceSliderGroup.h
HEADERS += ./arnMiscItemGroup.h
HEADERS += ./arnPushButtonItem.h
HEADERS += ./arnToggleButtonItem.h

HEADERS += ./arnSODevice.h

HEADERS += ./arnCycle.h
HEADERS += ./arnThrottleCycle.h

HEADERS += ./arnGraphDataStream.h
HEADERS += ./arnGraphVisualizer.h
HEADERS += ./arnEdlChannel.h
HEADERS += ./arnEdlChannelList.h
HEADERS += ./arnEdlFileInfo.h
HEADERS += ./arnEdlFileManager.h




SOURCES += ./arnParametric.cpp
SOURCES += ./arnCarriedParametric.cpp
SOURCES += ./arnSAParametric.cpp
SOURCES += ./arnParViewItem.cpp
SOURCES += ./arnPVIObjectContainer.cpp
SOURCES += ./arnPVIArray.cpp
SOURCES += ./arnPVIMatrix.cpp
SOURCES += ./arnPVIVariable.cpp
SOURCES += ./arnPVINumericArray.cpp
SOURCES += ./arnPVIStringArray.cpp
SOURCES += ./arnPVIMiscArray.cpp
SOURCES += ./arnPVINumericMatrix.cpp
SOURCES += ./arnPVIStringMatrix.cpp
SOURCES += ./arnPVIMiscMatrix.cpp
SOURCES += ./arnPVINumericVariable.cpp
SOURCES += ./arnPVIStringVariable.cpp
SOURCES += ./arnPVI8BitValueMatrix.cpp
SOURCES += ./arnPVI8BitExpandValueMatrix.cpp
SOURCES += ./arnPVI16BitValueMatrix.cpp
SOURCES += ./arnSObjectContainer.cpp
SOURCES += ./arnSVariable.cpp
SOURCES += ./arnSNumericVariable.cpp
SOURCES += ./arnSStringVariable.cpp
SOURCES += ./arnSArray.cpp
SOURCES += ./arnSStringArray.cpp
SOURCES += ./arnSNumericArray.cpp
SOURCES += ./arnSMiscNumericArray.cpp
SOURCES += ./arnSMiscMarkNumericArray.cpp
SOURCES += ./arnSMatrix.cpp
SOURCES += ./arnSNumericMatrix.cpp
SOURCES += ./arnSMiscNumericMatrix.cpp
SOURCES += ./arnSMiscMarkNumericMatrix.cpp
SOURCES += ./arnSMiscMarkTraceNumericMatrix.cpp

SOURCES += ./arnGLVector.cpp
SOURCES += ./arnGLMultipleVector.cpp
SOURCES += ./arnGLArray.cpp
SOURCES += ./arnGLMultipleArray.cpp
SOURCES += ./arnGLArrayViewer.cpp
SOURCES += ./arnGLMultipleArrayViewer.cpp
SOURCES += ./arnGLMatrixViewer.cpp
SOURCES += ./arnGLMatrix.cpp
SOURCES += ./arnGLTable.cpp
SOURCES += ./arnNumericArrayViewer.cpp
SOURCES += ./arnStringArrayViewer.cpp
SOURCES += ./arnCompositeArrayViewer.cpp
SOURCES += ./arnEnCompositeArrayViewer.cpp
SOURCES += ./arnNumericMatrixViewer.cpp
SOURCES += ./arnNumericVariableViewer.cpp
SOURCES += ./arnStringVariableViewer.cpp
SOURCES += ./arnCompositeMatrixViewer.cpp
SOURCES += ./arnEnCompositeMatrixViewer.cpp
SOURCES += ./arnMiscMatrixViewer.cpp
SOURCES += ./arnBitValueMatrixViewer.cpp
SOURCES += ./arnStringMatrixViewer.cpp
SOURCES += ./arnObjectViewer.cpp

SOURCES += ./arn44monitor.cpp
SOURCES += ./arnCarrier.cpp

SOURCES += ./arnConfig.cpp
SOURCES += ./arnNumericFilter.cpp
SOURCES += ./arnqlabel.cpp
SOURCES += ./arnqslider.cpp
SOURCES += ./arnSerialInterface.cpp
SOURCES += ./arnWTmonitor.cpp
SOURCES += ./arnz4monitor.cpp
SOURCES += ./CommonFunctions.cpp
SOURCES += ./Dispatchers.cpp
SOURCES += ./Protocols.cpp
SOURCES += ./arnLibversion.cpp

SOURCES += ./arnGenericLogger.cpp
#SOURCES += ./arnThermoPacketItem.cpp
SOURCES += ./arnPacketItem.cpp
SOURCES += ./arnSimplePacketItem.cpp
SOURCES += ./arnNumPacketItem.cpp
SOURCES += ./arnNumEnPacketItem.cpp
SOURCES += ./arnNumEnColorTrackPacketItem.cpp
SOURCES += ./arnStringPacketItem.cpp
SOURCES += ./arnPacketVisualizer.cpp
#SOURCES += ./arnThermoPacketVisualizer.cpp
SOURCES += ./arnNumEnPacketVisualizer.cpp
SOURCES += ./arnNumEnColorTrackPacketVisualizer.cpp
SOURCES += ./arnStringPacketVisualizer.cpp
SOURCES += ./arnThrottleCycleVisualizer.cpp
SOURCES += ./arnPacketVisualizerSelectPanel.cpp
#SOURCES += ./arnTimeBasedVectorPlot.cpp
#SOURCES += ./arnVectorPlot.cpp
#SOURCES += ./arnMulVectorPlot.cpp
SOURCES += ./arnSliderItem.cpp
SOURCES += ./arnMSSliderItem.cpp
SOURCES += ./arnSliderGroup.cpp
SOURCES += ./arnEngineAppSliderItem.cpp
SOURCES += ./arnEngineAppMSSliderItem.cpp
SOURCES += ./arnEngineAppMSSliderGroup.cpp
SOURCES += ./arnEngineAppSliderGroup.cpp
SOURCES += ./arnEngineZAppSliderItem.cpp
SOURCES += ./arnEngineZAppSliderGroup.cpp
SOURCES += ./arnEngineAppMSTraceSliderItem.cpp
SOURCES += ./arnEngineAppMSTraceSliderGroup.cpp
SOURCES += ./arnMiscItemGroup.cpp
SOURCES += ./arnPushButtonItem.cpp
SOURCES += ./arnToggleButtonItem.cpp

SOURCES += ./arnCycle.cpp
SOURCES += ./arnThrottleCycle.cpp

SOURCES += ./arnGraphDataStream.cpp
SOURCES += ./arnGraphVisualizer.cpp
SOURCES += ./arnEdlChannel.cpp
SOURCES += ./arnEdlChannelList.cpp
SOURCES += ./arnEdlFileInfo.cpp
SOURCES += ./arnEdlFileManager.cpp


FORMS += ./baudrateselectionform.ui
SOURCES += baudrateselectionimpl.cpp
HEADERS += baudrateselectionimpl.h

FORMS += ./comselectionform.ui
SOURCES += comselectionimpl.cpp
HEADERS += comselectionimpl.h

FORMS += ./commchannelselform.ui
SOURCES += commchannelselimpl.cpp
HEADERS += commchannelselimpl.h


LIBS = -L.

DEFINES += QT_THREAD_SUPPORT _REENTRANT

win32:LIBS += -lwsock32 -lopengl32 -lglu32

LIBS += -dl 

unix:idps {
}

# zlib support for gl2ps
zlib {
	DEFINES += GL2PS_HAVE_ZLIB
	win32:LIBS += zlib.lib
	unix:LIBS  += -lz
}
