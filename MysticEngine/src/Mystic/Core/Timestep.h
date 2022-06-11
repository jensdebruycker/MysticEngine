#pragma once

namespace Mystic {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f) : _time(time)
		{

		}

		operator float() const { return _time; }

		float GetSeconds() const { return _time; }
		float GetMilliseconds() const { return _time * 1000; }
	private:
		float _time;
	};

}