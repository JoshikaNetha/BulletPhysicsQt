QT += quick core gui quick3d

SOURCES += \
        Bullet.cpp \
        PhysicsEngine.cpp \
        main.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =


INCLUDEPATH += /home/joshika/workSpace/QtProject/Repo/bullet3/src
INCLUDEPATH += /home/joshika/workSpace/QtProject/Repo/bullet3/examples
INCLUDEPATH += /home/joshika/workSpace/QtProject/Repo/bullet3/examples/CommonInterfaces

INCLUDEPATH += /usr/local/lib
INCLUDEPATH += /usr/local/include/bullet


LIBS += -L/usr/local/lib -lBulletCollision -lBulletDynamics -lLinearMath


# export LD_LIBRARY_PATH=/home/joshika/workSpace/QtProject/Repo/bullet3/build/src:$LD_LIBRARY_PATH

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Bullet.h \
    PhysicsEngine.h
