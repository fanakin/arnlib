/***************************************************************************
                          arnlibtypes.h  -  description
                             -------------------
    begin                : sab feb 22 2003
    copyright            : (C) 2002 by fabio giovagnini
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

#ifndef ArnLibTypesH
#define ArnLibTypesH

#define __PACKED__	__attribute__((packed))
#define __ARN_STRUCT_ALIGN__(x)	 __attribute__((packed,aligned(x)))

typedef enum NumericFixedFormat {
	nff_u8 = 0,
	nff_u16,
	nff_u32,
	nff_s8,
	nff_s16,
	nff_s32,
	nff_float,
	nff_double,
	nff_string,
	nff_8bit,
	nff_16bit,
	nff_24bit,
	nff_32bit,
	nff_none
	} NumericFixedFormat_t;
typedef enum NumericProcess {
	np_linear = 0,
	np_polynom1,
	np_polynom2,
	np_polynom3,
	np_none
	} NumericProcess_t;
typedef enum NumericRepresentationFormat {
	nrf_hex = 0,
	nrf_dec,
	nrf_bin,
	nrf_none
	} NumericRepresentationFormat_t;
typedef enum CommInterface {
	ci_COM = 0,
	ci_SOCK,
	ci_None
	} CommInterface_t;
typedef enum CommProtocol {
	cp_arn,
	cp_z4,
	cp_arntcpip,
	cp_none
	} CommProtocol_t;
typedef enum CpuTarget {
	Ctt_H83048 = 0,
        Ctt_H8S2345,
        Ctt_H8S2345Z24E,
        Ctt_SH27044,
	Ctt_SH27044F,
	Ctt_ARN44B,
	Ctt_SH27145, // not yet impemented for SA devices
	Ctt_ARN45, // not yet implemented
	Ctt_H83687,
	Ctt_H8S2345_20MHZ,
	Ctt_H83687_10MHZ,
	Ctt_H83687_16MHZ,
	Ctt_H83687_16MHZ_BEN10,
	Ctt_H83048FONE_16MHZ,
	Ctt_H836064_16MHZ,
	// da qui in avanti tecnologia 0.18u
	Ctt_H8S2378_16MHZ,
	Ctt_SH27085_10MHZ,
	Ctt_SH2A7286_12MHZ,
	Ctt_None} CpuTarget_t;

typedef enum arnVisibleWidgetStatus {
	arn_vws_NONE = 0,
	arn_vws_VISIBLE,
	arn_vws_NOTVISIBLE,
	} arnVisibleWidgetStatus_t;

typedef enum arnGLArrayPaintingMode {
	arn_glAPM_VERTICAL_LINES = 0,
	arn_glAPM_MASHED_LINES,
	arn_glAPM_NONE } arnGLArrayPaintingMode_t;

typedef enum arnGLTablePaintingMode {
	arn_glTPM_VERTICAL_LINES = 0,
	arn_glTPM_MASHED_SURFACE,
	arn_glTPM_NONE } arnGLTablePaintingMode_t;

typedef enum arnKCDeviceActionType {
	arn_kcd_BUILD_PARAMETERS = 0,
	arn_kcd_SHOT,
	arn_kcd_RESET,
	arn_kcd_RESETRTPARAMS,
	arn_kcd_OPENFILE_TIMED_LOGG,
	arn_kcd_CLOSEFILE_TIMED_LOGG,
	arn_kcd_TIMED_LOGG,
	arn_kcd_OPENFILE_SHOT_LOGG,
	arn_kcd_CLOSEFILE_SHOT_LOGG,
	arn_kcd_SHOT_LOGG,
	arn_kcd_TIMED_TRACE,
	arn_kcd_UPDATE_RTPACKWIDGET_STATUS,
	arn_kcd_UPDATE_RTPARAMWIDGET_STATUS,
	arn_kcd_NONE } arnKCDeviceActionType_t;

typedef enum arnMultiLangItemType {
	arn_mli_SLIDERITEM_HIDE = 0,
	arn_mli_SLIDERITEM_CONNECT,
	arn_mli_SLIDERITEM_ENCOP,
	arn_mli_SLIDERITEM_EDITCOP,
	arn_mli_PACKETITEM_HIDE,
	arn_mli_PACKETITEM_ENWARNING,
	arn_mli_PACKETITEM_TRACKCOLOR,
	arn_mli_NONE } arnMultiLangItemType_t;

typedef enum arnDeviceToKtoolRequestType {
	arn_dtkr_NONE = 0,
	arn_dtkr_OPENCOMMCHANNEL,
	arn_dtkr_CLOSECOMMCHANNEL,
	arn_dtkr_PROCESSMESSAGEQUEUE,
	} arnDeviceToKtoolRequestType_t;

#define COLORNAME				16
typedef char __colorName_t[COLORNAME];

typedef enum arnPacketItemType {
    apit_PacketItem,
    apit_NumPacketItem,
    apit_NumEnPacketItem,
    apit_NumEnColorTrackPacketItem,
    apit_StringPacketItem,
    apit_ThermoPacketItem,
    apit_None
    } arnPacketItemType_t;

typedef enum arnGroupItemType {
	agit_PushButtonItem = 0,
	agit_ToggleButtonItem,
	agit_RadioButtonItem,
	agit_None
	} arnGroupItemType_t;

#endif

