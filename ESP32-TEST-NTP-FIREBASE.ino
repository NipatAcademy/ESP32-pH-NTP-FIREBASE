#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#define SSID                  "Phone"
#define PASSWORD              "123456789"
#define FIREBASE_HOST         "https://environment-e3963.firebaseio.com/"
#define FIREBASE_AUTH         "NVp26j3hrk8xlWQZTqboJlSI874e8Dm1stXIgNiq"
String  TD32_Get_Firebase(String path );
int     TD32_Set_Firebase(String path, String value, bool push = false );
int     TD32_Push_Firebase(String path, String value);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedDate;
String dayStamp;
String timeStamp;
void setup() {
  Serial.begin(115200); Serial.println();
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED ) delay(400);
  Serial.println();
  Serial.println(WiFi.localIP());

  TD32_Set_Firebase("Powered ", "\" BY NIPAT ACADEMY\"");
  Serial.println( TD32_Get_Firebase("name"));
  timeClient.begin();
  timeClient.setTimeOffset(25200);
}

int cnt;
uint32_t timer;

void loop() {
  if ( millis() - timer > 3000) {
    timer = millis();
    while (!timeClient.update()) {
      timeClient.forceUpdate();
    }
    formattedDate = timeClient.getFormattedDate();
    Serial.println(formattedDate);
    int splitT = formattedDate.indexOf("T");
    dayStamp = formattedDate.substring(0, splitT);
    Serial.print("DATE: ");
    Serial.println(dayStamp);
    timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
    Serial.print("HOUR: ");
    Serial.println(timeStamp);
    delay(1000);
    float t = (float)random(2000, 4000) / 100;
    float h = (float)random(1000, 9000) / 100;

    //----------------------- Set เป็นการส่งข้อมูลทับข้อมูลเดิม -------------------------------------
    TD32_Set_Firebase("Temperature/Set/Value", String(t));
    TD32_Set_Firebase("Temperature/Set/DateTime", "\"" + timeStamp + " " + dayStamp + "\"");
    TD32_Set_Firebase("Humidity/Set/Value", String(t));
    TD32_Set_Firebase("Humidity/Set/DateTime", "\"" + timeStamp + " " + dayStamp + "\"");

    //----------------------- Push เป็นการส่งข้อมูลเพิ่มเรื่อยๆ -------------------------------------
    TD32_Push_Firebase("Temperature/Push", String(h));
    TD32_Push_Firebase("Temperature/Push", "\"" + timeStamp + " " + dayStamp + "\"");
    TD32_Push_Firebase("Humidity/Push", String(h));
    TD32_Push_Firebase("Humidity/Push", "\"" + timeStamp + " " + dayStamp + "\"");

  }
}
const char* FIREBASE_ROOT_CA =
  "-----BEGIN CERTIFICATE-----\n"
  "MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n"
  "A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n"
  "Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n"
  "MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n"
  "A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n"
  "hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n"
  "v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n"
  "eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n"
  "tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n"
  "C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n"
  "zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n"
  "mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n"
  "V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n"
  "bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n"
  "3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n"
  "J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n"
  "291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n"
  "ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n"
  "AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n"
  "TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n"
  "-----END CERTIFICATE-----\n";

int TD32_Set_Firebase(String path, String value, bool push ) {
  WiFiClientSecure ssl_client;
  String host = String(FIREBASE_HOST); host.replace("https://", "");
  if (host[host.length() - 1] == '/' ) host = host.substring(0, host.length() - 1);
  String resp = "";
  int httpCode = 404; // Not Found

  String firebase_method = (push) ? "POST " : "PUT ";
  ssl_client.setCACert(FIREBASE_ROOT_CA);
  if ( ssl_client.connect( host.c_str(), 443)) {
    String uri = ((path[0] != '/') ? String("/") : String("")) + path + String(".json?auth=") + String(FIREBASE_AUTH);
    String request = "";
    request +=  firebase_method + uri + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "User-Agent: TD_ESP32\r\n";
    request += "Connection: close\r\n";
    request += "Accept-Encoding: identity;q=1,chunked;q=0.1,*;q=0\r\n";
    request += "Content-Length: " + String( value.length()) + "\r\n\r\n";
    request += value;

    ssl_client.print(request);
    while ( ssl_client.connected() && !ssl_client.available()) delay(10);
    if ( ssl_client.connected() && ssl_client.available() ) {
      resp      = ssl_client.readStringUntil('\n');
      httpCode  = resp.substring(resp.indexOf(" ") + 1, resp.indexOf(" ", resp.indexOf(" ") + 1)).toInt();
    }
    ssl_client.stop();
  }
  else {
    Serial.println("[Firebase] can't connect to Firebase Host");
  }
  return httpCode;
}
int TD32_Push_Firebase(String path, String value) {
  return TD32_Set_Firebase(path, value, true);
}
String TD32_Get_Firebase(String path ) {
  WiFiClientSecure ssl_client;
  String host = String(FIREBASE_HOST); host.replace("https://", "");
  if (host[host.length() - 1] == '/' ) host = host.substring(0, host.length() - 1);
  String resp = "";
  String value = "";
  ssl_client.setCACert(FIREBASE_ROOT_CA);
  if ( ssl_client.connect( host.c_str(), 443)) {
    String uri = ((path[0] != '/') ? String("/") : String("")) + path + String(".json?auth=") + String(FIREBASE_AUTH);
    String request = "";
    request += "GET " + uri + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "User-Agent: TD_ESP32\r\n";
    request += "Connection: close\r\n";
    request += "Accept-Encoding: identity;q=1,chunked;q=0.1,*;q=0\r\n\r\n";

    ssl_client.print( request);
    while ( ssl_client.connected() && !ssl_client.available()) delay(10);
    if ( ssl_client.connected() && ssl_client.available() ) {
      while ( ssl_client.available()) resp += (char)ssl_client.read();
      value = resp.substring( resp.lastIndexOf('\n') + 1, resp.length() - 1);
    }
    ssl_client.stop();
  } else {
    Serial.println("[Firebase] can't connect to Firebase Host");
  }
  return value;
}
