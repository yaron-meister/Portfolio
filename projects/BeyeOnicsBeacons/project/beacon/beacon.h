////////////////////////////////////////////////////////////////////////////////
//  File name:  beacon.h
//  Developer:  Yaron Meister
//  Date:       26.11.2021
//  Desciption: A header file for class Beacon
////////////////////////////////////////////////////////////////////////////////

#pragma once

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
	explicit Beacon(std::optional<cv::Point2d> center_point, float connectivity_radius, unsigned int id = 0);

	// Methods
	
	static float GetDistanceBetweenBeacons(Beacon& one_beacon, Beacon& other_beacon);

	std::optional<cv::Point2d>				GetCenterPoint() const  { return m_center_point; }
	float															GetConnectivityRadius() const { return m_connectivity_radius; }
	unsigned int											GetID() const { return m_id; }
	std::vector<unsigned int>					GetConnections() const { return m_connectedBeacons; }

	void SetCenterPoint(std::optional<cv::Point2d> new_center_point) { m_center_point = new_center_point; }
	void SetConnectivityRadius(float new_connectivity_radius) { m_connectivity_radius = new_connectivity_radius; }
	void SetID(unsigned int new_id) { m_id = new_id; }

	bool IsConnected() const { return !m_connectedBeacons.empty(); }
	void CheckAndUpdateConnection(Beacon& other_beacon);

private:

	// Members
	unsigned int								m_id;
	std::optional<cv::Point2d>  m_center_point;
	float                       m_connectivity_radius;
	std::vector<unsigned int>		m_connectedBeacons;
};
