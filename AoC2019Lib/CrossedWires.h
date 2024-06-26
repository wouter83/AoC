#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "Point.h"
#include "Segment.h"

struct Command {
	char command;
	unsigned int count;
};

class CrossedWires
{
public:

	CrossedWires() =default;

	bool RunWires(int& closedCross, int& shortestCross);
	void LoadWires(std::string& a, std::string& b);

	bool AddWire(std::vector<Command> commands, std::vector<Segment>& wire);

private:
	std::vector<Command> parse(const std::string& str);
	bool intersection(Segment& segA, Segment& segB, Point& intersect);
	int manhattLength(const Point& a, const Point& b);

	unsigned int mColSize = 0;
	unsigned int mRowSize = 0;

	std::vector<Segment> wireA;
	std::vector<Segment> wireB;
};