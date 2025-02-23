#ifndef BTSTOWERH
#define BTSTOWERH

#include <cmath>
#include <time.h>
#include <thread>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#define M_PI 3.14159265358979323846
#define ERROR_DISTANCE 99999999

/// <summary>
/// Base Transceiver Station Tower - class imitation of a mobile network base station
/// </summary>
class BTS_Tower
{
	/// <summary>
	/// latitude tower
	/// </summary>
	double latitude;
	/// <summary>
	/// longitude tower
	/// </summary>
	double longitude;
	/// <summary>
	/// signal strength tower
	/// </summary>
	int signal_strength;
	/// <summary>
	/// number tower
	/// </summary>
	int Number;
public:
	/// <summary>
	/// the default constructor with the wrong location
	/// </summary>
	BTS_Tower() : latitude(ERROR_DISTANCE), longitude(ERROR_DISTANCE), signal_strength(-99999), Number(-1) {}
	/// <summary>
	/// A constructor for adding a base tower at the specified latitude and longitude coordinates generates a random signal strength.
	/// </summary>
	/// <param name="_lat">specified latitude tower</param>
	/// <param name="_lon">specified longitude tower</param>
	/// <param name="number">number tower</param>
	BTS_Tower(double _lat, double _lon,int number) : latitude(_lat), longitude(_lon), Number(number)
	{
		srand(time(0));
		signal_strength = (-1 * (50 + rand() % 50));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		std::cout << latitude <<"  "<< longitude <<" "<< signal_strength<<" " << Number << std::endl;
	}
	/// <summary>
	/// Gets the current status of the BTS tower.
	/// </summary>
	/// <returns>
	/// Tuple (latitude, longitude, signal_strength, Number), where:
	/// - latitude of the tower,
	/// - longitude of the tower,
	/// - signal strength (from -50 to -100 dBm),
	/// - the number of the tower.
	/// </returns>
	std::tuple<double, double, int,int> GetTowerState() const
	{
		return { latitude,longitude,signal_strength,Number };
	}
	
};
/// <summary>
/// converting degrees to radians
/// </summary>
/// <param name="degree">degrees for conversion</param>
/// <returns>radians</returns>
constexpr double toRadians(double degree)
{
	return degree * M_PI / 180.0;
}
/// <summary>
/// calculating the distance using the haversine formula
/// </summary>
/// <param name="lat1">latitude point 1</param>
/// <param name="lon1">longitude point 1</param>
/// <param name="lat2">latitude point 2</param>
/// <param name="lon2">longitude point 2</param>
/// <returns></returns>
double haversineDistance(double lat1, double lon1, double lat2, double lon2)
{
	constexpr double EARTH_RADIUS = 6371.0;
	double dLat = toRadians(lat2 - lat1);
	double dLon = toRadians(lon2 - lon1);

	double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
		std::cos(toRadians(lat1)) * std::cos(toRadians(lat2)) *
		std::sin(dLon / 2) * std::sin(dLon / 2);

	double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
	return EARTH_RADIUS * c;
}
/// <summary>
/// the function of searching for the nearest tower
///
///1) first, select towers with a signal level from - 50 to - 80 and immediately calculate the distance to the user
///2) we sort the found towers
///3) using binary search, we are looking for the Closest tower
/// </summary>
/// <param name="towers">all towers</param>
/// <param name="user_location">user location</param>
/// <returns>closest tower for user</returns>
BTS_Tower findClosestTower(const std::vector<BTS_Tower>& towers, std::pair<double, double> user_location)
{
	std::vector<std::pair<double, BTS_Tower>> filteredTowers;

	const auto& [user_lat, user_lon] = user_location;

	for (const auto& tower : towers)
	{
		const auto& [tlat, tlon, tsig, _] = tower.GetTowerState();

		if (tsig >= -80 && tsig <= -50)
		{
			double distance = haversineDistance(user_lat, user_lon, tlat, tlon);
			filteredTowers.push_back({ distance, tower });
		}
	}

	if (filteredTowers.empty())
		return BTS_Tower();

	std::sort(filteredTowers.begin(), filteredTowers.end(), [](const auto& a, const auto& b) { return a.first < b.first; });

	int left = 0;
	int right = filteredTowers.size() - 1;
	double minDistance = ERROR_DISTANCE;
	BTS_Tower closestTower;

	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		double dist = filteredTowers[mid].first;

		if (dist < minDistance)
		{
			minDistance = dist;
			closestTower = filteredTowers[mid].second;
		}

		if (dist > 0)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	return closestTower;
}
#endif

