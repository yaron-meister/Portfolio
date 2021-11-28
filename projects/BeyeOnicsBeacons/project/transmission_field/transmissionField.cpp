////////////////////////////////////////////////////////////////////////////////
//  File name:  transmissionField.cpp
//  Developer:  Yaron Meister
//  Date:       26.11.2021
//  Desciption: An implementation of the transmissionField.h
////////////////////////////////////////////////////////////////////////////////

#include "transmissionField.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//													Functions Implementations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//	Function name:	ProcessAndAddNewBeacon	
//	Description:		Adds a new Beacon with "centerPoint" and 
//									"connectivityRadius", updates connections and Transmission
//									path.
//	Return value:		None
////////////////////////////////////////////////////////////////////////////////
void TransmissionField::ProcessAndAddNewBeacon(optional<cv::Point2d> centerPoint, int connectivityRadius)
{
	if (centerPoint)
	{
		try
		{
			shared_ptr<Beacon> newBeacon = shared_ptr<Beacon>(new Beacon(centerPoint, connectivityRadius, ++m_last_beacon_id));

			for (map<unsigned int, shared_ptr<Beacon>>::iterator it = m_beaconsMap.begin(); it != m_beaconsMap.end(); ++it)
			{
				UpdateConnections(it->second, newBeacon);
			}

			m_beaconsMap[newBeacon->GetID()] = newBeacon;
			UpdateTransmissionPath(newBeacon);
		}
		catch (...)
		{
			// TODO::YARON - Logger
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	Reset
//	Description:		Clear TransmissionField from Beacons
//	Return value:		None
////////////////////////////////////////////////////////////////////////////////
void TransmissionField::Reset()
{
	m_beaconsMap.clear();
	m_last_beacon_id = 0;
	m_smallest_path_length = Beacon::INVALID_DISTANCE;
	m_path_ids.clear();
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	IsEmpty
//	Description:		Checks if TransmissionField is empty from Beacons
//	Return value:		True - empty, False - there are Beacons
////////////////////////////////////////////////////////////////////////////////
bool TransmissionField::IsEmpty()
{
	return (m_beaconsMap.empty());
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	UpdateTransmissionPath
//	Description:		Updates Transmission Path with the new Beacon:
//									First try to update by the current exist path (heuristics),
//									if not succeeds, updates recursively
//	Return value:		None
////////////////////////////////////////////////////////////////////////////////
void TransmissionField::UpdateTransmissionPath(shared_ptr<Beacon> newBeacon)
{
	if (!IsNewIDAddedByExistPath(newBeacon->GetID()))
	{
		const float PATH_LENGTH(0.0f);

		m_path_ids.clear();
		m_smallest_path_length = 0;

		vector<unsigned int> transmissionPathIDs;
		unsigned long pathIncludedBeacons(FIRST_VALID_ID);

		UpdateTransmissionPathRec(FIRST_VALID_ID, INVALID_BEACON_ID, PATH_LENGTH, pathIncludedBeacons, transmissionPathIDs);
	}
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	UpdateConnections
//	Description:		Checks connection between "existBeacon" and "newBeacon"
//	Return value:		None
////////////////////////////////////////////////////////////////////////////////
void TransmissionField::UpdateConnections(shared_ptr<Beacon> existBeacon, shared_ptr < Beacon> newBeacon)
{
	try
	{
		existBeacon->CheckAndUpdateConnection(*newBeacon);
		newBeacon->CheckAndUpdateConnection(*existBeacon);
	}
	catch (...)
	{
		// TODO::YARON - Logger
	}
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	IsNewIDAddedByExistPath
//	Description:		Trying to update Transmission Path by the exist path
//									(by heuristics) 
//	Return value:		True - updated by heuristics, False - not updates
////////////////////////////////////////////////////////////////////////////////
bool TransmissionField::IsNewIDAddedByExistPath(unsigned int newID)
{
	bool addNewID(false);
	size_t pathNumOfIDs = m_path_ids.size();

	size_t idx(0);
	for (; idx < pathNumOfIDs && !addNewID; ++idx)
	{
		if (m_path_ids[idx] >= FIRST_VALID_ID && m_path_ids[idx] < m_last_beacon_id)
		{
			addNewID = m_beaconsMap[m_path_ids[idx]]->IsConnectedToOtherBeacon(newID);
		}
	}

	if (addNewID)
	{
		for (; idx < pathNumOfIDs; ++idx)
		{
			m_path_ids.pop_back();
		}

		m_path_ids.push_back(newID);
	}

	return (addNewID);
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	UpdateTransmissionPathRec
//	Description:		Updates the Transmission Path recursively:
//									Calling the function on every member of the current beacon's
//									connected beacons (and on and on...)
//									The "stop condition" is when the path got to "The Last Beacon"
//									The function make sure that a Beacon is not appear more than 
//									once at the path. 
//	Return value:		REACHED - Current iteration is the Last Beacon,
//									NOT_REACHED - It's not 
////////////////////////////////////////////////////////////////////////////////
TransmissionField::EReachedLastBeacon
TransmissionField::UpdateTransmissionPathRec(
	unsigned int currentBeaconID,
	unsigned int prevBeaconID,
	float pathLength,
	unsigned long pathIncludedBeacons,
	vector<unsigned int> transmissionPathIDs)
{
	if (currentBeaconID == m_last_beacon_id)
	{
		return (REACHED_LAST_BEACON);
	}

	// "pathIncludedBeacons" is a bit map to indicate if an ID is already included in the Transmission path
	if (NOT_INCLUDED == (pathIncludedBeacons & (1 << currentBeaconID)))
	{
		// Include this beacon in the path
		pathIncludedBeacons |= (1 << currentBeaconID);

		try
		{
			shared_ptr<Beacon> currentBeacon = m_beaconsMap[currentBeaconID];

			vector<unsigned int> currentBeaconConnections = currentBeacon->GetConnections();
			EReachedLastBeacon reachedLastBeacon(NOT_REACHED_LAST_BEACON);

			transmissionPathIDs.push_back(currentBeaconID);

			if (INVALID_BEACON_ID != prevBeaconID)
			{
				pathLength += Beacon::GetDistanceBetweenBeacons(*m_beaconsMap[prevBeaconID], *currentBeacon);
			}

			for (vector<unsigned int>::iterator it = currentBeaconConnections.begin(); it != currentBeaconConnections.end(); ++it)
			{
				reachedLastBeacon = UpdateTransmissionPathRec(*it, currentBeaconID, pathLength, pathIncludedBeacons, transmissionPathIDs);

				if (REACHED_LAST_BEACON == reachedLastBeacon)
				{
					float distance = Beacon::GetDistanceBetweenBeacons(*currentBeacon, *m_beaconsMap[m_last_beacon_id]);

					if (m_path_ids.empty() || (m_smallest_path_length > (pathLength + distance)))
					{
						m_smallest_path_length = pathLength + distance;
						transmissionPathIDs.push_back(m_last_beacon_id);
						m_path_ids = transmissionPathIDs;
					}
				}
			}
		}
		catch (...)
		{
			// TODO::YARON - Logger
		}
	}

	return (NOT_REACHED_LAST_BEACON);
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	GetBeacon
//	Description:		Gets Beacon by ID
//	Return value:		The Beacon that matches to "id" 
////////////////////////////////////////////////////////////////////////////////
shared_ptr<Beacon> TransmissionField::GetBeacon(unsigned int id)
{
	shared_ptr<Beacon> beacon(nullptr);

	if (id >= FIRST_VALID_ID && id <= m_last_beacon_id)
	{
		beacon = m_beaconsMap[id];
	}

	return (beacon);
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	GetFirstBeacon
//	Description:		Gets the first Beacon at Transmission Field
//	Return value:		The first Beacon 
////////////////////////////////////////////////////////////////////////////////
shared_ptr<Beacon> TransmissionField::GetFirstBeacon()
{
	return (GetBeacon(FIRST_VALID_ID));
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	GetLastBeacon
//	Description:		Gets the last Beacon at Transmission Field
//	Return value:		The last Beacon 
////////////////////////////////////////////////////////////////////////////////
shared_ptr<Beacon> TransmissionField::GetLastBeacon()
{
	return (GetBeacon(m_last_beacon_id));
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	GetNextBeacon
//	Description:		Gets the id's next Beacon at Transmission Field
//	Return value:		The id's next Beacon 
////////////////////////////////////////////////////////////////////////////////
shared_ptr<Beacon> TransmissionField::GetNextBeacon(unsigned int id)
{
	return (GetBeacon(id + 1));
}

////////////////////////////////////////////////////////////////////////////////
//	Function name:	GetPrevBeacon
//	Description:		Gets the id's prev Beacon at Transmission Field
//	Return value:		The id's prev Beacon 
////////////////////////////////////////////////////////////////////////////////
shared_ptr<Beacon> TransmissionField::GetPrevBeacon(unsigned int id)
{
	return (GetBeacon(id - 1));
}


