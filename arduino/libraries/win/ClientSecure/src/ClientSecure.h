#ifndef ClientSecure_h
#define ClientSecure_h

#include <Arduino.h>
#include <IPAddress.h>
#include <Print.h>
#include <Client.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define CIPHERS_ALL "ALL:!EXPORT:!LOW:!aNULL:!eNULL:!SSLv2"
#define CIPHERS_HIGH "HIGH:!aNULL:!kRSA:!PSK:!SRP:!MD5:!RC4"

typedef struct
{
    SSL_CTX *ctx;
    SSL *ssl;
    int sock;
    int32_t timeout;

    const char *ca_cert;
    const char *certificate;
    const char *private_key;
    const char *pskIdent; // identity for PSK cipher suites
    const char *psKey;    // key in hex for PSK cipher suites

    const char *ciphers;
    const char *sni_host_name;
    int verify;
} secure_contex;

class ClientSecure : public Client
{
protected:
    secure_contex client;
    bool _connected;
    int _lastError = 0;
    int ssl_begin(const char *host, uint32_t port, int vrf);
    void ssl_init()
    {
        SSL_library_init();
        SSL_load_error_strings();
        //ERR_load_BIO_strings();
        //ERR_load_crypto_strings();
        OpenSSL_add_all_algorithms();
        memset(&client, 0, sizeof(client));
    }

public:
    ClientSecure *next;
    ClientSecure();
    ClientSecure(int socket);
    ~ClientSecure();
    int connect(IPAddress ip, uint16_t port);
    int connect(IPAddress ip, uint16_t port, int32_t timeout);
    int connect(const char *host, uint16_t port);
    int connect(const char *host, uint16_t port, int32_t timeout);
    int connect(IPAddress ip, uint16_t port, const char *rootCABuff, const char *cli_cert, const char *cli_key);
    int connect(const char *host, uint16_t port, const char *rootCABuff, const char *cli_cert, const char *cli_key);
    int connect(IPAddress ip, uint16_t port, const char *pskIdent, const char *psKey);
    int connect(const char *host, uint16_t port, const char *pskIdent, const char *psKey);
    int peek();
    size_t write(uint8_t data);
    size_t write(const uint8_t *buf, size_t size);
    int available();
    int read();
    int read(uint8_t *buf, size_t size);
    void flush() {}
    void stop();
    uint8_t connected();
    int lastError(char *buf, const size_t size);
    void setPreSharedKey(const char *pskIdent, const char *psKey); // psKey in Hex
    void setCACert(const char *rootCA);
    void setCertificate(const char *client_ca);
    void setPrivateKey(const char *private_key);
    bool loadCACert(Stream &stream, size_t size);
    bool loadCertificate(Stream &stream, size_t size);
    bool loadPrivateKey(Stream &stream, size_t size);
    bool verify(const char *domain_name);

    void setHandshakeTimeout(unsigned long seconds) { client.timeout = seconds * 1000; }
    void setCiphers(const char *ciphers) { client.ciphers = ciphers; } // https://testssl.sh/openssl-iana.mapping.html
    void setSNI(const char *sni) { client.sni_host_name = sni; }
    void setVerify(int vrf) { client.verify = vrf; }

    operator bool() { return connected(); }

    ClientSecure &operator=(const ClientSecure &other);

    bool operator==(const bool value) { return bool() == value; }

    bool operator!=(const bool value)
    {
        return bool() != value;
    }

    bool operator==(const ClientSecure &);

    bool operator!=(const ClientSecure &rhs)
    {
        return !this->operator==(rhs);
    };

    int socket() { return client.sock = -1; }

    //friend class Server;
    using Print::write;

private:
    char *_streamLoad(Stream &stream, size_t size);
};

#endif /* _WIFICLIENT_H_ */
