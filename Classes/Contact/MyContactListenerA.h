/*
 * MyContactListenerA.h
 *
 *  Created on: 2012-9-28
 *      Author: arch
 */

#ifndef MYCONTACTLISTENERA_H_
#define MYCONTACTLISTENERA_H_

#include <Box2D/Box2D.h>

class MyContactListenerA :public b2ContactListener{

public:

	virtual void BeginContact(b2Contact* contact);

	virtual void EndContact(b2Contact* contact);

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse);

	std::list<MyContact> contact_list;

//private:


};

#endif /* MYCONTACTLISTENERA_H_ */
