/*
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *  The ASF licenses this file to You under the Apache License, Version 2.0
 *  (the "License"); you may not use this file except in compliance with
 *  the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

package java.net;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.security.Permission;
import java.security.PermissionCollection;

/**
 * Regulates the access to network operations available through sockets through
 * permissions. A permission consists of a target (a host), and an associated
 * action list. The target should identify the host by either indicating the
 * (possibly wildcarded (eg. {@code .company.com})) DNS style name of the host
 * or its IP address in standard {@code nn.nn.nn.nn} ("dot") notation. The
 * action list can be made up of one or more of the following actions separated
 * by a comma:
 * <dl>
 * <dt>connect</dt>
 * <dd>requests permission to connect to the host</dd>
 * <dt>listen</dt>
 * <dd>requests permission to listen for connections from the host</dd>
 * <dt>accept</dt>
 * <dd>requests permission to accept connections from the host</dd>
 * <dt>resolve</dt>
 * <dd>requests permission to resolve the hostname</dd>
 * </dl>
 * Note that {@code resolve} is implied when any (or none) of the others are
 * present.
 * <p>
 * Access to a particular port can be requested by appending a colon and a
 * single digit to the name (eg. {@code .company.com:7000}). A range of port
 * numbers can also be specified, by appending a pattern of the form
 * <i>LOW-HIGH</i> where <i>LOW</i> and <i>HIGH</i> are valid port numbers. If
 * either <i>LOW</i> or <i>HIGH</i> is omitted it is equivalent to entering the
 * lowest or highest possible value respectively. For example:
 *
 * <pre>
 * {@code SocketPermission(&quot;www.company.com:7000-&quot;, &quot;connect,accept&quot;)}
 * </pre>
 *
 * represents the permission to connect to and accept connections from {@code
 * www.company.com} on ports in the range {@code 7000} to {@code 65535}.
 */
public final class SocketPermission extends Permission implements Serializable {

    private static final long serialVersionUID = -7204263841984476862L;

    // Bit masks for each of the possible actions
    static final int SP_CONNECT = 1;

    static final int SP_LISTEN = 2;

    static final int SP_ACCEPT = 4;

    static final int SP_RESOLVE = 8;

    // list of actions permitted for socket permission in order, indexed by mask
    // value
    @SuppressWarnings("nls")
    private static final String[] actionNames = { "", "connect", "listen", "",
            "accept", "", "", "", "resolve" };

    // If a wildcard is present store the information
    private transient boolean isPartialWild;

    private transient boolean isWild;

    // The highest port number
    private static final int HIGHEST_PORT = 65535;

    // The lowest port number
    private static final int LOWEST_PORT = 0;

    transient String hostName; // Host name as returned by InetAddress

    transient String ipString; // IP address as returned by InetAddress

    transient boolean resolved; // IP address has been resolved

    // the port range;
    transient int portMin = LOWEST_PORT;

    transient int portMax = HIGHEST_PORT;

    private String actions; // List of all actions allowed by this permission

    transient int actionsMask = SP_RESOLVE;

    /**
     * Constructs a new {@code SocketPermission} instance. The hostname can be a
     * DNS name, an individual hostname, an IP address or the empty string which
     * implies {@code localhost}. The port or port range is optional.
     * <p>
     * The action list is a comma-separated list which can consists of the
     * possible operations {@code "connect"}, {@code "listen"}, {@code "accept"}
     * , and {@code "resolve"}. They are case-insensitive and can be put
     * together in any order. {@code "resolve"} is implied per default.
     *
     * @param host
     *            the hostname this permission is valid for.
     * @param action
     *            the action string of this permission.
     */
    public SocketPermission(String host, String action) {
        super(host.isEmpty() ? "localhost" : host);
        hostName = getHostString(host);
        if (action == null) {
            throw new NullPointerException();
        }
        if (action.isEmpty()) {
            throw new IllegalArgumentException();
        }

        setActions(action);
        actions = toCanonicalActionString(action);
        // Use host since we are only checking for port presence
        parsePort(host, hostName);
    }

    /**
     * Compares the argument {@code o} to this instance and returns {@code true}
     * if they represent the same permission using a class specific comparison.
     *
     * @param other
     *            the object to compare with this {@code SocketPermission}
     *            instance.
     * @return {@code true} if they represent the same permission, {@code false}
     *         otherwise.
     * @see #hashCode
     */
    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other == null || this.getClass() != other.getClass()) {
            return false;
        }
        SocketPermission sp = (SocketPermission) other;
        if (!hostName.equalsIgnoreCase(sp.hostName)) {
            if (getIPString(true) == null || !ipString.equalsIgnoreCase(sp.getIPString(true))) {
                return false;
            }
        }
        if (this.actionsMask != SP_RESOLVE) {
            if (this.portMin != sp.portMin) {
                return false;
            }
            if (this.portMax != sp.portMax) {
                return false;
            }
        }
        return this.actionsMask == sp.actionsMask;
    }

    /**
     * Returns the hash value for this {@code SocketPermission} instance. Any
     * two objects which returns {@code true} when passed to {@code equals()}
     * must return the same value as a result of this method.
     *
     * @return the hashcode value for this instance.
     * @see #equals
     */
    @Override
    public int hashCode() {
        return hostName.hashCode() ^ actionsMask ^ portMin ^ portMax;
    }

    /**
     * Gets a comma-separated list of all actions allowed by this permission. If
     * more than one action is returned they follow this order: {@code connect},
     * {@code listen}, {@code accept}, {@code resolve}.
     *
     * @return the comma-separated action list.
     */
    @Override
    public String getActions() {
        return actions;
    }

    /**
     * Stores the actions for this permission as a bit field.
     *
     * @param actions
     *            java.lang.String the action list
     */
    private void setActions(String actions) throws IllegalArgumentException {
        if (actions.isEmpty()) {
            return;
        }
        boolean parsing = true;
        String action;
        StringBuilder sb = new StringBuilder();
        int pos = 0, length = actions.length();
        while (parsing) {
            char c;
            sb.setLength(0);
            while (pos < length && (c = actions.charAt(pos++)) != ',') {
                sb.append(c);
            }
            if (pos == length) {
                parsing = false;
            }
            action = sb.toString().trim().toLowerCase();
            if (action.equals(actionNames[SP_CONNECT])) {
                actionsMask |= SP_CONNECT;
            } else if (action.equals(actionNames[SP_LISTEN])) {
                actionsMask |= SP_LISTEN;
            } else if (action.equals(actionNames[SP_ACCEPT])) {
                actionsMask |= SP_ACCEPT;
            } else if (action.equals(actionNames[SP_RESOLVE])) {
                // do nothing
            } else {
                throw new IllegalArgumentException("Invalid action: " + action);
            }
        }
    }

    /**
     * Checks whether this {@code SocketPermission} instance allows all actions
     * which are allowed by the given permission object {@code p}. All argument
     * permission actions, hosts and ports must be implied by this permission
     * instance in order to return {@code true}. This permission may imply
     * additional actions not present in the argument permission.
     *
     * @param p
     *            the socket permission which has to be implied by this
     *            instance.
     * @return {@code true} if this permission instance implies all permissions
     *         represented by {@code p}, {@code false} otherwise.
     */
    @Override
    public boolean implies(Permission p) {
        SocketPermission sp;
        try {
            sp = (SocketPermission) p;
        } catch (ClassCastException e) {
            return false;
        }

        // tests if the action list of p is the subset of the one of the
        // receiver
        if (sp == null || (actionsMask & sp.actionsMask) != sp.actionsMask) {
            return false;
        }

        // only check the port range if the action string of the current object
        // is not "resolve"
        if (!p.getActions().equals("resolve")) {
            if ((sp.portMin < this.portMin) || (sp.portMax > this.portMax)) {
                return false;
            }
        }

        // Verify the host is valid
        return checkHost(sp);
    }

    /**
     * Creates a new {@code PermissionCollection} to store {@code
     * SocketPermission} objects.
     *
     * @return the new permission collection.
     */
    @Override
    public PermissionCollection newPermissionCollection() {
        return new SocketPermissionCollection();
    }

    /**
     * Parse the port, including the minPort, maxPort
     * @param hostPort the host[:port] one
     * @param host the host name we just get
     * @throws IllegalArgumentException If the port is not a positive number or minPort
     *                                  is not less than or equal maxPort
     */
    private void parsePort(String hostPort, String host) throws IllegalArgumentException {
       String port = hostPort.substring(host.length());
       String emptyString = "";

       if (emptyString.equals(port)) {
           // Not specified
           portMin = 80;
           portMax = 80;
           return;
       }

       if (":*".equals(port)) {
           // The port range should be 0-65535
           portMin = 0;
           portMax = 65535;
           return;
       }

       // Omit ':'
       port = port.substring(1);
       int negIdx = port.indexOf('-');
       String strPortMin = emptyString;
       String strPortMax = emptyString;
       if (-1 == negIdx) {
           // No neg mark, only one number
           strPortMin = port;
           strPortMax = port;
       } else {
           strPortMin = port.substring(0, negIdx);
           strPortMax = port.substring(negIdx + 1);
           if (emptyString.equals(strPortMin)) {
               strPortMin = "0";
           }
           if (emptyString.equals(strPortMax)) {
               strPortMax = "65535";
           }
       }
       try {
           portMin = Integer.valueOf(strPortMin).intValue();
           portMax = Integer.valueOf(strPortMax).intValue();

           if (portMin > portMax) {
               throw new IllegalArgumentException("MinPort is greater than MaxPort: " + port);
           }
       } catch (NumberFormatException e) {
           throw new IllegalArgumentException("Invalid port number: " + port);
       }
    }

    /**
     * Creates a canonical action list.
     *
     * @param action
     *            java.lang.String
     *
     * @return java.lang.String
     */
    private String toCanonicalActionString(String action) {
        if (action == null || action.isEmpty() || actionsMask == SP_RESOLVE) {
            return actionNames[SP_RESOLVE]; // If none specified return the
        }
        // implied action resolve
        StringBuilder sb = new StringBuilder();
        if ((actionsMask & SP_CONNECT) == SP_CONNECT) {
            sb.append(',');
            sb.append(actionNames[SP_CONNECT]);
        }
        if ((actionsMask & SP_LISTEN) == SP_LISTEN) {
            sb.append(',');
            sb.append(actionNames[SP_LISTEN]);
        }
        if ((actionsMask & SP_ACCEPT) == SP_ACCEPT) {
            sb.append(',');
            sb.append(actionNames[SP_ACCEPT]);
        }
        sb.append(',');
        sb.append(actionNames[SP_RESOLVE]);// Resolve is always implied
        // Don't copy the first ','.
        return actions = sb.substring(1, sb.length());
    }

    private String getIPString(boolean isCheck) {
        if (!resolved) {
            try {
                ipString = InetAddress.getHostNameInternal(hostName, isCheck);
            } catch (UnknownHostException e) {
                // ignore
            }
            resolved = true;
        }
        return ipString;
    }

    /**
     * Get the host part from the host[:port] one. The host should be
     *
     * <pre>
     *      host = (hostname | IPv4address | IPv6reference | IPv6 in full uncompressed form)
     * </pre>
     *
     * The wildcard "*" may be included once in a DNS name host specification.
     * If it is included, it must be in the leftmost position
     *
     * @param host
     *            the {@code host[:port]} string.
     * @return the host name.
     * @throws IllegalArgumentException
     *             if the host is invalid.
     */
    private String getHostString(String host) throws IllegalArgumentException {
        host = host.trim();
        int idx = -1;
        idx = host.indexOf(':');
        isPartialWild = (host.length() > 0 && host.charAt(0) == '*');
        if (isPartialWild) {
            resolved = true;
            isWild = (host.length() == 1);
            if (isWild) {
                return host;
            }
            if (idx > -1) {
                host = host.substring(0, idx);
            }
            return host.toLowerCase();
        }

        int lastIdx = host.lastIndexOf(':');

        if (idx == lastIdx) {
            if (-1 != idx) {
                // only one colon, should be port
                host = host.substring(0, idx);
            }
            return host.toLowerCase();
        }
            // maybe ipv6
        boolean isFirstBracket = (host.charAt(0) == '[');
        if (!isFirstBracket) {
            // No bracket, should be in full form
            int colonNum = 0;
            for (int i = 0; i < host.length(); ++i) {
                if (host.charAt(i) == ':') {
                    colonNum++;
                }
            }
            // Get rid of the colon before port
            if (8 == colonNum) {
                host = host.substring(0, lastIdx);
            }
            if (isIP6AddressInFullForm(host)) {
                return host.toLowerCase();
            }
            throw new IllegalArgumentException("Invalid port number: " + host);
        }
        // forward bracket found
        int bbracketIdx = host.indexOf(']');
        if (-1 == bbracketIdx) {
            // no back bracket found, wrong
            throw new IllegalArgumentException("Invalid port number: " + host);
        }
        host = host.substring(0, bbracketIdx + 1);
        if (isValidIP6Address(host)) {
            return host.toLowerCase();
        }
        throw new IllegalArgumentException("Invalid port number: " + host);
    }

    private static boolean isValidHexChar(char c) {
        return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
    }

    private static boolean isValidIP4Word(String word) {
        char c;
        if (word.length() < 1 || word.length() > 3) {
            return false;
        }
        for (int i = 0; i < word.length(); i++) {
            c = word.charAt(i);
            if (!(c >= '0' && c <= '9')) {
                return false;
            }
        }
        if (Integer.parseInt(word) > 255) {
            return false;
        }
        return true;
    }

    private static boolean isIP6AddressInFullForm(String ipAddress) {
        if (isValidIP6Address(ipAddress)) {
            int doubleColonIndex = ipAddress.indexOf("::");
            if (doubleColonIndex >= 0) {
                // Simplified form which contains ::
                return false;
            }
            return true;
        }
        return false;
    }

    private static boolean isValidIP6Address(String ipAddress) {
        int length = ipAddress.length();
        boolean doubleColon = false;
        int numberOfColons = 0;
        int numberOfPeriods = 0;
        int numberOfPercent = 0;
        String word = "";
        char c = 0;
        char prevChar = 0;
        int offset = 0; // offset for [] IP addresses

        if (length < 2) {
            return false;
        }

        for (int i = 0; i < length; i++) {
            prevChar = c;
            c = ipAddress.charAt(i);
            switch (c) {

                // case for an open bracket [x:x:x:...x]
            case '[':
                if (i != 0) {
                    return false; // must be first character
                }
                if (ipAddress.charAt(length - 1) != ']') {
                    return false; // must have a close ]
                }
                offset = 1;
                if (length < 4) {
                    return false;
                }
                break;

                // case for a closed bracket at end of IP [x:x:x:...x]
            case ']':
                if (i != length - 1) {
                    return false; // must be last character
                }
                if (ipAddress.charAt(0) != '[') {
                    return false; // must have a open [
                }
                break;

                // case for the last 32-bits represented as IPv4 x:x:x:x:x:x:d.d.d.d
            case '.':
                numberOfPeriods++;
                if (numberOfPeriods > 3) {
                    return false;
                }
                if (!isValidIP4Word(word)) {
                    return false;
                }
                if (numberOfColons != 6 && !doubleColon) {
                    return false;
                }
                // a special case ::1:2:3:4:5:d.d.d.d allows 7 colons with an
                // IPv4 ending, otherwise 7 :'s is bad
                if (numberOfColons == 7 && ipAddress.charAt(0 + offset) != ':'
                && ipAddress.charAt(1 + offset) != ':') {
                    return false;
                }
                word = "";
                break;

            case ':':
                numberOfColons++;
                if (numberOfColons > 7) {
                    return false;
                }
                if (numberOfPeriods > 0) {
                    return false;
                }
                if (prevChar == ':') {
                    if (doubleColon) {
                        return false;
                    }
                    doubleColon = true;
                }
                word = "";
                break;
            case '%':
                if (numberOfColons == 0) {
                    return false;
                }
                numberOfPercent++;

                // validate that the stuff after the % is valid
                if ((i + 1) >= length) {
                    // in this case the percent is there but no number is
                    // available
                    return false;
                }
                try {
                    Integer.parseInt(ipAddress.substring(i + 1));
                } catch (NumberFormatException e) {
                    // right now we just support an integer after the % so if
                    // this is not
                    // what is there then return
                    return false;
                }
                break;

            default:
                if (numberOfPercent == 0) {
                    if (word.length() > 3) {
                        return false;
                    }
                    if (!isValidHexChar(c)) {
                        return false;
                    }
                }
                word += c;
            }
        }

        // Check if we have an IPv4 ending
        if (numberOfPeriods > 0) {
            if (numberOfPeriods != 3 || !isValidIP4Word(word)) {
                return false;
            }
        } else {
            // If we're at then end and we haven't had 7 colons then there is a
            // problem unless we encountered a doubleColon
            if (numberOfColons != 7 && !doubleColon) {
                return false;
            }

            // If we have an empty word at the end, it means we ended in either
            // a : or a .
            // If we did not end in :: then this is invalid
            if (numberOfPercent == 0) {
                if (word == "" && ipAddress.charAt(length - 1 - offset) == ':'
                && ipAddress.charAt(length - 2 - offset) != ':') {
                    return false;
                }
            }
        }

        return true;
    }

    /**
     * Determines whether or not this permission could refer to the same host as
     * sp.
     */
    boolean checkHost(SocketPermission sp) {
        if (isPartialWild) {
            if (isWild) {
                return true; // Match on any host
            }
            int length = hostName.length() - 1;
            return sp.hostName.regionMatches(sp.hostName.length() - length,
                    hostName, 1, length);
        }
        // The ipString may not be the same, some hosts resolve to
        // multiple ips
        return (getIPString(false) != null && ipString.equals(sp.getIPString(false)))
                || hostName.equals(sp.hostName);
    }

    private void writeObject(ObjectOutputStream stream) throws IOException {
        stream.defaultWriteObject();
    }

    private void readObject(ObjectInputStream stream) throws IOException,
            ClassNotFoundException {
        stream.defaultReadObject();
        // Initialize locals
        isPartialWild = false;
        isWild = false;
        portMin = LOWEST_PORT;
        portMax = HIGHEST_PORT;
        actionsMask = SP_RESOLVE;
        hostName = getHostString(getName());
        parsePort(getName(), hostName);
        setActions(actions);
    }
}
