/*
 * MyContactListenerA.h
 *
 *  Created on: 2012-9-28
 *      Author: arch
 */

#ifndef MYCONTACTLISTENER_H_
#define MYCONTACTLISTENER_H_

#include <Box2D/Box2D.h>
#include "MyContact.h"

class MyContactListener: public b2ContactListener {

public:
	virtual ~MyContactListener() {
		contact_list.clear();
	}

	virtual void BeginContact(b2Contact* contact) {
		if (contact) {
			MyContact mc;
			mc.fixtureA = contact->GetFixtureA();
			mc.fixtureB = contact->GetFixtureB();

			contact_list.push_back(mc);
		}
		B2_NOT_USED(contact);
	}
//
	virtual void EndContact(b2Contact* contact) {
		contact_list.clear();
		B2_NOT_USED(contact);
	}

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse) {
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}


	std::list<MyContact> contact_list;
};

#endif /* MYCONTACTLISTENERA_H_ */
