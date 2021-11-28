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

////////////////////////////////////////////////////////////////////////////////
//	Function name:	Beacon()	
//	Description:		CTor
//	Return value:		None
////////////////////////////////////////////////////////////////////////////////
Beacon::Beacon(std::optional<cv::Point2d> centerPoint, float connectivityRadius, unsigned int id) :
	m_id(id),
	m_center_point(centerPoint),
	m_connectivity_radius(connectivityRadius)
{
	if (m_center_point->x < 0 || m_center_point->y < 0 || m_connectivity_radius < 0)
	{
		m_center_point->x = 0;
		m_center_point->y = 0;

		m_connectivity_radius = 0.0f;
	}
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	CheckAndUpdateConnection	
//	Description:		Check if "this" is connectable with "otherBeacon",
//									If so, updates the m_connectedBeacons
//	Return value:		None
////////////////////////////////////////////////////////////////////////////////
void Beacon::CheckAndUpdateConnection(Beacon& otherBeacon)
{
	if (m_id != otherBeacon.m_id)
	{
		// Is connectable if own Radius is greater than the Distance between the center points
		if (m_connectivity_radius > GetDistanceBetweenBeacons(*this, otherBeacon))
		{
			m_connectedBeacons.push_back(otherBeacon.m_id);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	GetDistanceBetweenBeacons	
//	Description:		Calculates the distance between "oneBeacon" to "otherBeacon"
//	Return value:		float - The distance
////////////////////////////////////////////////////////////////////////////////
float Beacon::GetDistanceBetweenBeacons(Beacon& oneBeacon, Beacon& otherBeacon)
{
	float distance(INVALID_DISTANCE);
	float beaconsDeltaX(fabs(oneBeacon.m_center_point->x - otherBeacon.m_center_point->x));
	float beaconsDeltaY(fabs(oneBeacon.m_center_point->y - otherBeacon.m_center_point->y));

	// Distance = SQRT(x^2 + y^2)
	distance = sqrt(powf(beaconsDeltaX, 2.0f) + powf(beaconsDeltaY, 2.0f));
	
	return (distance);
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	IsConnectedToOtherBeacon	
//	Description:		Checks if "otherBeacon" is connected
//	Return value:		True - connected, False - not
////////////////////////////////////////////////////////////////////////////////
bool Beacon::IsConnectedToOtherBeacon(unsigned int otherBeaconID)
{
	std::vector<unsigned int>::iterator it = std::find(m_connectedBeacons.begin(), m_connectedBeacons.end(), otherBeaconID);

	// "other_beacon_id" is found if "it" didn't reach to end()
	return (it != m_connectedBeacons.end());
}
