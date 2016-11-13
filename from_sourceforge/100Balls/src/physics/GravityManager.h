/**
 * @file /FastBall/src/physics/GravityManager.h
 * @brief .
 */

#ifndef FastBall_GRAVITYMANAGER_H_
#define FastBall_GRAVITYMANAGER_H_

#include <gpx/phy2d/MaterialBody.hpp>
#include <gpx/phy2d/ForceManager.hpp>


using namespace gpx::phy2d;

class GravityManager: public ForceManager<MaterialBody>
{
	protected:
		gpx::real_t m_g;

	protected:
		virtual void updateForce(MaterialBody * obj, Force * f);

		virtual void attachForce(MaterialBody * obj, Force * f);

		virtual void detachForce(MaterialBody * obj, Force * f);

	public:
		GravityManager(gpx::real_t g = - 9.81);

		virtual ~GravityManager();

		void setAcceleration(gpx::real_t g);

		gpx::real_t acceleration();
};

#endif /* FastBall_GRAVITYMANAGER_H_ */
