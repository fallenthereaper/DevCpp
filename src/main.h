// LearnCPP_04_2024.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>


using pairList_t = std::vector<std::pair<std::string, int>>; // or typedef std::vector<std::pair<text_t, int>> pairList_t; //Gives a new identifier to an existing data type;
using boolean = bool;
using string = std::string;

struct Vec3 {

	float x;
	float y;
	float z;

	int getX() {
		return this->x;
	}

	int getY() {
		return this->y;
	}

	int getZ() {
		return this->z;
	}

	void setX(float x) {
		this->x = x;
	}

	void setY(float y) {
		this->y = y;
	}

	void setZ(float z) {
		this->z = z;
	}
};

struct Vec2 {

	float x;
	float y;

	int getX() {
		return this->x;
	}

	int getY() {
		return this->y;
	}

	void setX(float x) {
		this->x = x;
	}

	void setY(float y) {
		this->y = y;
	}
};

// TODO: Reference additional headers your program requires here.
