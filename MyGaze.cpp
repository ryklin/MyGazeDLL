// Copyright 2017 by Ryklin Software, Inc.
// All Rights Reserved.

#include "MyGaze.h"
data_sample MyGazeClass::sample;

string product_id;

MyGazeClass::MyGazeClass(){
	// This function gets called when hairball loads the eye tracker. This is where you want to connect to the eye tracker with its SDK function calls. This is also where initialization of variables takes place.

	connected = FALSE;
	sample.gaze_lx_relative = 0.5;
	sample.gaze_ly_relative = 0.5;
	sample.gaze_rx_relative = 0.5;
	sample.gaze_ry_relative = 0.5;
	sample.left_pupil_diameter = 4;
	sample.right_pupil_diameter = 4;

	sample.position_lx_relative = 0.40;
	sample.position_rx_relative = 0.60;
	sample.position_ly_relative = 0.50;
	sample.position_ry_relative = 0.50;

	sample.position_lz_relative = 0.5;
	sample.position_rz_relative = 0.5;

	product_id = ""; // this might be an ip address or some string that identifies the eye tracker's name

	// connect here
	// if connected successfully, make sure to set the below variable to TRUE
	connected = TRUE;

	// this timer code is just for example to simulate an eye tracker
	SetTimer(NULL, 0, 20, (TIMERPROC)&on_gaze_data_received);
}

MyGazeClass::~MyGazeClass(){

	// you may need to call some disconnect functions here depending on the DLL. This function will get called when the user disconnects from the eye tracker in Hairball. This happens when the program exists OR when a different DLL is loaded, and this one gets unloaded
	connected = FALSE;

	// this timer code is just for example to simulate an eye tracker
	KillTimer(0, 1);
}

// This is the function where new data is sampled and returned to Hairball. I have implemented some random values here so that you can changes in Hairball
void CALLBACK MyGazeClass::on_gaze_data_received(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	// needs to return normalized values between 0.0 - 1.0, where 0.5 is the center of the screen

	// you can either choose random values for testing
	//sample.gaze_rx_relative = rand() % GetSystemMetrics(SM_CXSCREEN) / (float)GetSystemMetrics(SM_CXSCREEN);
	//sample.gaze_ry_relative = rand() % GetSystemMetrics(SM_CYSCREEN) / (float)GetSystemMetrics(SM_CYSCREEN);
	//sample.gaze_lx_relative = rand() % GetSystemMetrics(SM_CXSCREEN) / (float)GetSystemMetrics(SM_CXSCREEN);
	//sample.gaze_ly_relative = rand() % GetSystemMetrics(SM_CYSCREEN) / (float)GetSystemMetrics(SM_CYSCREEN);

	/* I've demonstrated how to move in a circle*/
	static float t = 0;

	float positionX = sin(t)*(float)GetSystemMetrics(SM_CXSCREEN)/ (float)GetSystemMetrics(SM_CXSCREEN);
	positionX /= 2;
	positionX += 0.5;

	float positionY = cos(t)*(float)GetSystemMetrics(SM_CYSCREEN) / (float)GetSystemMetrics(SM_CYSCREEN);
	positionY /= 2;
	positionY += 0.5;

	sample.gaze_rx_relative = positionX;
	sample.gaze_ry_relative = positionY;
																	 
	sample.gaze_lx_relative = positionX;
	sample.gaze_ly_relative = positionY;

	t += 0.1;

	/* I've demonstrated how to move in a circle, the above is just an example*/

	// This is the location of the eye balls in space
	sample.position_lx_relative = 0.40;		// left eye X
	sample.position_ly_relative = 0.50;		// left eye Y

	sample.position_rx_relative = 0.60;		// right eye X
	sample.position_ry_relative = 0.50;		// right eye Y

	sample.position_lz_relative = 0.5;		// distance of left eye from eye tracker controller
	sample.position_rz_relative = 0.5;		// distance of right eye from eye tracker controller

	sample.left_validity = 2;				// validity codes are from 0 to 4, where 2 means both eyes are tracked OK, and 4 means no eyes are being tracked. Check Tobii Gaze for the exact meaning of these codes
	sample.right_validity = 2;				// validity codes are from 0 to 4, where 2 means both eyes are tracked OK, and 4 means no eyes are being tracked. Check Tobii Gaze for the exact meaning of these codes
}

// the below calibration functions are optional. Most eye trackers have their own calibration routines so you can ignore these
int MyGazeClass::loadCalibration(char* filePath)
{
    return 0;
}

int MyGazeClass::saveCalibration(char* filePath)
{
    return 0;
}

int MyGazeClass::addCalibrationPoint(F_POINT point)
{
	return 0;
}

int MyGazeClass::startCalibration()
{
	return 0;
}

int MyGazeClass::finishCalibration()
{
	return 0;
}

string MyGazeClass::GetSDKInfo() {
	sdk_info = "This says something about the SDK, such as who wrote it, what it does, what makes it different";
	return sdk_info;
}

string MyGazeClass::GetProductInfo()
{
	product_id = "This says something about the product such as the name, version, model";
	return product_id;
}