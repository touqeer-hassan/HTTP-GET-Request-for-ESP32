#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPass";
 
void setup() {
 
  Serial.begin(115200);
  delay(1000);
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}
 
const char* root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFMTCCBBmgAwIBAgISBPlSCh6bmb205aVOU+/ev7lkMA0GCSqGSIb3DQEBCwUA\n" \
"MDIxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQswCQYDVQQD\n" \
"EwJSMzAeFw0yMjAxMTQxNzI0MTJaFw0yMjA0MTQxNzI0MTFaMBoxGDAWBgNVBAMT\n" \
"D3d3dy5zaWYuc3lzdGVtczCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n" \
"AML17T0X9HlyT5LuHq+JNwOwBYvjHEoiiJpbvq4MhMa6x9uXmRzHPzHf1QktlsVL\n" \
"mh2HxTsaGIeaKDXXLS4Pq0YY/CdhbtiLDPkaZWvBdi6YcRi7H2Dd3xTsuHcE1L7n\n" \
"ZkPdBnStA/TdSiufI4NMmWw9kjTXu8xNsNX25dLjlQVg7SBxVpsrKvxxmRROHJzC\n" \
"k8/9L2wvWheFTCBIOI8trUvXv7D9/aEUkAunZHiwzDK1NcGTgdtDlu32UFPNX9qz\n" \
"D8vqL6Az4ecdInu+CZmwxz5ABGcXXPB6asGU3U8qbnOUykcv5NuVvphQKkvHgg36\n" \
"ghrKuX05qSQ9rDzjkDkDGT8CAwEAAaOCAlcwggJTMA4GA1UdDwEB/wQEAwIFoDAd\n" \
"BgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwDAYDVR0TAQH/BAIwADAdBgNV\n" \
"HQ4EFgQUc8a10lFRVl5xuGxHwtAwXV4C62IwHwYDVR0jBBgwFoAUFC6zF7dYVsuu\n" \
"UAlA5h+vnYsUwsYwVQYIKwYBBQUHAQEESTBHMCEGCCsGAQUFBzABhhVodHRwOi8v\n" \
"cjMuby5sZW5jci5vcmcwIgYIKwYBBQUHMAKGFmh0dHA6Ly9yMy5pLmxlbmNyLm9y\n" \
"Zy8wJwYDVR0RBCAwHoILc2lmLnN5c3RlbXOCD3d3dy5zaWYuc3lzdGVtczBMBgNV\n" \
"HSAERTBDMAgGBmeBDAECATA3BgsrBgEEAYLfEwEBATAoMCYGCCsGAQUFBwIBFhpo\n" \
"dHRwOi8vY3BzLmxldHNlbmNyeXB0Lm9yZzCCAQQGCisGAQQB1nkCBAIEgfUEgfIA\n" \
"8AB3AN+lXqtogk8fbK3uuF9OPlrqzaISpGpejjsSwCBEXCpzAAABflnVNwAAAAQD\n" \
"AEgwRgIhANEP+uvg/Kj4P8grd35dDF38+lohM5cWhD33oTr/PGsuAiEAzhbWhVdM\n" \
"VPJsRXy23U88jDFKUiWW+Z7ygnoETx8AlpgAdQApeb7wnjk5IfBWc59jpXflvld9\n" \
"nGAK+PlNXSZcJV3HhAAAAX5Z1TbwAAAEAwBGMEQCIE8TVwmJC28kAM3iAxbr7PmE\n" \
"5U6xaADPo5DWdLs8iwuPAiAqNHPoAmpbTtdAye1LUuf4PGYXXewGUUDFmvdK9/ZW\n" \
"bDANBgkqhkiG9w0BAQsFAAOCAQEAroRFq5uNuVcTazlqEWKxa/bMgvzN8agQ8n5v\n" \
"bKAaOc3sK5AIvHkw6ftoHHCc76GdY9MTDDls2/nBJ4qYq2QYFFtcJVapgtx7OetY\n" \
"B/3dTmYmP/jelfafnTYafyvmtHlr+SsJJHUEhYwcAwqyN+a0cmkr+2ahOtaQIxeL\n" \
"gY3Y/JcyHqfWdk9sX64kSHJmDCD3w3Ez98Pcl4JFck8OghzynmkNWQAGjsOC/xa/\n" \
"gtBQ0CYHBMjCmvUguKQDAvW5bVeUie3oqTtLmyrRabn/68Td6Ux8Y9E6plpLBGti\n" \
"g7dEXYNG+zSwPMBbyn6na0ukyseWbCK2fx82h072jOV3JyOktg==\n" \
"-----END CERTIFICATE-----\n";
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("https://sif.systems/pump.php?id=1", root_ca); //Specify the URL and certificate
    int httpCode = http.GET();                                                  //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
  delay(5000);
}
