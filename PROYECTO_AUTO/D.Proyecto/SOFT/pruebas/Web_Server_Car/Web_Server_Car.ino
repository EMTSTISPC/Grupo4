#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <iostream>
#include <sstream>
#include <AccelStepper.h>
/*#include <ESP32Servo.h>

#define DUMMY_SERVO1_PIN 12     
#define PAN_PIN 14

Servo dummyServo1;
Servo panServo;*/

#define HALFSTEP 8

// definir pines del primer motor
#define motorPin1 4  
#define motorPin2 5  
#define motorPin3 6  
#define motorPin4 7 

// definir pines del segundo motor
#define motorPin5 8
#define motorPin6 9
#define motorPin7 10
#define motorPin8 11

/*AccelStepper stepper1 (HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2 (HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);*/

#define LIGHT_PIN 4

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define STOP 0

#define FORWARD 1
#define BACKWARD -1

const int PWMResolution = 8;
const int PWMSpeedChannel = 2;
const int PWMLightChannel = 3;

//Camera related constants
/*#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22*/

const char* ssid     = "MyWiFiCar";
const char* password = "12345678";

// WebServer
AsyncWebServer server(80);
AsyncWebSocket wsCamera("/Camera");
AsyncWebSocket wsCarInput("/CarInput");

uint32_t cameraClientId = 0;

// Interface html + css + js
const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(
<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
        .arrows {
            font-size: 40px;
            color: black;
        }

        td.button {
            background-color: cyan;
            border-radius: 25%;
            box-shadow: 5px 5px #888888;
        }

        td.button:active {
            transform: translate(5px, 5px);
            box-shadow: none;
        }

        .noselect {
            -webkit-touch-callout: none;
            /* iOS Safari */
            -webkit-user-select: none;
            /* Safari */
            -khtml-user-select: none;
            /* Konqueror HTML */
            -moz-user-select: none;
            /* Firefox */
            -ms-user-select: none;
            /* Internet Explorer/Edge */
            user-select: none;
            /* Non-prefixed version, currently
                                      supported by Chrome and Opera */
        }

        .slidecontainer {
            width: 100%;
        }

        .slider {
            -webkit-appearance: none;
            width: 100%;
            height: 15px;
            border-radius: 5px;
            background: #d3d3d3;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
        }

        .slider:hover {
            opacity: 1;
        }

        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: red;
            cursor: pointer;
        }

        .slider::-moz-range-thumb {
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: red;
            cursor: pointer;
        }
    </style>

</head>
<h1>Inspección de ductos</h1>

<body class="noselect" align="center" style="background-color:white">
    <table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" CELLSPACING=10>
        <tr>
            <img id="cameraImage" src="" style="width:400px;height:250px"></td>
        </tr>
        <tr>
            <td></td>
            <td class="button" ontouchstart='sendButtonInput("MoveCar","1")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">&#8679;</span></td>
            <td></td>
        </tr>
        <tr>
            <td class="button" ontouchstart='sendButtonInput("MoveCar","3")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">&#8678;</span></td>
            <td class="button" ontouchstart='sendButtonInput("MoveCar","5")' ontouchend='sendButtonInput("MoveCar"
                ,"0")'><span class="">STOP</span></td>
            <td class="button" ontouchstart='sendButtonInput("MoveCar","4")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">&#8680;</span></td>
        </tr>
        <tr>
            <td></td>
            <td class="button" ontouchstart='sendButtonInput("MoveCar","2")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">&#8681;</span></td>
            <td></td>
        </tr>
        <tr/>
        <tr/>
        <tr>
            <td style="text-align:left"><b>Velocidad:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="150" class="slider" id="Velocidad" oninput='sendButtonInput("Velocidad",value)'>
                </div>
            </td>
        </tr>
        <tr>
            <td style="text-align:left"><b>Luz:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="0" class="slider" id="Luz" oninput='sendButtonInput("Luz",value)'>
                </div>
            </td>
        </tr>
        <tr>
            <td style="text-align:left"><b>Paneo:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="180" value="90" class="slider" id="Pan" oninput='sendButtonInput("Pan",value)'>
                </div>
            </td>
        </tr>
    </table>

    <script>
        var webSocketCameraUrl = "ws:\/\/" + window.location.hostname + "/Camera";
        var webSocketCarInputUrl = "ws:\/\/" + window.location.hostname + "/CarInput";
        var websocketCamera;
        var websocketCarInput;

        function initCameraWebSocket() {
            websocketCamera = new WebSocket(webSocketCameraUrl);
            websocketCamera.binaryType = 'blob';
            websocketCamera.onopen = function(event) {};
            websocketCamera.onclose = function(event) {
                setTimeout(initCameraWebSocket, 2000);
            };
            websocketCamera.onmessage = function(event) {
                var imageId = document.getElementById("cameraImage");
                imageId.src = URL.createObjectURL(event.data);
            };
        }

        function initCarInputWebSocket() {
            websocketCarInput = new WebSocket(webSocketCarInputUrl);
            websocketCarInput.onopen = function(event) {
                sendButtonInput("Velocidad", document.getElementById("Velocidad").value);
                sendButtonInput("Luz", document.getElementById("Luz").value);
                sendButtonInput("Paneo", document.getElementById("Paneo").value);
            };
            websocketCarInput.onclose = function(event) {
                setTimeout(initCarInputWebSocket, 2000);
            };
            websocketCarInput.onmessage = function(event) {};
        }

        function initWebSocket() {
            initCameraWebSocket();
            initCarInputWebSocket();
        }

        function sendButtonInput(key, value) {
            var data = key + "," + value;
            websocketCarInput.send(data);
        }

        window.onload = initWebSocket;
        document.getElementById("mainTable").addEventListener("touchend", function(event) {
            event.preventDefault()
        });
    </script>
</body>

</html>
)HTMLHOMEPAGE";

void speedMotor(int motorVelocidad)
{
//  stepper1.setSpeed(motorVelocidad);
//  stepper2.setSpeed(motorVelocidad);
}

void rotateMotor(int motorNumber, int motorDirection)
{
 /* if (motorDirection == FORWARD)
  {
    motorNumber.setMaxSpeed(1000);
    motorNumber.setSpeed(80);         //para controlar velocidad 

  }
  else if (motorDirection == BACKWARD)
  {
    motorNumber.setMaxSpeed(1000);
    motorNumber.setSpeed(-80);           //para controlar velocidad
   
  }
  else
  {

      
  }*/
}

void moveCar(int inputValue)
{
  Serial.printf("Got value as %d\n", inputValue);  
 /* switch(inputValue)
  {

    case UP:
      rotateMotor(stepper1, FORWARD);
      rotateMotor(stepper2, FORWARD);                  
      break;
  
    case DOWN:
      rotateMotor(stepper1, BACKWARD);
      rotateMotor(stepper2, BACKWARD);  
      break;
  
    case LEFT:
      rotateMotor(stepper1 FORWARD);
      rotateMotor(stepper2, BACKWARD);  
      break;
  
    case RIGHT:
      rotateMotor(stepper1, BACKWARD);
      rotateMotor(stepper2, FORWARD); 
      break;
 
    case STOP:
      rotateMotor(stepper1, STOP);
      rotateMotor(stepper2, STOP);    
      break;
  
    default:
      rotateMotor(stepper1, STOP);
      rotateMotor(stepper2, STOP);    
      break;
  }*/
}

void handleRoot(AsyncWebServerRequest *request) 
{
  request->send_P(200, "text/html", htmlHomePage);
}

void handleNotFound(AsyncWebServerRequest *request) 
{
    request->send(404, "text/plain", "File Not Found");
}

void onCarInputWebSocketEvent(AsyncWebSocket *server, 
                      AsyncWebSocketClient *client, 
                      AwsEventType type,
                      void *arg, 
                      uint8_t *data, 
                      size_t len) 
{                      
  switch (type) 
  {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      moveCar(0);
      ledcWrite(PWMLightChannel, 0);  
      break;
    case WS_EVT_DATA:
      AwsFrameInfo *info;
      info = (AwsFrameInfo*)arg;
      if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) 
      {
        std::string myData = "";
        myData.assign((char *)data, len);
        std::istringstream ss(myData);
        std::string key, value;
        std::getline(ss, key, ',');
        std::getline(ss, value, ',');
        Serial.printf("Key [%s] Value[%s]\n", key.c_str(), value.c_str()); 
        int valueInt = atoi(value.c_str());     
        if (key == "MoveCar")
        {
          moveCar(valueInt);        
        }
        else if (key == "Speed")
        {
          speedMotor(valueInt);
        }
        else if (key == "Light")
        {
          ledcWrite(PWMLightChannel, valueInt);         
        }     
      }
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;  
  }
}

void onCameraWebSocketEvent(AsyncWebSocket *server, 
                      AsyncWebSocketClient *client, 
                      AwsEventType type,
                      void *arg, 
                      uint8_t *data, 
                      size_t len) 
{                      
  switch (type) 
  {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      cameraClientId = client->id();
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      cameraClientId = 0;
      break;
    case WS_EVT_DATA:
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;  
  }
}

void setupCamera()
{
 /* camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) 
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }  

  if (psramFound())
  {
    heap_caps_malloc_extmem_enable(20000);  
    Serial.printf("PSRAM initialized. malloc to take memory from psram above this size");    
  }  */
}

void sendCameraPicture()
{
  /*if (cameraClientId == 0)
  {
    return;
  }
  unsigned long  startTime1 = millis();
  //capture a frame
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) 
  {
      Serial.println("Frame buffer could not be acquired");
      return;
  }

  unsigned long  startTime2 = millis();
  wsCamera.binary(cameraClientId, fb->buf, fb->len);
  esp_camera_fb_return(fb);
    
  //Wait for message to be delivered
  while (true)
  {
    AsyncWebSocketClient * clientPointer = wsCamera.client(cameraClientId);
    if (!clientPointer || !(clientPointer->queueIsFull()))
    {
      break;
    }
    delay(1);
  }
  
  unsigned long  startTime3 = millis();  
  Serial.printf("Time taken Total: %d|%d|%d\n",startTime3 - startTime1, startTime2 - startTime1, startTime3-startTime2 ); */
}

void setUpPinModes()
{
  /*
  //Set up flash light
  ledcSetup(PWMLightChannel, 1000, 8);
  pinMode(LIGHT_PIN, OUTPUT);    
  ledcAttachPin(LIGHT_PIN, PWMLightChannel); */
}


void setup(void) 
{
  setUpPinModes(); 
  Serial.begin(9600);
  
// conexion a internet
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
      
  wsCamera.onEvent(onCameraWebSocketEvent);
  server.addHandler(&wsCamera);

  wsCarInput.onEvent(onCarInputWebSocketEvent);
  server.addHandler(&wsCarInput);

  server.begin();
  Serial.println("HTTP server started");

  setupCamera();
}


void loop() 
{
  wsCamera.cleanupClients(); 
  wsCarInput.cleanupClients(); 
  sendCameraPicture(); 
  //Serial.printf("SPIRam Total heap %d, SPIRam Free Heap %d\n", ESP.getPsramSize(), ESP.getFreePsram());
}
