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
	// CTor
	explicit Beacon(std::optional<cv::Point2d> center_point, int connectivity_radius) :
		m_center_point(center_point),
		m_connectivity_radius(connectivity_radius)
	{
		if (m_center_point->x < 0 || m_center_point->y < 0 || m_connectivity_radius < 0)
		{
			m_center_point->x = 0;
			m_center_point->y = 0;

			m_connectivity_radius = 0;
		}
	}

	// Methods

	std::optional<cv::Point2d>  getCenterPoint() { return m_center_point; }
	int                         getConnectivityRadius() { return m_connectivity_radius; }

	void setCenterPoint(std::optional<cv::Point2d> newCenterPoint) { m_center_point = newCenterPoint; }
	void setConnectivityRadius(int newConnectivityRadius) { m_connectivity_radius = newConnectivityRadius; }

private:
	// Members
	std::optional<cv::Point2d>  m_center_point;
	int                         m_connectivity_radius;
};
