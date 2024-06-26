#include "pch.h"
#include "OrbitMap.h"
#include <algorithm>

OrbitMap::OrbitMap(const std::string& str)
{
	auto orbitsPairs = Generic::splitString(str, "\n");


	for (const auto& orbit : orbitsPairs)
	{
		const auto& bodies = Generic::splitString(orbit, ")");
		
		std::string ownName = bodies[1];
		std::string orbitName = bodies[0];

		Planet* pOwn = nullptr;
		Planet* pOrbit = nullptr;

		for (Planet* planet : mPLanets)
		{
			if (planet->name == ownName)
			{
				pOwn = planet;
			}
			if (planet->name == orbitName)
			{
				pOrbit = planet;
			}
		}


		if (!pOrbit)
		{
			pOrbit = new Planet();
			pOrbit->name = orbitName;
			mPLanets.push_back(pOrbit);
		}

		if (!pOwn)
		{
			pOwn = new Planet();
			pOwn->name = ownName;
			mPLanets.push_back(pOwn);
		}

		pOwn->orbit = pOrbit;
	}
}

OrbitMap::~OrbitMap()
{
	for (Planet* planet : mPLanets)
	{
		delete planet;
	}
}

uint OrbitMap::GetShortest()
{
	Planet* pYou = nullptr;
	Planet* pSan = nullptr;
	for (Planet* planet : mPLanets)
	{
		if (planet->name == "YOU")
			pYou = planet;
		if (planet->name == "SAN")
			pSan = planet;
	}

	if (!pSan || !pYou) return 0;

	std::vector<Planet*> planetsYou;
	pYou->GetOrbits(planetsYou);
	std::vector<Planet*> planetsSan;
	pSan->GetOrbits(planetsSan);

	std::vector<Planet*> toRemove;

	for (Planet* p : planetsYou)
	{
		if (std::find(planetsSan.begin(), planetsSan.end(), p) != planetsSan.end())
		{
			toRemove.push_back(p);
		}
	}
	for (Planet* p : toRemove)
	{
		auto san = std::find(planetsSan.begin(), planetsSan.end(), p);
		planetsSan.erase(san);
		auto you = std::find(planetsYou.begin(), planetsYou.end(), p);
		planetsYou.erase(you);
	}
	return planetsSan.size() + planetsYou.size();
}

uint OrbitMap::GetOrbit()
{
	std::vector<Planet*> planets;
	for (Planet* planet : mPLanets)
	{
		planet->GetOrbits(planets);
	}
	return planets.size();
}

void Planet::GetOrbits(std::vector<Planet*>& planets)
{
	if (orbit)
	{
		planets.push_back(orbit);
		orbit->GetOrbits(planets);
	}
}
