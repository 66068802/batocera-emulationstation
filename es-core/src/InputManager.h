#pragma once
#ifndef ES_CORE_INPUT_MANAGER_H
#define ES_CORE_INPUT_MANAGER_H

#include <SDL_joystick.h>
#include <map>
#include <pugixml/src/pugixml.hpp>

class InputConfig;
class Window;
union SDL_Event;

//you should only ever instantiate one of these, by the way
class InputManager
{
private:
	InputManager();

	static InputManager* mInstance;

	static const int DEADZONE = 23000;

	void loadDefaultKBConfig();

	std::map<std::string, int> mJoysticksInitialValues;
	std::map<SDL_JoystickID, SDL_Joystick*> mJoysticks;
	std::map<SDL_JoystickID, InputConfig*> mInputConfigs;
	InputConfig* mKeyboardInputConfig;
	InputConfig* mCECInputConfig;

	std::map<SDL_JoystickID, int*> mPrevAxisValues;

        // batocera
	std::map<int, int> m_lastKnownPlayersDeviceIndexes;
	std::map<int, InputConfig*> computePlayersConfigs();

	bool initialized() const;

	void addJoystickByDeviceIndex(int id);
	void removeJoystickByJoystickID(SDL_JoystickID id);
	bool loadInputConfig(InputConfig* config); // returns true if successfully loaded, false if not (or didn't exist)

    // batocera
    void clearJoystick();
    void addAllJoysticks();

	bool tryLoadInputConfig(std::string path, InputConfig* config, bool allowApproximate = true);

public:
	virtual ~InputManager();

	static InputManager* getInstance();

	void writeDeviceConfig(InputConfig* config);
	void doOnFinish();
	static std::string getConfigPath();
	static std::string getTemporaryConfigPath();

	void init();
	void deinit();

	int getNumJoysticks();
	int getAxisCountByDevice(int deviceId);
	const std::map<SDL_JoystickID, SDL_Joystick*>& getJoysticks() { return  mJoysticks; } // batocera
	int getButtonCountByDevice(int deviceId);
	int getNumConfiguredDevices();

	std::string getDeviceGUIDString(int deviceId);

	InputConfig* getInputConfigByDevice(int deviceId);

	bool parseEvent(const SDL_Event& ev, Window* window);
	std::string configureEmulators(); // batocera

	// information about last association players/pads // batocera
	std::map<int, int> lastKnownPlayersDeviceIndexes();
	void computeLastKnownPlayersDeviceIndexes();
};

#endif // ES_CORE_INPUT_MANAGER_H
