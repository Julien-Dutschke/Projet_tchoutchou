#include "../Include/Train.hpp"

int Train::_id = 0;

Train::Train(std::string name,
			   double weightTons,
			   double frictionCoeff,
			   double accelerationMaxKN,
			   double brakeMaxForceKN,
			   std::string departStation,
			   std::string arrivalStation)
	: _name(name),
	  _weightTons(weightTons),
	  _frictionCoeff(frictionCoeff),
	  _AccelerationMaxKN(accelerationMaxKN),
	  _BrakeMaxForceKN(brakeMaxForceKN),
	  _departStation(departStation),
	  _arrivalStation(arrivalStation),
	  _currentSpeedKMH(0.0),
	  _currentAccelerationKN(0.0),
	  _state(TrainState::Stopped)
{
	_id++;
}


Train::Train(Train const & cpy)
	: _name(cpy._name),
	  _weightTons(cpy._weightTons),
	  _frictionCoeff(cpy._frictionCoeff),
	  _AccelerationMaxKN(cpy._AccelerationMaxKN),
	  _BrakeMaxForceKN(cpy._BrakeMaxForceKN),
	  _departStation(cpy._departStation),
	  _arrivalStation(cpy._arrivalStation),
	  _currentSpeedKMH(cpy._currentSpeedKMH),
	  _currentAccelerationKN(cpy._currentAccelerationKN),
	  _state(cpy._state)
{
	_id++;
}

Train& Train::operator=(Train const& rhs)
{
	if (this != &rhs)
	{
		_name = rhs._name;
		_weightTons = rhs._weightTons;
		_frictionCoeff = rhs._frictionCoeff;
		_AccelerationMaxKN = rhs._AccelerationMaxKN;
		_BrakeMaxForceKN = rhs._BrakeMaxForceKN;
		_departStation = rhs._departStation;
		_arrivalStation = rhs._arrivalStation;
		_currentSpeedKMH = rhs._currentSpeedKMH;
		_currentAccelerationKN = rhs._currentAccelerationKN;
		_state = rhs._state;
	}
	return *this;
}