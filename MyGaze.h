// Copyright 2017 by Ryklin Software, Inc.
// All Rights Reserved.

#ifndef _MYGAZE_DLL_H_
#define _MYGAZE_DLL_H_
#include "stdafx.h"

class MyGazeClass
{
public:

	MyGazeClass(HWND hWnd);
	~MyGazeClass();
	int isConnected(){ return connected; }
    int loadCalibration(char* filePath);
    int saveCalibration(char* filepath);

	string GetSDKInfo();
	string GetProductInfo();
	int MyGazeClass::getConnectionStatus() { return connected; }

	data_sample* getSample(){return &sample;}
	int	addCalibrationPoint(F_POINT);
	int	finishCalibration();
	int startCalibration();

private:
	static void CALLBACK on_gaze_data_received(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);

	int connected;
	static data_sample sample;
	string sdk_info;
	string product_id;

	HWND hWnd;

};

#endif // _MYGAZE_DLL_H_
