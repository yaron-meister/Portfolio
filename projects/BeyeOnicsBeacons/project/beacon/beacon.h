////////////////////////////////////////////////////////////////////////////////
//  File name:  beacon.h
//  Developer:  Yaron Meister
//  Date:       26.11.2021
//  Desciption: A header file for class Beacon
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "logger.h"

#include <optional>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// A class to store data for defining a certain Beacon
class Beacon
{
public:
	static const float INVALID_DISTANCE;

	// CTor
	explicit Beacon(std::optional<cv::Point2d> centerPoint, float connectivityRadius, unsigned int id = 0);

	// Methods

	static float GetDistanceBetweenBeacons(Beacon& oneBeacon, Beacon& otherBeacon);

	std::optional<cv::Point2d>				GetCenterPoint() const { return m_center_point; }
	float															GetConnectivityRadius() const { return m_connectivity_radius; }
	unsigned int											GetID() const { return m_id; }
	std::vector<unsigned int>					GetConnections() const { return m_connectedBeacons; }

	void SetCenterPoint(std::optional<cv::Point2d> newCenterPoint) { m_center_point = newCenterPoint; }
	void SetConnectivityRadius(float newConnectivityRadius) { m_connectivity_radius = newConnectivityRadius; }
	void SetID(unsigned int newID) { m_id = newID; }

	bool IsConnected() const { return !m_connectedBeacons.empty(); }
	bool IsConnectedToOtherBeacon(unsigned int otherBeaconId);
	void CheckAndUpdateConnection(Beacon& otherBeacon);

private:

	// Members
	unsigned int								m_id;
	std::optional<cv::Point2d>  m_center_point;
	float                       m_connectivity_radius;
	std::vector<unsigned int>		m_connectedBeacons;
	//Logger*							m_logger;
};
