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

echo_and_run cd "/home/fyin/sim_env/src/TEB/move_base_flex/mbf_abstract_nav"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/fyin/sim_env/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/fyin/sim_env/install/lib/python2.7/dist-packages:/home/fyin/sim_env/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/fyin/sim_env/build" \
    "/usr/bin/python2" \
    "/home/fyin/sim_env/src/TEB/move_base_flex/mbf_abstract_nav/setup.py" \
     \
    build --build-base "/home/fyin/sim_env/build/TEB/move_base_flex/mbf_abstract_nav" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/fyin/sim_env/install" --install-scripts="/home/fyin/sim_env/install/bin"
