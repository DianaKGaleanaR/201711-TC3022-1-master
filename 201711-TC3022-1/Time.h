#pragma once
#include <chrono>

// A high resolution clock
typedef std::chrono::steady_clock Clock;

// A second
typedef std::chrono::seconds TimeInSeconds;

// A second with millisecond precision, represented as a double.
typedef std::chrono::duration<double> TimeInMilliseconds;

class Time
{
public:
	// Initialize the resources needed to measure time
	static void Init();
	// Update values of ElapsedTime and DeltaTime
	static void Tick();

	// Get the time, in seconds, since the last call to Time::Init().
	static TimeInSeconds GetElapsedTime();
	// Get the time, in seconds
	static TimeInMilliseconds GetDeltaTime();



private:
	// Private constructor. Time should not be constructed as an object.
	Time();

	// The start point when the application began measuring time.
	static Clock::time_point StartPoint;
	// 
	static Clock::time_point LastTime;

	// The elapsed time since the last call to Time::Tick
	static TimeInMilliseconds DeltaTime;
};