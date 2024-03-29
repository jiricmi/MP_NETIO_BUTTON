<html>
<head>
<style>
        body {
            font-family: "Helvetica",serif;

        }
    )
</style>
</head>
<body>
<h1>NETIO button tutorial</h1>
<h2>How to set it up</h2>
<ol>
<li>Turn it on with ON/OFF switch</li>
<li>Hold both buttons until red light blinks once.</li>
<li>Open WiFi manager and find <b>NETIO-BUTTON</b> network and search <b>192.168.4.1</b> in internet browser</li>
<li>Under WiFis find your WiFi and click on it after that enter your password</li>
<li>After connecting, copy IP address of the device, reconnect to your network and enter new IP to your browser</li>
</ol>
<h2>Connect to Netio socket</h2>
<ol>
<li>Select <b>Devices</b> on main screen</li>
<li>Click on button <b>add</b></li>
<li>Enter IP adress of Netio socket (only IP without http:// or /netio.json)
<li>Enter JSON string</li>
<li>Choose which button should use this command and submit</li>
<li> You can delete each record in table by clicking on button <b>Delete</b>
<li> On main screen click on button <b>Deep sleep</b> to end <b>conf-mode</b>
</ol>

<h2>Basic info</h2>
<p>
This is prototype of NETIO button that allow you to control the NETIO socket.
It works on sending HTTP request method.
On the other side, this communication is handled by the socket via JSON API. Button is made with small consumption. Button is only up when user sends HTTP request or turns on conf-mode.
</p>
<h3>Device structure</h3>
<p>
Device has 2 buttons with S1 and S2 marks. They are used for <b>JSON configure</b>.
User can program those buttons via conf-mode. <br>
</p>
<h3>LED and buzzer signaling</h3>
<p>
Device has LED with green and red color.
Buzzer is connected with red color of LED.<br>
If <b>green light</b> is on, device is trying to connect to wlan or communicate with the socket. <br>
If <b>red light</b> blinks once for longer time, device entered or quited conf-mode.<br> 
If <b>red light</b> blinks 2x with buzzer signalization, connection to wlan failed. <br>
If <b>red light</b> blinks 3x with buzzer signalization, HTTP communication failed.
Probably IP address of the socket is invalid. <br>
If <b>red light</b> blinks 4x with buzzer signalization, device wasn't able to recognize input. Please hold the button little bit longer.
</p>
<h2>Conf-mode</h2>
<p>
For entering conf-mode, hold both buttons until light turn on for 400ms. After that connect to AP called <b>NETIO-BUTTON</b>. Open browser and search <b>192.168.4.1</b>.
</p>
<h3>WiFi selection</h3>
<p>
On main screen, user is able to connect device to any close-range network without security or with WES, WPA or WPA2-personal. For update WiFi list, click on <b>Scan</b> button. <br>
By clicking on button with your wanted network, you will be transfer to security page (only if network is secured). If password is checked, page will show you IP address of device selected by DHCP server in network. And now you are able to connect to conf-mode via your network and appropriate IP address.
</p>
<h3>IP address of the socket</h3>
<p>
User is able to set 10 IP addresses for each button. So one HTTP request will be send a maximum of 10 devices at once. You can add IP address via form where you also select with button should use this IP address. It is possible to delete each address.
</p>
<h3>JSON message</h3>
<p>
Behind button configure you can find feature to write JSON message to JSON API of socket. Current JSON is below the form.
</p>
<h3>Deep sleep button</h3>
<p>This button will put device to sleep. Holding both buttons during conf-mode has same effect.</p>
<h3>Disconnect button</h3>
<p>This button will disconnect device from WiFi.</p>

</body>
</html>