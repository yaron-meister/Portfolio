////////////////////////////////////////////////////////////////////////////////
//  File name:  beacon.cpp
//  Developer:  Yaron Meister
//  Date:       26.11.2021
//  Desciption: An implementation of the beacon.h
////////////////////////////////////////////////////////////////////////////////

#include "beacon.h"

// Static members initializations
const float Beacon::INVALID_DISTANCE(-1.0);


////////////////////////////////////////////////////////////////////////////////
//													Functions Implementations
////////////////////////////////////////////////////////////////////////////////
Beacon::Beacon(std::optional<cv::Point2d> center_point, float connectivity_radius, unsigned int id)	:
	m_id(id),	
	m_center_point(center_point),	
	m_connectivity_radius(connectivity_radius)
{
		if (m_center_point->x < 0 || m_center_point->y < 0 || m_connectivity_radius < 0)
		{
				m_center_point->x = 0;
				m_center_point->y = 0;

				m_connectivity_radius = 0.0f;
		}
	}

////////////////////////////////////////////////////////////////////////////////
void Beacon::CheckAndUpdateConnection(Beacon& other_beacon)
{
		if (m_id != other_beacon.m_id)
		{
				// Is connectable if own Radius is greater than the Distance between the center points
				if (m_connectivity_radius > GetDistanceBetweenBeacons(*this, other_beacon))
				{
					m_connectedBeacons.push_back(other_beacon.m_id);
				}
		}
}

// TODO::YARON - Add descriptions for functions
////////////////////////////////////////////////////////////////////////////////
float Beacon::GetDistanceBetweenBeacons(Beacon& one_beacon, Beacon& other_beacon)
{
	float distance(INVALID_DISTANCE);

	try
	{
		float beacons_delta_x(fabs(one_beacon.m_center_point->x - other_beacon.m_center_point->x));
		float beacons_delta_y(fabs(one_beacon.m_center_point->y - other_beacon.m_center_point->y));

		// Distance = SQRT(x^2 + y^2)
		distance = sqrt(powf(beacons_delta_x, 2.0f) + powf(beacons_delta_y, 2.0f));
	}
	catch (...)
	{
		// TODO::YARON - Logger
	}

	return (distance);
}

////////////////////////////////////////////////////////////////////////////////
bool Beacon::IsConnectedToOtherBeacon(unsigned int other_beacon_id)
{
	std::vector<unsigned int>::iterator it = std::find(m_connectedBeacons.begin(), m_connectedBeacons.end(), other_beacon_id);

	// "other_beacon_id" is found if "it" didn't reach to end()
	return (it != m_connectedBeacons.end());
}
