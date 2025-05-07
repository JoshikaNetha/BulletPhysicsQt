#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <QObject>
#include <QVector3D>
#include <QTimer>
#include <btBulletDynamicsCommon.h>

class PhysicsEngine : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsEngine(QObject *parent = nullptr);
    ~PhysicsEngine();

    Q_PROPERTY(QVector3D spherePosition READ spherePosition NOTIFY spherePositionChanged)
    QVector3D spherePosition() const;

public slots:
    void stepSimulation();

signals:
    void spherePositionChanged();

private:
    btDiscreteDynamicsWorld* dynamicsWorld;
    btRigidBody* sphereRigidBody;
    QTimer simulationTimer;
    QVector3D m_spherePosition;
};

#endif // PHYSICSENGINE_H
