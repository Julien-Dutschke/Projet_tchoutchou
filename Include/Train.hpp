#ifndef TRAIN_HPP
# define TRAIN_HPP

# include <string>

enum class TrainState
{
	Stopped,
	Accelerating,
	Cruising,
	Braking                                                                                                                                                                                                                                                                             
};

class Train
{
	private:
		//identification 
		std::string	_name;
		static int 		_id;// initialiser a 0 dans le cpp
	
		
	
		//proprieter physique
		double _weightTons; // poid en tonnes
		double _frictionCoeff; // pour calculer la force de frottement
		double _AccelerationMaxKN;// acceleration max en kn
		double _BrakeMaxForceKN; // force de freinage max en kn

		//informmation sur le voyage
		std::string _departStation;
		std::string _arrivalStation;


		//information dynamique
		double _currentSpeedKMH;
		double _currentAccelerationKN;
		TrainState	_state;


		public:
		Train(std::string name,
			  double weightTons,
			  double frictionCoeff,
			  double accelerationMaxKN,
			  double brakeMaxForceKN,
			  std::string departStation,
			  std::string arrivalStation);
		~Train() = default;
		Train(Train const & cpy);
		Train& operator=(Train const& rhs);


		//Getters
		const std::string& getName() const {return _name;}
		double getWeightTons() const { return _weightTons; }
		double getFrictionCoeff() const {return _frictionCoeff; }
		double getAccelerationMaxKN() const { return _AccelerationMaxKN; }
		double getBrakeMaxForceKN() const { return _BrakeMaxForceKN; }
		double getCurrentSpeedKMH() const { return _currentSpeedKMH; }
		double getCurrentAccelerationKN() const { return _currentAccelerationKN; }
		
		TrainState getState() const;
		
		const std::string& getDepartStation() const;
		const std::string& getArrivalStation() const;

		
		//methodes pour la simulation





};

#endif // TRAIN_HPP
