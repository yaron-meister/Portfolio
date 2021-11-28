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
void TransmissionField::ProcessAndAddNewBeacon(optional<cv::Point2d> center_point, int connectivity_radius)
{
  if (center_point)
  {
    try
    {
        shared_ptr<Beacon> new_beacon = shared_ptr<Beacon>(new Beacon(center_point, connectivity_radius, ++m_last_beacon_id));
      
        for (map<unsigned int, shared_ptr<Beacon>>::iterator it = m_beaconsMap.begin(); it != m_beaconsMap.end(); ++it)
        {
          UpdateConnections(it->second, new_beacon);
        }

        m_beaconsMap[new_beacon->GetID()] = new_beacon;
        UpdateTransmissionPath(new_beacon);
    }
    catch (...)
    {
      // TODO::YARON - Logger
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
void TransmissionField::Reset()
{
    m_beaconsMap.clear();
    m_last_beacon_id = 0;
    m_smallest_path_length = Beacon::INVALID_DISTANCE;
    m_path_ids.clear();
}

////////////////////////////////////////////////////////////////////////////////
bool TransmissionField::IsEmpty()
{
  return (m_beaconsMap.empty());
}

////////////////////////////////////////////////////////////////////////////////
void TransmissionField::UpdateTransmissionPath(shared_ptr<Beacon> new_beacon)
{
    if (!IsNewIDAddedByExistPath(new_beacon->GetID()))
    {
        const float PATH_LENGTH(0.0f);

        m_path_ids.clear();
        m_smallest_path_length = 0;

        vector<unsigned int> transmission_path_ids;
        unsigned long path_included_beacons(FIRST_VALID_ID);

        UpdateTransmissionPathRec(FIRST_VALID_ID, INVALID_BEACON_ID, PATH_LENGTH, path_included_beacons, transmission_path_ids);
    }
}

////////////////////////////////////////////////////////////////////////////////
void TransmissionField::UpdateConnections(shared_ptr<Beacon> exist_beacon, shared_ptr < Beacon> new_beacon)
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
bool TransmissionField::IsNewIDAddedByExistPath(unsigned int new_id)
{
  bool addNewID(false);
  size_t pathNumOfIDs = m_path_ids.size();

  size_t idx(0);
  for (; idx < pathNumOfIDs && !addNewID; ++idx)
  {
    if (m_path_ids[idx] >= FIRST_VALID_ID && m_path_ids[idx] < m_last_beacon_id)
    {
      addNewID = m_beaconsMap[m_path_ids[idx]]->IsConnectedToOtherBeacon(new_id);
    }
  }

  if (addNewID)
  {
    for (; idx < pathNumOfIDs; ++idx)
    {
      m_path_ids.pop_back();
    }

    m_path_ids.push_back(new_id);
  }

  return (addNewID);
}

////////////////////////////////////////////////////////////////////////////////
TransmissionField::EReachedLastBeacon	
TransmissionField::UpdateTransmissionPathRec(
  unsigned int current_beacon_id,
  unsigned int prev_beacon_id,
  float path_length,
  unsigned long path_included_beacons,
  vector<unsigned int> transmission_path_ids)
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
          shared_ptr<Beacon> current_beacon = m_beaconsMap[current_beacon_id];

          vector<unsigned int> current_beacon_connections = current_beacon->GetConnections();
          EReachedLastBeacon reached_last_beacon(NOT_REACHED_LAST_BEACON);

          transmission_path_ids.push_back(current_beacon_id);

          if (INVALID_BEACON_ID != prev_beacon_id)
          {
              path_length += Beacon::GetDistanceBetweenBeacons(*m_beaconsMap[prev_beacon_id], *current_beacon);
          }

          for (vector<unsigned int>::iterator it = current_beacon_connections.begin(); it != current_beacon_connections.end(); ++it)
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
shared_ptr<Beacon> TransmissionField::GetFirstBeacon()
{
    return (GetBeacon(FIRST_VALID_ID));
}

////////////////////////////////////////////////////////////////////////////////
shared_ptr<Beacon> TransmissionField::GetLastBeacon()
{
    return (GetBeacon(m_last_beacon_id));
}

////////////////////////////////////////////////////////////////////////////////
shared_ptr<Beacon> TransmissionField::GetNextBeacon(unsigned int id)
{
    return (GetBeacon(id + 1));
}

////////////////////////////////////////////////////////////////////////////////
shared_ptr<Beacon> TransmissionField::GetPrevBeacon(unsigned int id)
{
    return (GetBeacon(id - 1));
}


