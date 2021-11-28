////////////////////////////////////////////////////////////////////////////////
//  File name:  transmissionField.h
//  Developer:  Yaron Meister
//  Date:       26.11.2021
//  Desciption: A header file for the Transmission Path data processor
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "beacon.h"

#include <map>

// A class to process the data of all exist beacons and calculate Transmission Path
class TransmissionField
{
public:
	const unsigned int INVALID_BEACON_ID	= 0;
	const unsigned int FIRST_VALID_ID			= 1;

	enum EReachedLastBeacon
	{
			NOT_REACHED_LAST_BEACON,
			REACHED_LAST_BEACON
	};

	enum EIncludedInPath
	{
			NOT_INCLUDED,
			INCLUDED
	};

	// CTor
	TransmissionField() : m_last_beacon_id(INVALID_BEACON_ID), m_smallest_path_length(0){}

	// DTor
	~TransmissionField();

	// Methods

	void											ProcessAndAddNewBeacon(std::optional<cv::Point2d> center_point, int connectivity_radius);
	void											Reset();
	bool											IsEmpty();
	unsigned int							GetLastBeaconId() const { return m_last_beacon_id; }
	std::vector<unsigned int> GetTransmissionPath() const { return m_path_ids; }

	// Beacons iterations
	Beacon*	GetFirstBeacon();
	Beacon*	GetLastBeacon();
	Beacon*	GetNextBeacon(unsigned int id);
	Beacon* GetPrevBeacon(unsigned int id);
	Beacon*	GetBeacon(unsigned int id);

private:
	// Methods
	void UpdateTransmissionPath(Beacon* new_beacon);
	void UpdateConnections(Beacon* exist_beacon, Beacon* new_beacon);

	EReachedLastBeacon	UpdateTransmissionPathRec(
		unsigned int current_beacon_id,
		unsigned int prev_beacon_id,
		float pathLength, 
		unsigned long path_included_beacons, 
		std::vector<unsigned int> transmission_path_ids);

	// Members
	std::map<unsigned int, Beacon*>	m_beaconsMap;
	unsigned int										m_last_beacon_id;
	float														m_smallest_path_length;
	std::vector<unsigned int>				m_path_ids;
};