#include <pgmspace.h>
String mac = (WiFi.macAddress());
char __mac[sizeof(mac)];

// const char ssid[]="hotspot2";
// const char password[] ="abc123098a#";

const char *mqtt_server = "18.213.166.207";
const int mqtt_port = 1883;
const char *mqtt_user = "device";
const char *mqtt_pass = "device";
const char *mqtt_client_name = __mac; //"12312312312332212";// any random alphanumeric stirng
//////////////////////////////
#define BUFFER_SIZE 250

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIULaFytFGcnRJOEpDE/Ml4VwJ4P74wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIyMTAyNzEwMjYx
MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAOqF7koqlk1VlUDl6hxZ
RxR/KZCELgYEQRUz3gDAnIv+uHm/VDH4hbfhNBXpsSFWyqQMmRaYPBZ4x4WjWXog
kB0VA4tPTerBf4rZsSHIJzMeIZ5puU3GLMGRIinkWyssW3uEenSR1W6e+7vmipml
DeR/SiEMURz5O/P3Ry1CECTMgNbO9nNNkxM2pPFHSaMQpJV/I5nYWLlV8kjRSIQE
Tv7w94AUMEeDuMkDZjF6sUY77LKRAFVBujWE89xsUgefkex0feXsNzz2uVc4h39Q
cgzmh3R65j/40Vq7278E7nNhEw57SxRzYiF+0TguKzaWwFanWxxRHU89zjm+07lj
aN8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUNqAjoec31ITDc4b2/tB0u+h8U1EwHQYD
VR0OBBYEFOYDvaQJKRbybuTjVsjSjgiqRxgvMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAHw2O7AW9kTQSbYyBcpajAhuGa
YCYuONEPpVHePkgI8aDP/o2zaYhBUtX7VyuvhEIz1h4xccaLJL/P8gqi+fX/y6KQ
wx6IAYaiq002o72GDVcJe9Xv+cYvJEuDnUjMGYsvZh40rx9ZRZddsln9kU9CYC33
h1lJjTCCPUlJtrZctyXI29+gSkvlSNTwcIk6pYPVVyKLb4b/vkuPWX9VX+jf8KpC
Pf0Uo90m8MeKsFXo2HQVwqh+4MvKUA0BDDLTI4Ktj4MqiJ2HmjdEH3W1AM4lLX2/
NJBbq+9+Vu8Gz4WI/fkq9E+wjkc22370Z4oMLqSIWugqW8Rg10thZ9nXjl1y
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEA6oXuSiqWTVWVQOXqHFlHFH8pkIQuBgRBFTPeAMCci/64eb9U
MfiFt+E0FemxIVbKpAyZFpg8FnjHhaNZeiCQHRUDi09N6sF/itmxIcgnMx4hnmm5
TcYswZEiKeRbKyxbe4R6dJHVbp77u+aKmaUN5H9KIQxRHPk78/dHLUIQJMyA1s72
c02TEzak8UdJoxCklX8jmdhYuVXySNFIhARO/vD3gBQwR4O4yQNmMXqxRjvsspEA
VUG6NYTz3GxSB5+R7HR95ew3PPa5VziHf1ByDOaHdHrmP/jRWrvbvwTuc2ETDntL
FHNiIX7ROC4rNpbAVqdbHFEdTz3OOb7TuWNo3wIDAQABAoIBAGawLh6bdyR1jNzV
zySKku0OoQx+VAieZED8bQC3VdSWu//THvKidyqEmWHe6YhHkIM0YPPbxLOyPurt
E4i+KVwSj3K4Ts2z3DzYBQ9drIxdbSsH7/N2CrLW8baWHrVQvt3erB/Omz3Mrz0f
PSD5fJPIiJTf58Rf/Thd1fSjMJ5rdom4zrIorPHZeYN3HTcz3y9dCNWwfakvgvwp
bWpKjzsgIZhCOT/qm8ngphk7EwLzkJSOAHA9NuRVQNOcdH78fqIES/ZL62pZIDPF
Zcke4Q+JPOYLYfQwSvt0h7L+MioDHAjfhTGrWank/M0pe+8w2afXgBNUgYgIAL0h
o0PxR4ECgYEA9oYAWYJgmrFTf7pry4Al/9TG2tj6oqspRCjkq2RJEaKPYguiH/jm
BqoSyERRHatw6PXNu34iwPWh9tW1+ZqTtu7HgySUKARCR3m4m+2rqAhB4aGUDgD1
nCvPyNFbWrwQL7pD0AbNizOvHmw4UpsUJSs47UB91kuCcJEcLp1SGXkCgYEA84nW
LKbHcDAoRZJYvSuK4Ye62gk45AB/N3oYWUpWvSG4wSENfdbTHjRh4SObOrJbgUYp
EVPlB6b6R6uZOdlyXMCzWXBFIaZt+yKbK1CDgwUxj8b7CsdzHxjNW3F/2gM0km67
9V5uto1VK3ZVQagHRfL34uDaA5oXo43sFHdzVxcCgYBDWPhfe67IlAkrq9InFitL
aOWqg/x01C3B4SoXaJ5NowtozaTM90JgL7ZR39gJMvz1p7E8t4jnDjPhKyE7v277
WuBGg4e2JvO0cxxr/NIYZakZ6vp3mOuAbrelNQywDRCe+VPtUO52SPheZ1I7vwIR
5Wz349Z85MQN3JbGZVQ4gQKBgQDCrCTCzpJP0H7wlfpPRNYgT6ICFisevnLywqth
/LV3O9R2tNgXBjj+RPsUv6Se9+GDZbUAP+KtCkG4NqgmAPaUxAjZbpAkROhXPiNx
LUvi2Kz0dCdKR4Jzkhzdgs2jVLqabt/aVKEFVdaGBnJCKHGf7YdPGVPMW0mYGKNk
/NL7AwKBgQCW4ZrJ6v71Wkf5rnc0TFdraMzyX2hlN9ayCURxphsio2G0Qp/JncN3
wgNzMehTP8PRMofOI0o6zrG8DqTfSCDZ7Pr4rkxvuCd8LfitQaviW0sI/G9FFF8I
ib+zQOGPefGFSiFYWEHLeQ7muVDlqhMA6b9AUAoR77iDptrWMzLa8A==
-----END RSA PRIVATE KEY-----
)KEY";