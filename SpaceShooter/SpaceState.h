#pragma once

#include <osgGA/GUIEventHandler>

#include "Universe.h"
#include "Follower.h"
#include "Misc.h"

using namespace osg;
using namespace osgGA;

namespace Shooter {

	typedef struct _gameData
	{
		Universe* universe;
		Follower* follower;
		double* simTime;
		double* simTimeDiff;
	} GameData;

	typedef struct _inputData
	{
		InputStateStamp inputState;

		int mouseX;
		int mouseY;
		int mouseXold;
		int mouseYold;
		int mouseXspeed_ret;
		int mouseYspeed_ret;
	} InputData;


	class SpaceState : public GUIEventHandler
	{
	public:
		SpaceState();

		void setGameData(GameData data);

		virtual void initialize() {}
		virtual SpaceState* update() { return 0; }

		void updateMouseMotion();
		void updateMousePosition(unsigned int x, unsigned int y);
		void assignInputState(SpaceState* state);
		void flushEvents();

		InputData getInputData();
		InputStateStamp getInputStateStamp();

		bool keyDown(int key);
		bool keyHit(int key);
		bool mouseDown(int button);
		bool mouseHit(int button);
		int getMouseXspeed();
		int getMouseYspeed();


	protected:
		Universe* m_universe;
		Follower* m_follower;

		double* m_simTime;
		double* m_simTimeDiff;

	private:
		// input events
		InputData m_input;

		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
		virtual void accept(osgGA::GUIEventHandlerVisitor& v) { v.visit(*this); }
	};

}