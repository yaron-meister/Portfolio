////////////////////////////////////////////////////////////////////////////////
//  File name:  transmissionField.cpp
//  Developer:  Yaron Meister
//  Date:       26.11.2021
//  Desciption: An implementation of the transmissionField.h
////////////////////////////////////////////////////////////////////////////////

#include "transmissionField.h"


////////////////////////////////////////////////////////////////////////////////
//													Functions Implementations
////////////////////////////////////////////////////////////////////////////////
TransmissionField::~TransmissionField()
{
    // Free all Beacons
    for (std::map<unsigned int, Beacon*>::iterator it = m_beaconsMap.begin();
      it != m_beaconsMap.end(); ++it)
    {
      delete it->second;
      it->second = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////
void TransmissionField::ProcessAndAddNewBeacon(std::optional<cv::Point2d> center_point, int connectivity_radius)
{
  if (center_point)
  {
    try
    {
      UpdateTransmissionPath(new Beacon(center_point, connectivity_radius, ++m_last_beacon_id));
    }
    catch (...)
    {
      // TODO::YARON - Logger
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
void TransmissionField::UpdateTransmissionPath(Beacon* new_beacon)
{
    if (nullptr != new_beacon)
    {
        for (std::map<unsigned int, Beacon*>::iterator it = m_beaconsMap.begin(); it != m_beaconsMap.end(); ++it)
        {
          UpdateConnections(it->second, new_beacon);
        }
      
        int new_id = new_beacon->GetID();
        if (new_id >= 0)
        {
            const float PATH_LENGTH(0.0f);

            m_beaconsMap[new_id] = new_beacon;
            m_last_beacon_id = new_beacon->GetID();

            std::vector<unsigned int> transmission_path_ids;
            unsigned long path_included_beacons(FIRST_VALID_ID);

            UpdateTransmissionPathRec(FIRST_VALID_ID, INVALID_BEACON_ID, PATH_LENGTH, path_included_beacons, transmission_path_ids);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void TransmissionField::UpdateConnections(Beacon* exist_beacon, Beacon* new_beacon)
{
  try
  {
    exist_beacon->CheckAndUpdateConnection(*new_beacon);
    new_beacon->CheckAndUpdateConnection(*exist_beacon);
  }
  catch (...)
  {
    // TODO::YARON - Logger
  }
}

////////////////////////////////////////////////////////////////////////////////
TransmissionField::EReachedLastBeacon	
TransmissionField::UpdateTransmissionPathRec(
  unsigned int current_beacon_id,
  unsigned int prev_beacon_id,
  float path_length,
  unsigned long path_included_beacons,
  std::vector<unsigned int> transmission_path_ids)
{
  if (current_beacon_id == m_last_beacon_id)
  {
    return (REACHED_LAST_BEACON);
  }

  // TODO::YARON - Explain about path_included_beacons
  if (NOT_INCLUDED == (path_included_beacons & (1 << current_beacon_id)))
  {
      // Include this beacon in the path
      path_included_beacons |= (1 << current_beacon_id);

      try
      {
          Beacon* current_beacon = m_beaconsMap[current_beacon_id];

          std::vector<unsigned int> current_beacon_connections = current_beacon->GetConnections();
          EReachedLastBeacon reached_last_beacon(NOT_REACHED_LAST_BEACON);

          transmission_path_ids.push_back(current_beacon_id);

          if (INVALID_BEACON_ID != prev_beacon_id)
          {
              path_length += Beacon::GetDistanceBetweenBeacons(*m_beaconsMap[prev_beacon_id], *current_beacon);
          }

          for (std::vector<unsigned int>::iterator it = current_beacon_connections.begin(); it != current_beacon_connections.end(); ++it)
          {
              reached_last_beacon = UpdateTransmissionPathRec(*it, current_beacon_id, path_length, path_included_beacons, transmission_path_ids);

              if (REACHED_LAST_BEACON == reached_last_beacon)
              {
                  float distance = Beacon::GetDistanceBetweenBeacons(*current_beacon, *m_beaconsMap[m_last_beacon_id]);

                  if (m_path_ids.empty() || (m_smallest_path_length > (path_length + distance)))
                  {
                      m_smallest_path_length = path_length + distance;
                      transmission_path_ids.push_back(m_last_beacon_id);
                      m_path_ids = transmission_path_ids;
                  }
              }
          }
      }
      catch (...)
      {
        // TODO::YARON - Logger
      }
  }

  // TODO::YARON - Check indentations

  return (NOT_REACHED_LAST_BEACON);
}

////////////////////////////////////////////////////////////////////////////////
Beacon* TransmissionField::GetBeacon(unsigned int id)
{
    Beacon* beacon(nullptr);

    if (id >= FIRST_VALID_ID && id <= m_last_beacon_id)
    {
        beacon = m_beaconsMap[id];
    }

    return (beacon);
}

////////////////////////////////////////////////////////////////////////////////
Beacon* TransmissionField::GetFirstBeacon()
{
    return (GetBeacon(FIRST_VALID_ID));
}

////////////////////////////////////////////////////////////////////////////////
Beacon* TransmissionField::GetLastBeacon()
{
    return (GetBeacon(m_last_beacon_id));
}

////////////////////////////////////////////////////////////////////////////////
Beacon* TransmissionField::GetNextBeacon(unsigned int id)
{
    return (GetBeacon(id + 1));
}

////////////////////////////////////////////////////////////////////////////////
Beacon* TransmissionField::GetPrevBeacon(unsigned int id)
{
    return (GetBeacon(id - 1));
}


