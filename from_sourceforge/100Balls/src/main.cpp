/**
 * 100 balls demo.
 *
 * @author doc
 */


//#define SFML_DYNAMIC
//#define GPX_DYNAMIC


#include <iostream>
#include <cstring>

#include <gpx/gra/RenderWindow.hpp>
//#include <SFML/System.hpp>

#include <guichan.hpp>
#include <guichan/sfml.hpp>


#include <gpx/log/Log.hpp>
#include <gpx/math/functions.hpp>

#include <gpx/phy2d/DragnDropCollider.hpp>
#include <gpx/phy2d/NewtonCollider.hpp>
#include <gpx/phy2d/Force.hpp>
#include <gpx/phy2d/joints.hpp>
#include <gpx/phy2d/Board.hpp>
#include <gpx/phy2d/Hook.hpp>
//#include <phy/DoubleBufferSwapper.h>
#include <gpx/phy/PhyLog.hpp>
#include <gpx/phy2d/RigidBodyRenderer.hpp>
#include <gpx/phy2d/BoardRenderer.hpp>
#include <gpx/phy2d/joints/JointRenderer.hpp>
#include <gpx/phy2d/forces/HookeForce.hpp>
#include <gpx/gra2d/View.hpp>
#include <gpx/gra/GraLog.hpp>

#include <gcn/gra/ContextMenu.hpp>
#include <gcn/phy2d/BoardGUI.hpp>
#include <gcn/phy2d/ContextGUICollider.hpp>
#include <gcn/phy2d/NewtonColliderGUI.hpp>


#include "graphics/BallRenderer.h"
#include "models/BallModel.h"
#include "physics/Ball.h"

#include "graphics/WallRenderer.h"
#include "models/WallModel.h"
#include "physics/Wall.h"

#include "graphics/BoxRenderer.h"
#include "models/BoxModel.h"
#include "physics/Box.h"

#include "graphics/SoftBoxRenderer.h"
#include "models/BoxModel.h"
#include "physics/SoftBox.h"

#include "graphics/CPolygonRenderer.h"
#include "models/CPolygonModel.h"
#include "physics/CPolygon.h"

#include "graphics/SoftPolygonRenderer.h"
#include "physics/SoftPolygon.h"
#include "control/SoftPolygonControl.h"

#include "physics/GravityManager.h"


using namespace std;
using namespace gpx;


int main(int argc, char* argv[])
{
	//default window width and height
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const double SCENE_HEIGHT = 20.0; //let scene be 20 meters tall
	const double SCENE_WIDTH = (static_cast<gpx::real_t>(WINDOW_WIDTH) / static_cast<gpx::real_t>(WINDOW_HEIGHT)) * SCENE_HEIGHT;

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

//	cout << reinterpret_cast<std::size_t>(glMultiDrawElements) << std::endl;
//	void * ptr = & glMultiDrawElements;
//	cout << *(static_cast<std::size_t *>(ptr)) << std::endl;
//	if (*ptr == NULL)
//		cout << "glMultiDrawElements not available" << endl;
//	else
//		cout << "glMultiDrawElements available" << endl;

	//create OpenGL context
	gpx::gra::RenderWindow win(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Fast Ball", sf::Style::Close | sf::Style::Resize, settings);
	win.UseVerticalSync(true);
//	app.logGlInfo(2);

//	cout << reinterpret_cast<std::size_t>(glMultiDrawElements) << std::endl;
//	cout << *(static_cast<std::size_t *>(ptr)) << std::endl;
//	if (ptr == NULL)
//		cout << "glMultiDrawElements not available" << endl;
//	else
//		cout << "glMultiDrawElements available" << endl;



	const sf::Input & input = win.GetInput();
	gcn::Gui * gui = 0;
	gcn::SFMLGraphics * graphics = 0;
	gcn::SFMLInput * gcnInput = 0;
	gcn::SFMLImageLoader * imageLoader = 0;
	gui = new gcn::Gui();
	graphics = new gcn::SFMLGraphics(win);
	imageLoader = new gcn::SFMLImageLoader();
	gcn::Image::setImageLoader(imageLoader);
	gcnInput = new gcn::SFMLInput();
	gui->setGraphics(graphics);
	gui->setInput(gcnInput);
	gcn::ImageFont * gcnFont = new gcn::ImageFont("fonts/fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	gcn::Widget::setGlobalFont(gcnFont);
	gcn::Container* top;
    top = new gcn::Container();
    top->setOpaque(false);
    top->setDimension(gcn::Rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    gui->setTop(top);

    gra2d::Scene scene(SCENE_WIDTH, SCENE_HEIGHT);
    gra2d::View view(win, scene);
//	app.PreserveOpenGLStates(true); //temp (required for fps draw)
//	app.SetFramerateLimit(5);

	BallModel ballModel(1.0);
//	Ball ball(& ballModel, std::numeric_limits<gpx::real_t>::infinity()); //mass = inf
	Ball ball(& ballModel, 1.0);
	BallRenderer ballRenderer(& ball);
	ball.setPos(15.0, 13.0);
	ball.mountForce(new gpx::math::Vector<2>(0.0, -5.0));
//	ball.setV(gpx::math::Vector<2>(5.0, 0.0));

	BallModel nBallModel(1.0);
	Ball nBall(& nBallModel, nBallModel.r);
	BallRenderer nBallRenderer(& nBall);
	nBall.setPos(15.0, 10.0);

	BallModel mBallModel(1.0);
	Ball mBall(& mBallModel, mBallModel.r);
	BallRenderer mBallRenderer(& mBall);
	mBall.setPos(15.0, 8.0);

	BallModel oBallModel(1.0);
	Ball oBall(& oBallModel, oBallModel.r);
	BallRenderer oBallRenderer(& oBall);
	oBall.setPos(15.0, 6.0);

	WallModel bWallModel(SCENE_WIDTH - 2.0, WallModel::BOTTOM);
	Wall bWall(& bWallModel);
	WallRenderer bWallRenderer(& bWall);
	bWall.setPos(1.0, 1.0);

	WallModel tWallModel(SCENE_WIDTH - 2.0, WallModel::TOP);
	Wall tWall(& tWallModel);
	WallRenderer tWallRenderer(& tWall);
	tWall.setPos(1.0, SCENE_HEIGHT - 1.0);

	WallModel lWallModel(SCENE_HEIGHT - 2.0, WallModel::LEFT);
	Wall lWall(& lWallModel);
	WallRenderer lWallRenderer(& lWall);
	lWall.setPos(1.0, 1.0);

	WallModel rWallModel(SCENE_HEIGHT - 2.0, WallModel::RIGHT);
	Wall rWall(& rWallModel);
	WallRenderer rWallRenderer(& rWall);
	rWall.setPos(SCENE_WIDTH - 1.0, 1.0);

	BoxModel boxModel(2.0, 1.0);
	Box box(& boxModel, 1.0);
	BoxRenderer boxRenderer(& box);
	phy2d::RigidBodyRenderer boxRbRenderer(& box);
//	box.setPos(4.5, 1.0 + std::sqrt(10.0) * 0.25);
	box.setPos(8.5, 5.1);
//	box.setAngularV(-0.1);
	box.setV(gpx::math::Vector<2>(5.0, 0.0));
//	box.setAngle(gpx::math::PI/6);
//	box.mountForce(new phy::Force2(0.0, .1, false), math::Vector<2>(1.0, 0.0));
	box.mountForce(new phy2d::Force(0.0, -1.5), math::Vector<2>(0.0, 0.0));
//	box.mountForce(new phy::Force2(0.0, -.1), math::Vector<2>(2.0, 0.0));
//	box.mountForce(new phy::Force2(0.0, -.1), math::Vector<2>(2.0, 0.0));

	BoxModel sboxModel(1.5, 1.0);
	SoftBox sbox(& sboxModel, 1.0);
	SoftBoxRenderer sboxRenderer(& sbox);
	phy2d::RigidBodyRenderer sboxRbRenderer(& sbox);
	sbox.setPos(10.5, 4.7);
//	sbox.setAngle(gpx::math::PI / 4.0 + gpx::math::PI / 3.0 + gpx::math::PI);
	sbox.setAngle(gpx::math::PI / 2.0);
//	sbox.setV(gpx::math::Vector<2>(0.0, -1.0));
//	sbox.setAngularV(-0.02);
//	sbox.mountForce(new phy2d::Force(0.0, -1.5), math::Vector<2>(0.0, 0.0));

//	CPolygonModel cpolyModel(ballModel.cvertices);
	CPolygon cpoly(ballModel.cvertices, 10.0);
	CPolygonRenderer cpolyRenderer(& cpoly);
	cpoly.setPos(12.5, 5.0);
//	cpoly.setV(gpx::math::Vector<2>(-0.1, 0.0));
//	cpoly.setAngle(gpx::math::PI);
	cpoly.mountForce(new phy2d::Force(0.0, -5.0), math::Vector<2>(0.0, 0.0));

	SoftPolygon spoly(ballModel.cvertices, 0.25, 0.005);
	SoftPolygonRenderer spolyRenderer(& spoly);
	spoly.setPos(12.5, 8.0);
	spoly.mountForce(new phy2d::Force(0.0, -0.01), math::Vector<2>(0.0, 0.0));
//	spoly.setV(gpx::math::Vector<2>(-0.1, 0.0));
//	spoly.setAngle(gpx::math::PI / 2.0);
	SoftPolygonControl spolyControl(win.GetInput(), & spoly);


	gpx::phy2d::Board board;
	phy2d::BoardRenderer boardRenderer(& board);
	math::Vector<2> & pin = board.addPin(math::Vector<2>(5.0, 5.0));
	phy2d::Hook boxHook(& boxModel.vertices[0], box.tMatrix());
	phy2d::forces::HookeForce<phy2d::op::Heaviside> hookeForce(pin, boxHook.tVertex(), 1.0);
//	box.mountForce(& hookeForce, math::Vector<2>(& boxModel.vertices[0]));
//	phy2d::joints::LinearJoint<> linJoint(boxHook.tVertex(), pin, 1.0);
//	phy2d::joints::JointRenderer linJointRenderer(& linJoint);
//	std::cout << "linJoint value(): " << linJoint.value() << std::endl;

	gcn::phy2d::ContextGUICollider contextCollider;
	gcn::phy2d::BoardGUI boardGUI(& boardRenderer);
	contextCollider.add(& boardGUI);

	scene.add(& oBallRenderer);
	scene.add(& mBallRenderer);
	scene.add(& nBallRenderer);
	scene.add(& ballRenderer);
	scene.add(& bWallRenderer);
	scene.add(& tWallRenderer);
	scene.add(& lWallRenderer);
	scene.add(& rWallRenderer);
	scene.add(& boxRenderer);
	scene.add(& boxRbRenderer);
//	scene.add(& linJointRenderer);
	scene.add(& sboxRenderer);
	scene.add(& sboxRbRenderer);
	scene.add(& cpolyRenderer);
	scene.add(& spolyRenderer);

//	scene.add(& softRenderer);

//	GravityManager gravityManager;
//	gravityManager.add(& ball);
//	gravityManager.add(& nBall);
//	gravityManager.add(& mBall);
//	gravityManager.add(& oBall);

	phy2d::DragnDropCollider dndCollider;
	dndCollider.add(& nBall);
	dndCollider.add(& mBall);
	dndCollider.add(& oBall);
	dndCollider.add(& ball);
	dndCollider.add(& box);
	dndCollider.add(& sbox);
	dndCollider.add(& cpoly);

	phy2d::NewtonCollider newtonCollider;
	newtonCollider.setSubsequentCollisionLimit(2);
	newtonCollider.addMovable(& ball);
//	newtonCollider.addMovable(& nBall);
//	newtonCollider.addMovable(& mBall);
//	newtonCollider.addMovable(& oBall);
	newtonCollider.addMovable(& box);
	newtonCollider.addMovable(& cpoly);
//	std::vector<SoftBoxVertex> & sboxParts = sbox.getParts();
//	for (std::vector<SoftBoxVertex>::iterator part = sboxParts.begin(); part != sboxParts.end(); ++part)
//		newtonCollider.addMovable(& (*part));
	std::vector<SoftPolygonVertex> & spolyParts = spoly.getParts();
	for (std::vector<SoftPolygonVertex>::iterator part = spolyParts.begin(); part != spolyParts.end(); ++part)
		newtonCollider.addMovable(& (*part));
	newtonCollider.addFixed(& bWall);
	newtonCollider.addFixed(& tWall);
	newtonCollider.addFixed(& lWall);
	newtonCollider.addFixed(& rWall);

	sf::Font font;
	//lucida console
	if (!font.LoadFromFile("fonts/lucon.ttf")) {
		cout << "Could not load font" << endl;
		exit(0);
	}
	char fpsChar[80] = "fps info N/A";
	double fps, fpsAvg = 0.0;
	double fpsMin = std::numeric_limits<double>::infinity();
	double fpsMinTime = 0.0;
	double fpsMax = 0.0;
	double fpsMaxTime = 0.0;
	sf::String fpsString(fpsChar, font, 12.0);
	fpsString.SetPosition(10.0, 10.0);
	fpsString.SetColor(sf::Color(0, 0, 0));

	phyClock.Reset();
	while (win.IsOpened()) {
		//clear display
		glClear(GL_COLOR_BUFFER_BIT);
//	    glDisable(GL_TEXTURE_2D | GL_DEPTH_TEST);

		//prepare display
//		glTranslated(SCENE_WIDTH / 2.0, SCENE_HEIGHT / 2.0, 0.0);
//		glTranslated(-SCENE_WIDTH / 2.0, -SCENE_HEIGHT / 2.0, 0.0);
//	    glLoadIdentity();
//		glRotated(20.01, 0.0, 0.0, 1.0);
	    view.update();

	    glPushMatrix();	//push current MODELVIEW matrix
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();	//push PROJECTION matrix
			glPushAttrib(GL_TRANSFORM_BIT | GL_ENABLE_BIT);
				gui->draw();
				win.Draw(fpsString);
			glPopAttrib();
		glPopMatrix(); //pop PROJECTION matrix (GL_TRANSFORM_BIT within glPush/PopAttrib() restores GL_MATRIX_MODE)
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix(); //pop MODELVIEW matrix
		//display results
	    win.display();


		//handle control
		spolyControl.update();
		if (input.IsKeyDown(sf::Key::R))
			cpoly.mountImpulse(gpx::math::Vector<2>(0.0, 0.5));
		if (input.IsKeyDown(sf::Key::E))
			cpoly.mountImpulse(gpx::math::Vector<2>(-.5, 0.0));
		if (input.IsKeyDown(sf::Key::T))
			cpoly.mountImpulse(gpx::math::Vector<2>(0.5, 0.0));
		if (input.IsKeyDown(sf::Key::Y))
			ball.mountImpulse(gpx::math::Vector<2>(0.0, 0.5));

		//get time elapsed
		phyTime = phyClock.GetElapsedTime();
		phyClock.Reset();
	    //handle real time input (temp)
		if (input.IsMouseButtonDown(sf::Mouse::Left)) {
			dndCollider.setPos(view.mapToScene(input.GetMouseX(), win.GetHeight() - input.GetMouseY()));
			dndCollider.update(0.03);
		}
		//handle collisions and calculate physics
		boxHook.update();
		hookeForce.update();
//		sbox.update(0.003);
		spoly.update(0.03);
		newtonCollider.update(0.03);
//		sbox.swapBuffers();
		spoly.swapBuffers();
		//after simulation is performed, results should be displayed fast

		double frameTime = win.GetFrameTime();
		fps = 1.0 / frameTime;
		if (fpsMinTime > 30.0) {
			fpsMin = std::numeric_limits<double>::infinity();
			fpsMinTime = 0.0;
		}
		fps < fpsMin ? fpsMin = fps : fpsMinTime += frameTime;
		if (fpsMaxTime > 30.0)
			fpsMax = fpsMaxTime = 0.0;
		fps > fpsMax ? fpsMax = fps : fpsMaxTime += frameTime;

		fpsAvg = (fpsAvg * 0.995) + (fps * 0.005);
		snprintf(fpsChar, sizeof(fpsChar), "fps: %6.1f    avg: %6.1f    min: %6.1f    max: %6.1f", fps, fpsAvg, fpsMin, fpsMax);
		fpsString.SetText(fpsChar);
//		sf::Sleep(0.1);
//		sf::Sleep(sf::Randomizer::Random(0.0f, 0.1f));

		//handle events
		while (win.fetchEvent(event)) {
			if (event.Type == sf::Event::Closed)
				win.Close();
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
				win.Close();
//			if (event.Type == sf::Event::MouseWheelMoved)
//				view.setZoom(view.getZoom() + ((double)event.MouseWheel.Delta * 1.0));
			if ((event.Type == sf::Event::MouseButtonPressed) && (event.MouseButton.Button == sf::Mouse::Left))
				dndCollider.drag(view.mapToScene(event.MouseButton.X, win.GetHeight() - event.MouseButton.Y));
			if ((event.Type == sf::Event::MouseButtonReleased) && (event.MouseButton.Button == sf::Mouse::Left))
				dndCollider.drop();
//			if (dndCollider.draggedNum() && (event.Type == sf::Event::MouseMoved)) {
//				dndCollider.setPos(event.MouseMove.X / glView.getZoom(), (app.GetHeight() - event.MouseMove.Y) / glView.getZoom());
//				dndCollider.update(0.003);
//			}
			gcnInput->pushEvent(event, input);
			gui->logic();
		}
	}

	delete gui;
	delete imageLoader;
	delete gcnInput;
	delete graphics;

	return EXIT_SUCCESS;
}
