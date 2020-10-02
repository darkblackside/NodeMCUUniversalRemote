#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>

const char* ssid = "xxxx"; //  your own hostpot name 
const char* password = "xxxx"; // and password

uint16_t RECV_PIN = 4;

IPAddress ip(192,168,0,7); // your ip address
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

IRsend irsend(5);
IRrecv irrecv(RECV_PIN);
decode_results results;

void handleRoot() {
  server.send(200, "text/plain", "<a href='/commands'>UNIVERSAL Remote - Commands</a>");
}

void handleCommand() {
  long pre = -1;
  long command = -1;
  int type = -1;

  if(server.args() == 0)
  {
    server.send(200, "application/json", "[{\"name\":\"panasonicPower\",\"pre\":‭16388‬, \"command\":‭83934393, \"type\":" + String(PANASONIC) + "}," +
                                          "{\"name\":\"panasonicTV\",\"pre\":‭16388‬, \"command\":‭‭83900732‬, \"type\":" + String(PANASONIC) + "}‬‬," +
                                          "{\"name\":\"panasonicDVRDVD\",\"pre\":‭16388‬, \"command\":‭‭‭83950076‬‬, \"type\":" + String(PANASONIC) + "}‬‬," +
                                          "{\"name\":\"panasonicMusic\",\"pre\":‭16388‬, \"command\":‭‭‭86543521‬‬, \"type\":" + String(PANASONIC) + "}‬‬," +
                                          "{\"name\":\"panasonicVolUp\",\"pre\":‭16388‬, \"command\":‭‭‭83887105‬‬, \"type\":" + String(PANASONIC) + "}‬‬," +
                                          "{\"name\":\"panasonicVolDown\",\"pre\":‭16388‬, \"command\":‭‭‭83920001‬‬, \"type\":" + String(PANASONIC) + "}‬‬," +
                                          "{\"name\":\"panasonicLessSubwoofer\",\"pre\":‭16388‬, \"command\":‭‭‭86556048‬‬, \"type\":" + String(PANASONIC) + "}‬‬," +
                                          "{\"name\":\"panasonicMoreSubwoofer\",\"pre\":‭16388‬, \"command\":‭‭‭86523152‬‬, \"type\":" + String(PANASONIC) + "}‬‬," +
                                          "{\"name\":\"JVC\",\"pre\":‭?‬, \"command\":‭‭?‬, \"type\":" + String(JVC) + "}‬‬," +
                                          "{\"name\":\"NEC\",\"pre\":‭?‬, \"command\":‭‭?‬, \"type\":" + String(NEC) + "}‬‬," +
                                          "{\"name\":\"RC5\",\"pre\":‭?‬, \"command\":‭‭?‬, \"type\":" + String(RC5) + "}‬‬," +
                                          "{\"name\":\"RC6\",\"pre\":‭?‬, \"command\":‭‭?‬, \"type\":" + String(RC6) + "}‬‬," +
                                          "{\"name\":\"SamsungPower\",\"pre\":‭7, \"command\":‭‭‭‭3772793023‬‬‬, \"type\":" + String(SAMSUNG) + "}‬‬," +
                                          "{\"name\":\"SANYO\",\"pre\":‭?‬, \"command\":‭‭?‬, \"type\":" + String(SANYO) + "}‬‬," +
                                          "{\"name\":\"Sony\",\"pre\":‭?‬, \"command\":‭‭?‬, \"type\":" + String(SONY) + "}‬‬," +
                                          "{\"name\":\"LG\",\"pre\":‭?‬, \"command\":‭‭?‬, \"type\":" + String(LG) + "}‬‬" +
                                          "‬‬]");
  }
  else if(server.args() == 3)
  {
    for (int i = 0; i < server.args(); i++)
    {
      if(server.argName(i) == "pre")
      {
        pre = server.arg(i).toInt();
      }
      else if(server.argName(i) == "command")
      {
        command = server.arg(i).toInt();
      }
      else if(server.argName(i) == "type")
      {
        type = server.arg(i).toInt();
      }
  
      String typeString = String(type);
      
      if (type == DENON){
        irsend.sendDenon(pre, command);
      }
      else if (type == DISH){
        irsend.sendDISH(pre, command);
      }
      else if (type == GREE){
        irsend.sendGree(pre, command);
      }
      else if (type == JVC){
        irsend.sendJVC(pre, command);
      }
      else if (type == LG){
        irsend.sendLG(pre, command);
      }
      else if (type == MAGIQUEST){
        irsend.sendMagiQuest(pre, command);
      }
      else if (type == MITSUBISHI){
        irsend.sendMitsubishi(pre, command);
      }
      else if (type == NEC){
        irsend.sendNEC(pre, command);
      }
      else if (type == NIKAI){
        irsend.sendNikai(pre, command);
      }
      else if (type == PANASONIC){
        irsend.sendPanasonic(pre, command);
        typeString = "PANASONIC";
      }
      else if (type == RC5){
        irsend.sendRC5(pre, command);
      }
      else if (type == RC6){
        irsend.sendRC6(pre, command);
      }
      else if (type == RCMM){
        irsend.sendRCMM(pre, command);
      }
      else if (type == SAMSUNG){
        irsend.sendSAMSUNG(pre, command);
      }
      else if (type == SANYO){
        irsend.sendSanyoLC7461(pre, command);
      }
      else if (type == SHARP){
        irsend.sendSharpRaw(pre, command);
      }
      else if (type == SHERWOOD){
        irsend.sendSherwood(pre, command);
      }
      else if (type == SONY){
        irsend.sendSony(pre, command);
      }
      else if (type == WHYNTER){
        irsend.sendWhynter(pre, command);
      }
      else {
        server.send(500, "text/html", "Protocol not implemented!");
      }
      
      server.send(200, "application/json", "{\"command\":{\"pre\":‭" + String(pre) + "‬, \"command\":‭ " + String(command) + ", \"type\":" + String(type) + "}}‬");
    }
  }
  else if(server.args() == 1)
  {
    String commands = "";
    uint16_t middle[100];
    uint16_t last = 0;
    
    for (int i = 0; i < 100; i++) // ...initialize it
    {
        middle[i] = 0;
    }

    String lastNumber = "";
    
    if(server.argName(0) == "command")
    {
      commands = server.arg(0);
      Serial.println(commands);
      char commandArray[1000];
      commands.toCharArray(commandArray, 1000);

      boolean end = false;
      int currentCharIndex = 0;
      char currentChar = '\0';
      while(!end)
      {
        currentChar = commandArray[currentCharIndex];

        if(currentChar == ',')
        {
          if(last == 0)
          {
            lastNumber = "";
            last++;
          }
          else
          {
            Serial.println(lastNumber);
            middle[last-1] = lastNumber.toInt();
            lastNumber = "";
            last++;
          }
        }
        else if(currentChar == '\0')
        {
          Serial.println("end");
          end = true;
          last = last-1;
          middle[last-1] = lastNumber.toInt();
          last++;
        }
        else
        {
          Serial.println("Add: " + String(currentChar));
          lastNumber += String(currentChar);
        }

        currentCharIndex++;
      }
    }   

    irsend.sendRaw(middle, last, 38);
    server.send(200, "plain/text", "sent");
  }
  
  server.send(400, "plain/text", "invalid parameters‬");
}

void handleReadNewCommand(){
  String result = "";
  bool first = true;
  int middle[100];
  int last = 0;
  int counter = 0;

  for (int i = 0; i < 100; i++) // ...initialize it
  {
      middle[i] = 0;
  }
  
  for(int i = 0; i < 20; i++)
  {
    if (irrecv.decode(&results)) {

      for(int j = 0; j < results.rawlen; j++)
      {
        middle[j] = ((middle[j]*counter) + results.rawbuf[j])/(counter+1);
      }

      if(last < results.rawlen)
      {
        last = results.rawlen;
        Serial.println(String(last));
      }
      
      counter++;
      
      irrecv.resume();  // Receive the next value
    }
    delay(100);
  }

  for(int i = 0; i < last; i++)
  {
    if(i != 0)
    {
      result += ",";
    }
    result += middle[i];
  }
  
  server.send(200, "application/json", "{\"commands\":[" + result + "]}");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  irsend.begin();
  irrecv.enableIRIn();
  Serial.begin(115200);// communication of hardware 
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/commands", handleCommand);
  server.on("/read", handleReadNewCommand);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
