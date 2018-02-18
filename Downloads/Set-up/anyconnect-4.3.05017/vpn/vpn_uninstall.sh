#!/bin/sh

LEGACY_INSTPREFIX="/opt/cisco/vpn"
LEGACY_BINDIR="${LEGACY_INSTPREFIX}/bin"

INSTPREFIX="/opt/cisco/anyconnect"
ROOTCERTSTORE=/opt/.cisco/certificates/ca
ROOTCACERT="VeriSignClass3PublicPrimaryCertificationAuthority-G5.pem"
BINDIR="${INSTPREFIX}/bin"
LIBDIR="${INSTPREFIX}/lib"
PROFDIR="${INSTPREFIX}/profile"
SCRIPTDIR="${INSTPREFIX}/script"
HELPDIR="${INSTPREFIX}/help"
PLUGINDIR="${BINDIR}/plugins"
MENUDIR="/etc/xdg/menus/applications-merged/"
DIRECTORYDIR="/usr/share/desktop-directories/"
DESKTOPDIR="/usr/share/applications"
INIT="vpnagentd"
AGENT="vpnagentd"
SYSVSTART="S85"
SYSVSTOP="K25"
SYSVLEVELS="2 3 4 5"
ACMANIFESTDAT="${INSTPREFIX}/VPNManifest.dat"
VPNMANIFEST="ACManifestVPN.xml"

# List of files to remove
FILELIST="${BINDIR}/vpnagentd \
          ${BINDIR}/vpn_uninstall.sh \
          ${BINDIR}/anyconnect_uninstall.sh \
          ${LIBDIR}/libacciscossl.so \
          ${LIBDIR}/libacciscocrypto.so \
          ${LIBDIR}/libaccurl.so.4 \
          ${LIBDIR}/libaccurl.so.4.3.0 \
          ${LIBDIR}/libvpnagentutilities.so \
          ${LIBDIR}/libvpncommon.so \
          ${LIBDIR}/libvpncommoncrypt.so \
          ${LIBDIR}/libvpnapi.so \
          ${BINDIR}/vpnui \
          ${BINDIR}/vpn \
          ${BINDIR}/vpndownloader \
          ${BINDIR}/vpndownloader-cli \
          ${BINDIR}/acinstallhelper \
          ${LEGACY_BINDIR}/vpndownloader \
          ${LEGACY_BINDIR}/vpndownloader.sh \
          ${LEGACY_BINDIR}/manifesttool \
          ${LEGACY_BINDIR}/vpn_uninstall.sh \
          ${MENUDIR}/cisco-anyconnect.menu \
          ${DIRECTORYDIR}/cisco-anyconnect.directory \
          ${DESKTOPDIR}/cisco-anyconnect.desktop \
          ${INSTPREFIX}/pixmaps/* \
          ${INSTPREFIX}/${VPNMANIFEST} \
          ${INSTPREFIX}/update.txt \
          ${LEGACY_INSTPREFIX}/update.txt \
          ${INSTPREFIX}/OpenSource.html \
          ${PROFDIR}/AnyConnectProfile.xsd \
          ${INSTPREFIX}/AnyConnectLocalPolicy.xsd \
          ${PLUGINDIR}/libvpnipsec.so \
          ${PLUGINDIR}/libacfeedback.so \
          ${ROOTCERTSTORE}/${ROOTCACERT}"

echo "Uninstalling Cisco AnyConnect Secure Mobility Client..."
echo "Uninstalling Cisco AnyConnect Secure Mobility Client..." > /tmp/vpn-uninstall.log
echo `whoami` "invoked $0 from " `pwd` " at " `date` >> /tmp/vpn-uninstall.log

# Check for root privileges
if [ `id | sed -e 's/(.*//'` != "uid=0" ]; then
  echo "Sorry, you need super user privileges to run this script."
  echo "Sorry, you need super user privileges to run this script." >> /tmp/vpn-uninstall.log
  exit 1
fi

# update the VPNManifest.dat; if no entries remain in the .dat file then
# this tool will delete the file - DO NOT blindly delete VPNManifest.dat by
# adding it to the FILELIST above - allow this tool to delete the file if needed
if [ -f "${BINDIR}/manifesttool" ]; then
  echo "${BINDIR}/manifesttool -x ${INSTPREFIX} ${INSTPREFIX}/${VPNMANIFEST}" >> /tmp/vpn-uninstall.log
  ${BINDIR}/manifesttool -x ${INSTPREFIX} ${INSTPREFIX}/${VPNMANIFEST}
fi

# check the existence of the manifest file - if it does not exist, remove the manifesttool
if [ ! -f ${ACMANIFESTDAT} ] && [ -f ${BINDIR}/manifesttool ]; then
  echo "Removing ${BINDIR}/manifesttool" >> /tmp/vpn-uninstall.log
  rm -f ${BINDIR}/manifesttool
fi

# Remove only those files that we know we installed
for FILE in ${FILELIST}; do
  echo "rm -f ${FILE}" >> /tmp/vpn-uninstall.log
  rm -f ${FILE} >> /tmp/vpn-uninstall.log 2>&1
done

# Remove the plugins directory
echo "rm -rf ${PLUGINDIR}" >> /tmp/vpn-uninstall.log
rm -rf ${PLUGINDIR} >> /tmp/vpn-uninstall.log 2>&1

# Remove the bin directory if it is empty
echo "rmdir --ignore-fail-on-non-empty ${BINDIR}" >> /tmp/vpn-uninstall.log
rmdir --ignore-fail-on-non-empty ${BINDIR} >> /tmp/vpn-uninstall.log 2>&1

# Remove the lib directory if it is empty
echo "rmdir --ignore-fail-on-non-empty ${LIBDIR}" >> /tmp/vpn-uninstall.log
rmdir --ignore-fail-on-non-empty ${LIBDIR} >> /tmp/vpn-uninstall.log 2>&1

# Remove the script directory if it is empty
echo "rmdir --ignore-fail-on-non-empty ${SCRIPTDIR}" >> /tmp/vpn-uninstall.log
rmdir --ignore-fail-on-non-empty ${SCRIPTDIR} >> /tmp/vpn-uninstall.log 2>&1

# Remove the help directory if it is empty
echo "rmdir --ignore-fail-on-non-empty ${HELPDIR}" >> /tmp/vpn-uninstall.log
rmdir --ignore-fail-on-non-empty ${HELPDIR} >> /tmp/vpn-uninstall.log 2>&1

# Remove the profile directory if it is empty
echo "rmdir --ignore-fail-on-non-empty ${PROFDIR}" >> /tmp/vpn-uninstall.log
rmdir --ignore-fail-on-non-empty ${PROFDIR} >> /tmp/vpn-uninstall.log 2>&1

# Remove the legacy bin directory if it is empty
echo "rmdir --ignore-fail-on-non-empty ${LEGACY_BINDIR}" >> /tmp/vpn-uninstall.log
rmdir --ignore-fail-on-non-empty ${LEGACY_BINDIR} >> /tmp/vpn-uninstall.log 2>&1

# Remove the legacy directory if it is empty
echo "rmdir --ignore-fail-on-non-empty ${LEGACY_INSTPREFIX}" >> /tmp/vpn-uninstall.log
rmdir --ignore-fail-on-non-empty ${LEGACY_INSTPREFIX} >> /tmp/vpn-uninstall.log 2>&1

# Remove the cert store directory if it is empty
echo "rmdir --ignore-fail-on-non-empty ${ROOTCERTSTORE}" >> /tmp/vpn-uninstall.log
rmdir --ignore-fail-on-non-empty ${ROOTCERTSTORE} >> /tmp/vpn-uninstall.log 2>&1

# update the menu cache so that the AnyConnect short cut in the
# applications menu is removed. This is neccessary on some
# gnome desktops(Ubuntu 10.04)
if [ -x "/usr/share/gnome-menus/update-gnome-menus-cache" ]; then
    for CACHE_FILE in $(ls /usr/share/applications/desktop.*.cache); do
        echo "updating ${CACHE_FILE}" >> /tmp/vpn-uninstall.log
        /usr/share/gnome-menus/update-gnome-menus-cache /usr/share/applications/ > ${CACHE_FILE}
    done
fi

# We need to check for, and try to remove, our init script.
if [ `chkconfig --list 2> /dev/null | wc -l` -gt 0 ]; then
  chkconfig --del ${INIT} # We don't exit on error in case user manually
                          # removed from chkconfig
fi

if [ -e "/etc/init.d/${INIT}" ]; then
  INITD="/etc/init.d"
elif [ -e "/etc/rc.d/init.d/${INIT}" ]; then
  INITD="/etc/rc.d/init.d"
else
  INITD="/etc/rc.d"
fi

if [ -d "/etc/rc.d" ]; then
  RCD="/etc/rc.d"
else
  RCD="/etc"
fi

# Make sure our runlevel symlinks are removed, in case of BSD-style init
for LEVEL in ${SYSVLEVELS}; do
  DIR="rc${LEVEL}.d"
  if [ -d "${RCD}/${DIR}" ]; then
    echo "rm -f ${RCD}/${DIR}/${SYSVSTART}${INIT}" >> /tmp/vpn-uninstall.log
    rm -f ${RCD}/${DIR}/${SYSVSTART}${INIT}
    echo "rm -f ${RCD}/${DIR}/${SYSVSTOP}${INIT}" >> /tmp/vpn-uninstall.log
    rm -f ${RCD}/${DIR}/${SYSVSTOP}${INIT}
  fi
done

# Attempt to stop the service if it is running, and remove the init script.
if [ "x${INITD}" != "x" ]; then
  echo "Stopping the VPN agent..." >> /tmp/vpn-uninstall.log
  TESTINIT=`ls -l /proc/1/exe`
  if [ -z "${TESTINIT##*"systemd"*}" ]; then
    echo systemctl stop ${INIT} >> /tmp/vpn-uninstall.log
    systemctl stop ${INIT} >> /tmp/vpn-uninstall.log
  else
    echo "${INITD}/${INIT} stop" >> /tmp/vpn-uninstall.log
    ${INITD}/${INIT} stop >> /tmp/vpn-uninstall.log
  fi
  echo "rm ${INITD}/${INIT}" >> /tmp/vpn-uninstall.log
  logger "Stopping the VPN agent..."

  max_seconds_to_wait=10
  ntests=$max_seconds_to_wait
  # Wait up to max_seconds_to_wait seconds for the agent to finish.
  while [ -n "`ps -A -o command | grep \"/opt/cisco/anyconnect/bin/${AGENT}\" | egrep -v 'grep'`" ]
    do
        ntests=`expr  $ntests - 1`
        if [ $ntests -eq 0 ]; then
          logger "Timeout waiting for agent to stop."
          echo "Timeout waiting for agent to stop." >> /tmp/vpn-uninstall.log
          break
        fi
        sleep 1
    done
  
  rm ${INITD}/${INIT} || echo "Warning: unable to remove init script"
fi

# ensure that the agent, gui and cli are not running
OURPROCS=`ps -A -o pid,command | grep '/opt/cisco/anyconnect/bin' | egrep -v 'grep|vpn_uninstall|anyconnect_uninstall' | cut -c 1-5`
if [ -n "${OURPROCS}" ] ; then
    for DOOMED in ${OURPROCS}; do
        echo Killing `ps -A -o pid,command -p ${DOOMED} | grep ${DOOMED} | egrep -v 'ps|grep'` >> /tmp/vpn-uninstall.log
        kill -KILL ${DOOMED} >> /tmp/vpn-uninstall.log 2>&1
    done
fi

# do daemon-reload if systemd is in place
if [ -z "${TESTINIT##*"systemd"*}" ]; then
    echo systemctl daemon-reload >> /tmp/vpn-uninstall.log
    systemctl daemon-reload >> /tmp/vpn-uninstall.log
fi

echo "Successfully removed Cisco AnyConnect Secure Mobility Client from the system." >> /tmp/vpn-uninstall.log
echo "Successfully removed Cisco AnyConnect Secure Mobility Client from the system."
exit 0

