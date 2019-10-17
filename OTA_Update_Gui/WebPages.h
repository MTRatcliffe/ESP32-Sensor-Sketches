

const char* OTA_HTML ="<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

const char* header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

const char* Index_HTML = R"=====(
<!DOCTYPE html><html><head><script>
function Request_Readings() {
ajaxLoad('Send_Sensor_Data_18650');}
var ajaxRequest = null;
if (window.XMLHttpRequest)  { ajaxRequest =new XMLHttpRequest(); }
else                        { ajaxRequest =new ActiveXObject("Microsoft.XMLHTTP"); }
function ajaxLoad(ajaxURL){
if(!ajaxRequest){ alert("AJAX is not supported."); return; }
 
ajaxRequest.open("GET",ajaxURL,true);
ajaxRequest.onreadystatechange = function(){
if(ajaxRequest.readyState == 4 && ajaxRequest.status==200){
var ajaxResult = ajaxRequest.responseText;
var data = JSON.parse( ajaxRequest.responseText);
console.log(ajaxResult);
document.getElementById("Time_stamp").value = data.Air_temp;
document.getElementById("Air_temp").value = data.Air_temp;
document.getElementById("Air_Hum").value = data.Air_Hum;
document.getElementById("Air_press").value = data.Air_press;
document.getElementById("Lght_Lux").value = data.Air_temp;
document.getElementById("Water_Temp").value = data.Air_temp;
document.getElementById("Water_EC").value = data.Air_temp;
document.getElementById("Batt_Voltage").innerHTML = data.Battery_Voltage;
document.getElementById("Batt_Charge").innerHTML = data.Battery_Percent;
}
}
ajaxRequest.send();

} 
</script>
<title>Data_Logger</title></head><body onload="Request_Readings()">
<h1>Data Logger</h1><p>For Help Contact: Mike@Aquaponicslab.org</p>
<h2>Set Date and Time </h2><button type='button'onClick=window.location='www.Sensor.com/Update'>Continue</button>
<h2>Sensor Readings</h2>
<input type="button" id = "Refresh_Readings_Button" onclick="Request_Readings()" value="Refresh Readings"/> 
<p>Time Stamp: <span id = "Time_stamp">00/00/00    00/00/000</span></p>
<p>Air Temp:<span id = "Air_temp">0.00</span>*C</p>
<p>Air Humidity:<span id = "Air_Hum">0.00</span>%</p>
<p>Air Pressure:<span id = "Air_press">0.00</span>hPa</p>
<p>Light Intensity:<span id = "Lght_Lux">0.00</span>Lux:</p>
<p>Water Temp:<span id = "Water_Temp">0.00</span>*C</p>
<p>Water EC:<span id = "Water_EC">0.00</span>mS/cm</p>
<p>Battery Voltage:<span id = "Batt_Voltage">0.00</span>V</p>
<p>Charge: <span id = "Batt_Charge">0.00</span>%</p>
<h2>Download Data Log</h2><button type='button' onClick=window.location='/Update'>Continue</button>
<h2>Upload New Firmware</h2><button type='button' onClick=window.location='/Update'>Continue</button>

</body></html> )=====";

