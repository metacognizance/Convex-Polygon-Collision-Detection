print '\x1b[31m' + "\n--------------------No-Motivation--------------------" + '\033[0m'

libs = Split("""
sfml-graphics
sfml-window
sfml-system
""")

sources = Split("""
src/actor/Actor.cpp
src/actor/ActorIdTracker.cpp
src/actor/ActorManager.cpp
src/actor/LifeActor.cpp
src/actor/NPCActor.cpp
src/actor/NPCSpawner.cpp
src/actor/NPCSpawnerManager.cpp
src/actor/PlayerActor.cpp
src/actor/FollowerNetwork.cpp
src/application/Camera.cpp
src/application/main.cpp
src/application/Application.cpp
src/application/Math.cpp
src/world/World.cpp
src/world/Quadtree.cpp
""")

environment = Environment(CC='gcc')
environment.Append(CPPPATH='src')
environment.Append(LIBS=libs)
environment.Append(CXXFLAGS='-std=c++11')
environment.Program(target='No-Motivation', source=sources)

