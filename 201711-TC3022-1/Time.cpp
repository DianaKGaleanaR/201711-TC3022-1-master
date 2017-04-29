// This file is part of the 'OpenGL Base Project' project which is released under the MIT license.
// See file License.txt or go to http://opensource.org/licenses/MIT for full license details.

#include "Time.h"

// This file contains the definition of one class, Time.

// Includes
// This project
// Third-party libraries
// C++ standard libraries

// Class member definition
Clock::time_point Time::StartPoint;
Clock::time_point Time::LastTime;
TimeInMilliseconds Time::DeltaTime;

// Initialize the resources needed to measure time
Time::Time()
{
	StartPoint;
	LastTime;
	DeltaTime;
}

void Time::Init()
{
	// Mark the start of the clock
	StartPoint = Clock::now();
	// There is no last time
	LastTime = StartPoint;

	// Set the delta time to 0
	DeltaTime = TimeInMilliseconds(0);
}

// Update values of ElapsedTime and DeltaTime
void Time::Tick()
{
	auto now = Clock::now();

	DeltaTime = std::chrono::duration_cast<TimeInMilliseconds>(now - LastTime);
	
	LastTime = now;
}

// Get the time, in seconds, since the last call to Time::Init().
TimeInSeconds Time::GetElapsedTime()
{
	return std::chrono::duration_cast<TimeInSeconds>(Clock::now() - StartPoint);
}

// Get the time, in seconds, since the last call to Time::GetDeltaTime().
TimeInMilliseconds Time::GetDeltaTime()
{
	return DeltaTime;
}

