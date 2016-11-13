#include "glew/glew.h"

#include "model/BoxModel.hpp"
#include "model/WallModel.hpp"
#include "model/InclinedPlaneModel.hpp"
#include "model/BallModel.hpp"

#include "physics/MaterialPoly.hpp"
#include "physics/RigidPoly.hpp"
#include "physics/Wall.hpp"
#include "physics/InclinedPlane.hpp"

#include "graphics/MaterialPolyRenderer.hpp"
#include "graphics/RigidPolyRenderer.hpp"
#include "graphics/WallRenderer.hpp"
#include "graphics/InclinedPlaneRenderer.hpp"

#include "Introspector.hpp"
#include "Recorder.hpp"

#include <gpx/log.hpp>
#include <gpx/math.hpp>

#include <gpx/phy/PhyLog.hpp>
#include <gpx/phy2d/cnewton/pmepp2_s/Collider.hpp>

#include <gpx/gra/GraLog.hpp>
#include <gpx/gra/RenderWindow.hpp>
#include <gpx/gra2d/Scene.hpp>
#include <gpx/gra2d/View.hpp>

#include <iostream>

#define NNS pmepp2_s	//cnewton namespace

int main(int argc, char* argv[])
{
	GPX_UNUSED(argc);
	GPX_UNUSED(argv);

	//default window width and height
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
//	const int WINDOW_WIDTH = 80;
//	const int WINDOW_HEIGHT = 60;
	const double SCENE_HEIGHT = 20.0; //let scene be 20 meters tall
	const double SCENE_WIDTH = (static_cast<gpx::real_t>(WINDOW_WIDTH) / static_cast<gpx::real_t>(WINDOW_HEIGHT)) * SCENE_HEIGHT;
	const char * DUMP_FILE = "frames.gpx";

	sf::Event event;
	sf::Clock phyClock;
	double phyTime;

#ifndef NDEBUG
	std::cout << "note: debug mode is on, define NDEBUG macro to surpass" << std::endl;
#endif /* NDEBUG */

	//set up log
	gpx::log::Log::Instance().combinedStream().attachStream(std::cout);
	gpx::phy::PhyLog::Instance().attachLog(gpx::log::Log::Instance());
	gpx::gra::GraLog::Instance().attachLog(gpx::log::Log::Instance());

	sf::WindowSettings settings;
	settings.DepthBits = 24;
	settings.StencilBits = 8;
	settings.AntialiasingLevel = 0;

	gpx::gra::RenderWindow win(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Phy Demo", sf::Style::Close | sf::Style::Resize, settings);
	gpx::gra2d::Scene scene(SCENE_WIDTH, SCENE_HEIGHT);
    gpx::gra2d::View view(win, scene);

//	gpx::phy2d::NewtonCollider newtonCollider;
	gpx::phy2d::cnewton::NNS::Collider newtonCollider;
//	newtonCollider.setSubsequentCollisionLimit(20);

	NNS::Introspector introspector(win, view);
	newtonCollider.setIntrospector(introspector);

	Recorder blackBox(100);

	InclinedPlaneModel incPlaneModel(10.0, 4.0);
	NNS::InclinedPlane incPlane(incPlaneModel);
	incPlane.setName("incPlane");
//	incPlane.setMaterial(22);
	NNS::InclinedPlaneRenderer incPlaneRenderer(incPlane);
	incPlane.setPos(10.0, 1.0);
//	scene.add(& incPlaneRenderer);
//	newtonCollider.addFixed(& incPlane);
	introspector.associate(& incPlane, & incPlaneRenderer);

	WallModel bWallModel(SCENE_WIDTH - 2.0, WallModel::BOTTOM);
	NNS::Wall bWall(bWallModel);
	bWall.setName("bWall");
	NNS::WallRenderer bWallRenderer(bWall);
	bWall.setPos(1.0, 1.0);
	scene.add(& bWallRenderer);
	newtonCollider.addFixed(& bWall);
//	ff->mapToGlobal(gpx::math::Vector<2>(2.3, 12.9));	//tmp
	introspector.associate(& bWall, & bWallRenderer);

	WallModel tWallModel(SCENE_WIDTH - 2.0, WallModel::TOP);
	NNS::Wall tWall(tWallModel);
	tWall.setName("tWall");
	NNS::WallRenderer tWallRenderer(tWall);
	tWall.setPos(1.0, SCENE_HEIGHT - 1.0);
	scene.add(& tWallRenderer);
	newtonCollider.addFixed(& tWall);
	introspector.associate(& tWall, & tWallRenderer);

	WallModel lWallModel(SCENE_HEIGHT - 2.0, WallModel::LEFT);
	NNS::Wall lWall(lWallModel);
	lWall.setName("lWall");
	NNS::WallRenderer lWallRenderer(lWall);
	lWall.setPos(1.0, 1.0);
	scene.add(& lWallRenderer);
	newtonCollider.addFixed(& lWall);
	introspector.associate(& lWall, & lWallRenderer);

	WallModel rWallModel(SCENE_HEIGHT - 2.0, WallModel::RIGHT);
	NNS::Wall rWall(rWallModel);
	rWall.setName("rWall");
	NNS::WallRenderer rWallRenderer(rWall);
	rWall.setPos(SCENE_WIDTH - 1.0, 1.0);
	scene.add(& rWallRenderer);
	newtonCollider.addFixed(& rWall);
	introspector.associate(& rWall, & rWallRenderer);

	BoxModel boxModel(2.0, 1.0);

	NNS::MaterialPoly materialBox(boxModel.cvertices, 1.0, 22);
	NNS::MaterialPolyRenderer materialRenderer(materialBox);
	materialBox.setPos(13, 7.5);
//	materialBox.setV(gpx::math::Vector<2>(55.0, -10.0));
	materialBox.mountForce(new gpx::phy2d::Force(0.0, -90.0), gpx::math::Point<2>(0.0, 0.0));
//	scene.add(& materialRenderer);
//	newtonCollider.addMovable(& materialBox);
//	blackBox.add(& materialBox);
	introspector.associate(& materialBox, & materialRenderer);

	NNS::RigidPoly rigidBox(boxModel.cvertices, 1.0);
	rigidBox.setName("rigidBox");
	NNS::RigidPolyRenderer rigidRenderer(rigidBox);
	rigidBox.setPos(10.0, 2.0);
//	rigidBox.setAngle(gpx::math::PI / 4.0);
//	rigidBox.setAngle(gpx::math::PI);
//	rigidBox.setAngle(-0.38);
//	rigidBox.setV(gpx::math::Vector<2>(3.0, 0.0));
	rigidBox.mountForce(new gpx::phy2d::Force(0.0, -100.5), gpx::math::Point<2>(0.0, 0.0));
	scene.add(& rigidRenderer);
	newtonCollider.addMovable(& rigidBox);
	blackBox.add(& rigidBox);
	introspector.associate(& rigidBox, & rigidRenderer);

	BoxModel boxModel2(2.125, 1.0);
	NNS::RigidPoly rigidBox2(boxModel2.cvertices, 1.0);
	rigidBox2.setName("rigidBox2");
	NNS::RigidPolyRenderer rigidRenderer2(rigidBox2);
	rigidBox2.setPos(6.0, 15.0);
//	rigidBox2.setAngle(-0.3);
//	rigidBox2.setV(gpx::math::Vector<2>(9.0, 0.0));
//	rigidBox2.setV(gpx::math::Vector<2>(0.0, -10.0));
	rigidBox2.mountForce(new gpx::phy2d::Force(0.0, -100.5), gpx::math::Point<2>(0.0, 0.0));
//	scene.add(& rigidRenderer2);
//	newtonCollider.addMovable(& rigidBox2);
//	blackBox.add(& rigidBox2);
	introspector.associate(& rigidBox2, & rigidRenderer2);

	BoxModel boxModel3(2.125, 1.0);
	NNS::RigidPoly rigidBox3(boxModel3.cvertices, 1.0);
	rigidBox3.setName("rigidBox3");
	NNS::RigidPolyRenderer rigidRenderer3(rigidBox3);
	rigidBox3.setPos(6.0, 10.0);
	rigidBox3.mountForce(new gpx::phy2d::Force(0.0, -100.5), gpx::math::Point<2>(0.0, 0.0));
//	scene.add(& rigidRenderer3);
//	newtonCollider.addMovable(& rigidBox3);
//	blackBox.add(& rigidBox3);
	introspector.associate(& rigidBox3, & rigidRenderer3);

	BallModel ballModel(1.0);
	NNS::RigidPoly rigidBall(ballModel.cvertices, 1.0);
	rigidBall.setName("rigidBall");
	NNS::RigidPolyRenderer ballRenderer(rigidBall);
	rigidBall.setPos(16.0, 10.0);
	rigidBall.mountForce(new gpx::phy2d::Force(0.0, -10.5), gpx::math::Point<2>(0.0, 0.0));
//	scene.add(& ballRenderer);
//	newtonCollider.addMovable(& rigidBall);
//	blackBox.add(& rigidBall);
	introspector.associate(& rigidBall, & ballRenderer);

	gpx::phy2d::Force * ff = new gpx::phy2d::Force(0.0, -100.5);
	std::vector<NNS::RigidPoly *> rigidBoxArr;
	std::vector<NNS::RigidPolyRenderer *> rigidRendererArr;
	for (int x = 0; x < 1; x++)
		for (int y = 0; y < 2; y++) {
			NNS::RigidPoly * rb = new NNS::RigidPoly(boxModel.cvertices, 1.0);
			NNS::RigidPolyRenderer * rr = new NNS::RigidPolyRenderer(*rb);
			rb->setPos(10.0 + static_cast<gpx::real_t>(x) * 3.0, 4.0 + static_cast<gpx::real_t>(y) * 2.0);
			rb->mountForce(ff, gpx::math::Point<2>(0.0, 0.0));
			scene.add(rr);
			newtonCollider.addMovable(rb);
			blackBox.add(rb);
			rigidBoxArr.push_back(rb);
			rigidRendererArr.push_back(rr);
			introspector.associate(rb, rr);
		}

	gpx::phy::NewtonPlasticityTable::Instance().get(0).e = 2.0;
	gpx::phy::NewtonPlasticityTable::Instance().get(0).s = 0.0;
	gpx::phy::NewtonPlasticityTable::Instance().get(22).e = 2.0;
	gpx::phy::NewtonPlasticityTable::Instance().get(22).s = 0.0;

//	blackBox.snapshot();
	phyClock.Reset();
	while (win.IsOpened()) {
		//clear display
		glClear(GL_COLOR_BUFFER_BIT);

	    view.update();
		win.display();

		//handle events
		bool update = false;
		while (win.fetchEvent(event)) {
			if (event.Type == sf::Event::Closed)
				win.Close();
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
				win.Close();
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::A))
				rigidBox.applyImpulse(gpx::math::Vector<2>(-10.0, 0.0), gpx::math::Point<2>(0.0, 0.0));
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::D))
				rigidBox.applyImpulse(gpx::math::Vector<2>(10.0, 0.0), gpx::math::Point<2>(0.0, 0.0));
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::S))
				rigidBox.applyImpulse(gpx::math::Vector<2>(0.0, -10.0), gpx::math::Point<2>(0.0, 0.0));
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::W))
				rigidBox.applyImpulse(gpx::math::Vector<2>(0.0, 10.0), gpx::math::Point<2>(0.0, 0.0));
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Q))
				ff->rotate(0.1);
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::E))
				ff->rotate(-0.1);
			if (event.Type == sf::Event::KeyPressed)
				update = true;
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::B)) {
				rigidBox.swapBuffers();
				rigidBall.swapBuffers();
				for (std::vector<NNS::RigidPoly *>::iterator rb = rigidBoxArr.begin(); rb != rigidBoxArr.end(); ++rb)
					(*rb)->swapBuffers();
				update = false;
			}
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::I))
				introspector.toggleSkipBreakpoints();
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Left)) {
				blackBox.rewind();
				update = false;
			}
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Right)) {
				blackBox.forward();
				update = false;
			}
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Down)) {
				blackBox.dump(DUMP_FILE);
				update = false;
			}
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Up)) {
				blackBox.load(DUMP_FILE);
				update = false;
			}
		}
		if (introspector.error()) {
			GPX_WARN("introspector error: " << introspector.errorMsg());
			GPX_DEBUG("press R to resume");
			while ((event.Type != sf::Event::KeyPressed) || (event.Key.Code != sf::Key::R))
				win.fetchEvent(event);
			introspector.resetError();
		}

//przy subsequent collision limit ustawione na 20
//w pasywnym zbiera się 40 impulsów bo passiveMov nie ma czyszczonego impulsePoints
//aktywny robi 20 updatatów, a egzekutor dodaje za kazdym razem do passiveMov impuls.
		//stepping mode
//		while (!win.fetchEvent(event) || (event.Type != sf::Event::KeyPressed))
//			Sleep(1);
//		do {
//			if (event.Type == sf::Event::Closed)
//				win.Close();
//			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
//				win.Close();
//		} while (win.fetchEvent(event));

		//get time elapsed
//		phyTime = phyClock.GetElapsedTime();
		//fixed time
//		phyTime = 0.05;		//20Hz
//		phyTime = 0.025;	//40Hz
		phyTime = 0.0025;	//400Hz
//		phyTime = 0.00125;	//800Hz
//		phyTime = 0.000625;	//1600Hz

		phyClock.Reset();

		if (update)
			newtonCollider.update(phyTime);
		if (update)
			blackBox.snapshot();
	}

	return EXIT_SUCCESS;
}
