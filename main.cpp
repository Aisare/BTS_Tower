#include "BTS_Tower.h"
/// <summary>
/// GPS coordinates for the formation of towers
/// </summary>
std::vector<std::pair<double, double>> GPSCord =
{
	{55.753928,37.604422},
	{55.749066,37.609262},
	{55.752852,37.626046},
	{55.749854,37.619587},
	{55.755637,37.607245},
	{55.755442,37.612428},
	{55.748630,37.617184},
	{55.754269,37.603903},
	{55.754657,37.608545},
	{55.753579,37.624015},
	{55.756204,37.618499},
	{55.752496,37.629609},
	{55.758298,37.614272},
	{55.753298,37.627634},
	{55.758403,37.624160},
	{55.753343,37.619241},
	{55.755191,37.617302},
	{55.753388,37.616372},
	{55.753393,37.630002},
	{55.755842,37.614485},
	{55.754533,37.614686},
	{55.754683,37.613000},
	{55.755997,37.615416},
	{55.762946,37.611467},
	{55.755566,37.618441},
	{55.752871,37.620866},
	{55.753684,37.603072},
	{55.759270,37.611550},
	{55.752800,37.631564},
	{55.755328,37.621093},
	{55.762543,37.608612},
	{55.758178,37.615702},
	{55.754577,37.629914},
	{55.755477,37.609956},
	{55.764485,37.613655},
	{55.754770,37.615935},
	{55.750316,37.620250},
	{55.750511,37.608043},
	{55.752318,37.619195},
	{55.753470,37.615363},
	{55.759353,37.603458},
	{55.759043,37.615446},
	{55.754827,37.607241},
	{55.757552,37.617917},
	{55.753319,37.632062},
	{55.753617,37.622557},
	{55.755797,37.617286},
	{55.758509,37.608016},
	{55.752346,37.611498},
	{55.757016,37.628471},
	{55.763425,37.610788},
	{55.756084,37.617223},
	{55.753392,37.611870},
	{55.752713,37.616477},
	{55.754667,37.614431},
	{55.755591,37.619930},
	{55.751639,37.622624},
	{55.755225,37.614571},
	{55.758717,37.618761},
	{55.760153,37.627040},
	{55.757833,37.622927},
	{55.756712,37.626582},
	{55.755731,37.616770},
	{55.755232,37.604990},
	{55.753440,37.609005},
	{55.758011,37.611499},
	{55.754890,37.615599},
	{55.753550,37.617185},
	{55.749507,37.605999},
	{55.762606,37.614074},
	{55.754412,37.630631},
	{55.754463,37.622016},
	{55.752098,37.614806},
	{55.759805,37.621102},
	{55.754700,37.616570},
	{55.750096,37.606175},
	{55.754249,37.617925},
	{55.759157,37.615028},
	{55.758683,37.602914},
	{55.761498,37.615634},
	{55.752044,37.619682},
	{55.752005,37.618197},
	{55.757604,37.616435},
	{55.753091,37.616130},
	{55.758644,37.625388},
	{55.751989,37.604004},
	{55.759908,37.623889},
	{55.755062,37.629142},
	{55.762604,37.614295},
	{55.751818,37.626965},
	{55.751611,37.620739},
	{55.752625,37.619701},
	{55.757297,37.615714},
	{55.750902,37.604583},
	{55.751742,37.610039},
	{55.752170,37.606420},
	{55.753687,37.625636},
	{55.758199,37.607462},
	{55.747775,37.618474},
	{55.753765,37.618187},
};
/// <summary>
/// the function of forming towers based on GPS coordinates
/// </summary>
/// <param name="gps_cord">GPS coordinates</param>
/// <returns>vector with formed towers</returns>
std::vector<BTS_Tower> Generate_Tower(std::vector<std::pair<double, double>> gps_cord)
{
	std::vector<BTS_Tower> resultGen;
	int index = 13567;
	for (const auto& itm : gps_cord)
	{
		const auto& [lat, log] = itm;
		resultGen.push_back(BTS_Tower(lat, log, ++index));
	}
	return std::move(resultGen);
}

void main()
{
	/*
	Example of searching for the nearest tower relative to the user's coordinates
	*/
	auto Towers = Generate_Tower(GPSCord);
	std::pair<double, double> userPos =
	{
		55.759270,37.609956
	};

	BTS_Tower closestTower = findClosestTower(Towers, userPos);

	const auto& [lat, lon, sign, numb] = closestTower.GetTowerState();

	if (lat == ERROR_DISTANCE && lon == ERROR_DISTANCE)
		std::cout << "Not found tower" << std::endl;
	else
	{
		std::cout << "Found tower: " << std::endl
			<< "Latitude: " << lat << std::endl
			<< "Longitude: " << lon << std::endl
			<< "Signal Strength: " << sign << std::endl
			<< "Numb: " << numb << std::endl;
	}
}