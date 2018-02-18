#!/bin/sh
#

#
# Set up to do reads with possible shell escape and default assignment
#
getvalue() {
    ans='!'

    echo 
    echo -n "$1 [$2] "

        while expr "X$ans" : "X!" >/dev/null; do
                read ans
                case "$ans" in
                        !)
                                sh
                                echo " "
                                echo $n "$rp $c"
                                ;;
                        !*)
                                set `expr "X$ans" : "X!\(.*\)$"`
                                sh -c "$*"
                                echo " "
                                echo $n "$rp $c"
                                ;;
                        esac
        done

        if [ -z "$ans" ]; then
        ans="$dflt"
    fi
}

INSTPREFIX=/opt/cisco/hostscan
INIT_SRC="ciscod_init"
INIT="ciscod"
BINDIR=${INSTPREFIX}/bin
LIBDIR=${INSTPREFIX}/lib
LOGDIR=${INSTPREFIX}/log
SYSVSTART="S85"
SYSVSTARTNUM="85"
SYSVSTOP="K25"
SYSVSTOPNUM="25"
SYSVLEVELS="2 3 4 5"

LOGFNAME=`/bin/date "+posture-4.3.05017-install-%H%M%S%d%m%Y.log"` ||
  LOGFNAME=`/usr/bin/date "+posture-4.3.05017-install-%H%M%S%d%m%Y.log"` ||
  LOGFNAME=`date "+posture-4.3.05017-install-%H%M%S%d%m%Y.log"` ||
  LOGFNAME=posture-4.3.05017-install.log

DIR=`dirname $0 2> /dev/null` || 
  DIR=`/usr/bin/dirname $0 2> /dev/null` || 
  DIR=`/bin/dirname $0 2> /dev/null` || 
  DIR=.

ID=`id -u  2> /dev/null` || ID=`/usr/bin/id -u  2> /dev/null` ||
  ID=`/usr/bin/id -u  2> /dev/null`

if [ -x "/usr/bin/install" ]; then
    INSTALL="/usr/bin/install"
elif [ -x "/bin/install" ]; then
    INSTALL="/bin/install"
elif [ -x "/usr/local/bin/install" ]; then
    INSTALL="/usr/local/bin/install"
else
    INSTALL="install"
fi
${INSTALL} --help 2> /dev/null > /dev/null
if [ $? != 0 ]; then
    INSTALL=""
fi

# Find out  if we are using insserv
if [ -x "/sbin/insserv" ]; then
    INSSERV="/sbin/insserv"
elif [ -x "/usr/sbin/insserv" ]; then
    INSSERV="/usr/sbin/insserv"
fi
${INSSERV} > /dev/null 2> /dev/null
if [ $? != 0 ]; then
    INSSERV=""
fi

# Find out if we are using chkconfig
if [ -x "/sbin/chkconfig" ]; then
  CHKCONFIG="/sbin/chkconfig"
elif [ -x "/usr/sbin/chkconfig" ]; then
  CHKCONFIG="/usr/sbin/chkconfig"
else
  CHKCONFIG="chkconfig"
fi
if [ `${CHKCONFIG} --list 2> /dev/null | wc -l` -lt 1 ]; then
  CHKCONFIG=""
  echo "(chkconfig not found or not used)" >> /tmp/${LOGFNAME}
fi

# Find out if we are using update-rc.d
if [ -x "/usr/sbin/update-rc.d" ]; then
    UPDATERCD="/usr/sbin/update-rc.d"
elif [ -x "/sbin/update-rc.d" ]; then
    UPDATERCD="/sbin/update-rc.d"
else
    UPDATERCD="update-rc.d"
fi
${UPDATERCD} > /dev/null 2> /dev/null
if [ $? = 127 ]; then
    UPDATERCD=""
fi

ARG_NO_LICENSE=0
ARG_NO_PROMPT=0

for i in $*
do
    if [ "x${i}" = "x--no-license" ]; then
	ARG_NO_LICENSE=1
    fi

    if [ "x${i}" = "x--no-prompt" ]; then
	ARG_NO_PROMPT=1
    fi
done

echo "Installing Cisco AnyConnect Posture Module..."
echo "Installing Cisco AnyConnect Posture Module v4.3.05017..." > /tmp/${LOGFNAME}
echo `whoami` "invoked $0 from " `pwd` " at " `date` >> /tmp/${LOGFNAME}
echo ""

# Make sure we are root
if [ "x${ID}" != "x0" ]; then
  echo "Sorry, you need super user privileges to run this script."
  exit 1
fi


if [ "x${ARG_NO_LICENSE}" = "x1" ]; then

    echo "Skipping license text ..."

else

    if [ -f "${DIR}/license.txt" ]; then
	more ${DIR}/license.txt
    else
	echo "License file not found. Aborting installation."
	exit 1
    fi

    getvalue "Do you accept the Client Software License Agreement of Cisco Systems?" "n"
    response=$ans

    case "$response" in
	y* | Y*)
    # keep going 
	    ;;
	*)
	    exit 0
	    ;;
    esac
    
fi
    
echo -n "Creating directories... "

if [ "x${INSTALL}" = "x" ]; then
    echo "failed."
    echo "Unable to find install command."
    exit 1
fi

# Make sure destination directories exist
echo "Installing "${BINDIR} >> /tmp/${LOGFNAME}
${INSTALL} -d ${BINDIR} || ( echo "failed." && exit 1 )

echo "Installing "${LIBDIR} >> /tmp/${LOGFNAME}
${INSTALL} -d ${LIBDIR} || ( echo "failed." && exit 1 )

echo "Installing "${LOGDIR} >> /tmp/${LOGFNAME}
${INSTALL} -d ${LOGDIR} || ( echo "failed." && exit 1 )

echo "done."

echo -n "Copying files... "

# Copy files to their home
echo "Installing "${DIR}/cstub >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/cstub ${BINDIR} || 
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/ciscod >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/ciscod ${BINDIR} ||
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/cscan >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/cscan ${BINDIR} ||
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/libhostscan.so >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/libhostscan.so ${LIBDIR} ||
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/libcsd.so >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/libcsd.so ${LIBDIR} || 
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/libinspector.so >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/libinspector.so ${LIBDIR} || 
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/libacciscocrypto.so >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/libacciscocrypto.so ${LIBDIR} || 
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/libaccurl.so.4.3.0 >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/libaccurl.so.4.3.0 ${LIBDIR} || 
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/tables.dat >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 644 ${DIR}/tables.dat ${LIBDIR} || 
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/libacciscossl.so >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/libacciscossl.so ${LIBDIR} || 
    ( echo "failed." && exit 1 )

echo "Installing "${DIR}/posture_uninstall.sh >> /tmp/${LOGFNAME}
${INSTALL} -o root -m 755 ${DIR}/posture_uninstall.sh ${BINDIR} || 
    ( echo "failed." && exit 1 )
ln -f -s ${BINDIR}/posture_uninstall.sh ${BINDIR}/csd_uninstall.sh
chmod 755 ${BINDIR}/csd_uninstall.sh
echo "done."

echo -n "Determining system initialization script location... "

# Locate the init script directory
if [ -d "/etc/init.d" ]; then
  INITD="/etc/init.d"
elif [ -d "/etc/rc.d/init.d" ]; then
  INITD="/etc/rc.d/init.d"
else
  INITD="/etc/rc.d"
fi

# BSD-style init scripts on some distributions will emulate SysV-style.
if [ "x${CHKCONFIG}" = "x" ] && 
    [ "x${INSSERV}" = "x" ] && 
    [ "x${UPDATERCD}" = "x" ]; then
  if [ -d "/etc/rc.d" -o -d "/etc/rc0.d" ]; then
    BSDINIT=1
    if [ -d "/etc/rc.d" ]; then
      RCD="/etc/rc.d"
    else
      RCD="/etc"
    fi
  fi
fi

echo "done."

# systemctl bin location
if [ -x "/bin/systemctl" ]; then
  SYSTEMCTL="/bin/systemctl"
fi

# Install the new init script alongside the old, and use the 
# new script to shutdown.  Then remove the parallel script and
# and install as normal.

echo -n "Stopping the security agent... "
${INSTALL} -o root -m 755 -T ${DIR}/${INIT_SRC} ${INITD}/${INIT_SRC}
if ${INITD}/${INIT_SRC} status > /dev/null 2>&1 ; then
	${INITD}/${INIT_SRC} stop 2> /dev/null
fi
/bin/rm -f ${INITD}/${INIT_SRC}
echo "done."


echo -n "Creating system initialization script... "
if [ "x${INITD}" != "x" ]; then

  cmd="${INSTALL} -o root -m 755 -T ${DIR}/${INIT_SRC} ${INITD}/${INIT}"
  echo "Installing "${DIR}/${INIT_SRC} >> /tmp/${LOGFNAME}
  echo ${cmd} >> /tmp/${LOGFNAME}
  ${cmd} || ( echo "failed." && exit 1 )

  if [ "x${INSSERV}" != "x" ]; then
    echo -n "(using insserv)... "
    echo ${INSSERV} ${INIT} >> /tmp/${LOGFNAME}
    ${INSSERV} ${INIT} >> /tmp/${LOGFNAME} 
  elif [ "x${CHKCONFIG}" != "x" ]; then
    echo -n "(using chkconfig)... "
    echo ${CHKCONFIG} --add ${INIT} >> /tmp/${LOGFNAME}
    ${CHKCONFIG} --add ${INIT} >> /tmp/${LOGFNAME}
  elif [ "x${UPDATERCD}" != "x" ]; then
    echo -n "(using update-rc.d)... "
    echo ${UPDATERCD} ${INIT} defaults ${SYSVSTARTNUM} ${SYSVSTOPNUM} >> /tmp/${LOGFNAME}
    ${UPDATERCD} ${INIT} defaults ${SYSVSTARTNUM} ${SYSVSTOPNUM} >> /tmp/${LOGFNAME}
  else
    if [ "x${BSDINIT}" != "x" ]; then
      echo -n "(using brute force)... "
      for LEVEL in ${SYSVLEVELS}; do
        DIR="rc${LEVEL}.d"
        if [ ! -d "${RCD}/${DIR}" ]; then
          mkdir ${RCD}/${DIR}
          chmod 755 ${RCD}/${DIR}
        fi
        ln -sf ${INITD}/${INIT} ${RCD}/${DIR}/${SYSVSTART}${INIT}
        ln -sf ${INITD}/${INIT} ${RCD}/${DIR}/${SYSVSTOP}${INIT}
      done
    fi
  fi
  echo "done."

  logger "Starting the cisco security service..."
  echo -n "Starting the cisco security service... "
  echo "Starting the cisco security service..." >> /tmp/${LOGFNAME}
  # Attempt to start up the agent
  if [ "x${SYSTEMCTL}" != "x" ]; then
    echo ${SYSTEMCTL} daemon-reload >> /tmp/${LOGFNAME}
    ${SYSTEMCTL} daemon-reload >> /tmp/${LOGFNAME} || ( echo "failed." && exit 1 )
    echo ${SYSTEMCTL} start ${INIT} >> /tmp/${LOGFNAME}
    ${SYSTEMCTL} start ${INIT} >> /tmp/${LOGFNAME} || ( echo "failed." && exit 1 )
  else
    echo ${INITD}/${INIT} start >> /tmp/${LOGFNAME}
    ${INITD}/${INIT} start >> /tmp/${LOGFNAME} || ( echo "failed." && exit 1 )
    echo "done."
  fi
fi

# update manifest
echo "Updating AC manifest."
MANIFESTDIR=/opt/cisco/anyconnect/
${INSTALL} -o root -m 755 ${DIR}/ACManifestPOS.xml ${MANIFESTDIR} 2> /dev/null
/opt/cisco/anyconnect/bin/manifesttool -i ${MANIFESTDIR} ${MANIFESTDIR}ACManifestPOS.xml 2> /dev/null

echo "Done!"
echo "Done!" >> /tmp/${LOGFNAME}

# move the logfile out of the tmp directory
mv /tmp/${LOGFNAME} ${LOGDIR}

exit 0
