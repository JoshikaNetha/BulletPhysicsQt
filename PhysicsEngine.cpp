#include "PhysicsEngine.h"
#include <QDebug>
PhysicsEngine::PhysicsEngine(QObject* parent)
    : QObject(parent), dynamicsWorld(nullptr), sphereRigidBody(nullptr)
{
    // Initialize Bullet Physics
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -9.8, 0));

    // Create ground
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);

    // Create sphere
    btCollisionShape* sphereShape = new btSphereShape(1);
    btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 100, 10)));
    btScalar mass = 1;
    btVector3 sphereInertia(0, 0, 0);
    sphereShape->calculateLocalInertia(mass, sphereInertia);
    btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);
    sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
    dynamicsWorld->addRigidBody(sphereRigidBody);



    // Start simulation timer
    connect(&simulationTimer, &QTimer::timeout, this, &PhysicsEngine::stepSimulation);
    simulationTimer.start(16); // ~60 FPS
}

PhysicsEngine::~PhysicsEngine()
{
    delete dynamicsWorld;
}

QVector3D PhysicsEngine::spherePosition() const
{
    return m_spherePosition;
}

void PhysicsEngine::stepSimulation()
{
    dynamicsWorld->stepSimulation(1 / 60.f, 10);

    btTransform trans;
    sphereRigidBody->getMotionState()->getWorldTransform(trans);
    // qDebug() << "Initial Sphere Position: " << trans.getOrigin().getX() << trans.getOrigin().getY() << trans.getOrigin().getZ();

    m_spherePosition = QVector3D(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
    // qDebug()<<"Step Simulatio";
    emit spherePositionChanged();
}
