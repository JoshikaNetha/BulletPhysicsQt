#include "Bullet.h"
#include <QDebug>
// #include "/home/joshika/workSpace/QtProject/Repo/bullet3/src/BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#define ARRAY_SIZE_Y 5
#define ARRAY_SIZE_X 5
#define ARRAY_SIZE_Z 5

#include "LinearMath/btVector3.h"
#include "LinearMath/btScalar.h"
#include "LinearMath/btAlignedObjectArray.h"

Bullet::Bullet() {
    qDebug()<<"bullet constructor";

}

void Bullet::initialize()
{
    btDiscreteDynamicsWorld* dynamicsWorld;
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -9.8, 0));



    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1.0);
    btCollisionShape* fallShape = new btSphereShape(1);

    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);

    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
    btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
    dynamicsWorld->addRigidBody(fallRigidBody);

    dynamicsWorld->stepSimulation(1 / 60.f, 10);

    btTransform trans;
    fallRigidBody->getMotionState()->getWorldTransform(trans);
    qDebug() << "Sphere height: " << trans.getOrigin().getY();

    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
    delete groundShape;
    delete fallShape;
}
