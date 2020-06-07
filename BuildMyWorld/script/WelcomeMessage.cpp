#include <gazebo/gazebo.hh> // Standard Gazebo Library Import

namespace gazebo
{

class WorldPluginMyRobot : public WorldPlugin
	{
	
	public: WorldPluginMyRobot() : WorldPlugin()
		{
		printf("Welcome to Project One! \n");
		}
	
	// Loading Physics Engine
	public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
	{}

};

//Registering the World Plugin with Simulator
GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot)

}
