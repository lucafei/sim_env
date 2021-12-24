#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/fyin/D01_WS/sim_env/src/navigation/base_local_planner"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/fyin/D01_WS/sim_env/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/fyin/D01_WS/sim_env/install/lib/python2.7/dist-packages:/home/fyin/D01_WS/sim_env/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/fyin/D01_WS/sim_env/build" \
    "/usr/bin/python2" \
    "/home/fyin/D01_WS/sim_env/src/navigation/base_local_planner/setup.py" \
     \
    build --build-base "/home/fyin/D01_WS/sim_env/build/navigation/base_local_planner" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/fyin/D01_WS/sim_env/install" --install-scripts="/home/fyin/D01_WS/sim_env/install/bin"
