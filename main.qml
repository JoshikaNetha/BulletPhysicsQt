import QtQuick
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers
import PhysicsEngine 1.0
ApplicationWindow {
             visible: true
             width: Screen.width
             height: Screen.height
             title: "Bullet Physics Sphere"
             color: "white"

             PhysicsEngine {
                          id: physicsEngine
                          onSpherePositionChanged: {
                                       sphereModel.position = physicsEngine.spherePosition
                          }
             }

             View3D {
                          anchors.fill: parent

                          PerspectiveCamera {
                                id: camera
                                fieldOfView: 60
                                position: Qt.vector3d(0, 200, 300)
                                eulerRotation.x: -20

                                Component.onCompleted: {
                                    physicsEngine.spherePositionChanged.connect(() => {
                                        camera.position = Qt.vector3d(
                                            physicsEngine.spherePosition.x,
                                            physicsEngine.spherePosition.y + 50, // Offset to keep the sphere in view
                                            physicsEngine.spherePosition.z + 150 // Offset for depth
                                        );
                                    });
                                }
                            }
                          DirectionalLight {
                                       eulerRotation.x: -30
                                       eulerRotation.y: -70
                          }



                          Model {
                                       id: groundModel
                                       source: "#Cube"
                                       scale: Qt.vector3d(20, 1, 20)
                                       position: Qt.vector3d(0, -1, 0)
                                       materials: DefaultMaterial {
                                                    diffuseColor: "gray"
                                       }
                          }
                          Model {
                                       id: sphereModel
                                       source: "#Sphere"
                                       scale: Qt.vector3d(0.5, 0.5, 0.5)
                                       position: Qt.vector3d(0, 100, 0) // Static position

                                       materials: DefaultMaterial {
                                                    diffuseColor: "red"
                                       }
                          }
             }
}

/*        Model {
            position: Qt.vector3d(0, -200, 0)
            source: "#Cylinder"
            scale: Qt.vector3d(2, 0.2, 1)
            materials: [ DefaultMaterial {
                    diffuseColor: "red"
                }
            ]
        }*/
