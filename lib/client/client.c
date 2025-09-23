#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // POSIX-заголовог для работы с UNIX ОС
#include <sys/types.h> // Безнаковые базовые типы данных size_t
#include <sys/socket.h> // Работа с сокетами
#include <netdb.h> // Заголовок для DNS и сетевых сервисов
#include <openssl/ssl.h> // openssl для поддержки tls-шифрования (работает поверх tcp)
#include <openssl/err.h>

static void append_data(char **data, size_t *size, const char *buf, size_t len)
{
	char *new_ptr = realloc(*data, *size + len + 1);
	if (!new_ptr) {
		fprintf(stderr, "Out of memory\n");
		free(*data);
		exit(1);
	}

	*data = new_ptr;
	memcpy(*data + *size, buf, len);
	*size += len;
	(*data)[*size] = '\0';
}

void http_get(const char *url, char **out_data, size_t *out_size)
{
	/*
	void http_get_example:
		const char *url		// напр. «www.example.com» или IP
		char **out data		// указатель на полученные данные
		size_t out_size		// размер полученных данных					 
	*/

	*out_data = NULL;
	*out_size = 0;

	int status;
	int sockete, sende, connecte;

	struct addrinfo hints; //инициализируем структуру под именем hints
	struct addrinfo *res; //указатель res на нее
	memset(&hints, 0,
	       sizeof(hints)); //обнуляем данные в инициализированной структуре, чтобы не было мусора

	hints.ai_family = AF_UNSPEC; //все равно IPv4 или IPv6
	hints.ai_socktype = SOCK_STREAM;
	//TCP stream-sockets - подготовка к соединению

	status = getaddrinfo(url, "http", &hints, &res);
	/*getaddrinfo:
		const char *url - адрес или IP
		const char *service - "http" или "номер порта" 
		struct addrinfo
		res - указывает на связанный список на одну или больше структуру addrinfo
	*/
	if (status != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n",
			gai_strerror(status));
		exit(1);
	}

	sockete = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	/*int socket:
		int domain - PF_INET или PF_INET6 (ipv4 / ipv6)
		int type - SOCK_STREAM / SOCK_DGRAM 
		int protocol - может быть установлен в 0 для автомат. выбора подходящего этому семейству протокола
	return - дескриптор сокета
	*/
	if (sockete < 0) {
		perror("socket");
		freeaddrinfo(res);
		exit(1);
	}

	//bind(sockete, res->ai_addr, res->ai_addrlen);
	/*int bind:
		int sockfd - файловый дескриптор сокета, возвращаемый socket()
		struct sockaddr *my_addr - укащатель на структуру sockaddr - информация о IP и порте
		int addrlen - длина адреса в байтах

	*/

	connecte = connect(sockete, res->ai_addr, res->ai_addrlen);
	/*int connect:
		int sockfd - файловый дескриптор сокета, возвращаемый socket()
		struct sockaddr *my_addr - укащатель на структуру sockaddr - информация о IP и порте
		int addrlen - длина адреса в байтах
	*/
	if (connecte != 0) {
		perror("connect");
		close(sockete);
		freeaddrinfo(res);
		exit(1);
	}
	freeaddrinfo(res); //освобождение связанного списка

	char request[512];
	snprintf(request, sizeof(request),
		 "GET %s HTTP/1.0\r\n"
		 "Host: %s\r\n"
		 "Connection: close\r\n\r\n",
		 "/", url);

	send(sockete, request, strlen(request), 0);
	/*int send: отправка HTTP запроса
		int sockfd
		const void *msg - данныеы которые надо передать
		int len - длина этих данных
		int flags - 
		return - число байт посланных фактически
	*/
	if (sende < 0) {
		perror("send");
		close(sockete);
		exit(1);
	}

	// Читаем и печатаем ответ
	char buffer[1024];
	ssize_t bytes;

	while ((bytes = recv(sockete, buffer, sizeof(buffer) - 1, 0)) > 0) {
		append_data(out_data, out_size, buffer, bytes);
	}
	close(sockete);

	if (*out_data == NULL) {
		fprintf(stderr, "No data received\n");
		exit(1);
	}
}

void https_get(const char *url, const char *path, char **out_data,
	       size_t *out_size)
{
	/*void https_get_example:
		const char *url		// напр. «www.example.com» или IP
		char **out data		// указатель на полученные данные
		size_t out_size		// размер полученных данных					 
	*/

	SSL_library_init(); //SSL инициализация
	OpenSSL_add_all_algorithms(); //загрузка необходимых алгоритмов шифрования

	SSL_CTX *ctx =
		SSL_CTX_new(TLS_client_method()); //инициализация контекста
	if (!ctx) {
		fprintf(stderr, "Не удалось создать SSL context!\n");
		exit(1);
	}

	*out_data = NULL;
	*out_size = 0;

	int status;
	int sockete, sende, connecte;

	struct addrinfo hints; //инициализируем структуру под именем hints
	struct addrinfo *res; //указатель res на нее
	memset(&hints, 0,
	       sizeof(hints)); //обнуляем данные в инициализированной структуре, чтобы не было мусора

	hints.ai_family = AF_UNSPEC; //все равно IPv4 или IPv6
	hints.ai_socktype = SOCK_STREAM;
	//TCP stream-sockets - подготовка к соединению

	status = getaddrinfo(url, "https", &hints, &res);
	/*getaddrinfo:
		const char *url - адрес или IP
		const char *service - "http" или "номер порта" 
		struct addrinfo
		res - указывает на связанный список на одну или больше структуру addrinfo
	*/
	if (status != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n",
			gai_strerror(status));
		exit(1);
	}

	sockete = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	/*int socket:
		int domain - PF_INET или PF_INET6 (ipv4 / ipv6)
		int type - SOCK_STREAM / SOCK_DGRAM 
		int protocol - может быть установлен в 0 для автомат. выбора подходящего этому семейству протокола
	return - дескриптор сокета
	*/
	if (sockete < 0) {
		perror("socket");
		freeaddrinfo(res);
		exit(1);
	}
	freeaddrinfo(res); //освобождение связанного списка

	//bind(sockete, res->ai_addr, res->ai_addrlen);
	/*int bind:
		int sockfd - файловый дескриптор сокета, возвращаемый socket()
		struct sockaddr *my_addr - укащатель на структуру sockaddr - информация о IP и порте
		int addrlen - длина адреса в байтах

	*/

	connecte = connect(sockete, res->ai_addr, res->ai_addrlen);
	/*int connect:
		int sockfd - файловый дескриптор сокета, возвращаемый socket()
		struct sockaddr *my_addr - укащатель на структуру sockaddr - информация о IP и порте
		int addrlen - длина адреса в байтах
	*/
	if (connecte != 0) {
		perror("connect");
		printf("Ошибка при создании socket\n");
		close(sockete);
		freeaddrinfo(res);
		exit(1);
	}

	SSL *ssl = SSL_new(ctx); //инициирует соединение с сервером
	if (!ssl) {
		fprintf(stderr, "Не удалось создать SSL_new\n");
		exit(1);
	}

	if (!SSL_set_tlsext_host_name(
		    ssl,
		    url)) //запрос у сервера сведения относящиеся к веб-сайту
	{
		fprintf(stderr,
			"Не удалось создать SSL_set_tlsext_host_name\n");
		exit(1);
	}

	SSL_set_fd(ssl, sockete); //подключение TCP-сокета к SSL
	if (SSL_connect(ssl) == -1) {
		fprintf(stderr, "SSL соединение не удалось\n");
	}
	printf("SSL/TLS using %s\n",
	       SSL_get_cipher(ssl)); //вывод шифра на экран

	//Объявление и заполнение буфера необходимыми HTTP-заголовками для отправки запроса
	char buffer[9192];

	sprintf(buffer, "GET %s HTTP/1.1\r\n", path);
	sprintf(buffer + strlen(buffer), "Host: %s:443\r\n", url);
	sprintf(buffer + strlen(buffer), "Connection: close\r\n");
	sprintf(buffer + strlen(buffer), "User-Agent: https-simple\r\n");
	sprintf(buffer + strlen(buffer), "\r\n");

	SSL_write(ssl, buffer, strlen(buffer)); //отправка запроса
	printf("Sent Headers: \n%s", buffer);

	//получение данных
	int bytes_received;
	while ((bytes_received = SSL_read(ssl, buffer, sizeof(buffer))) > 0) {
		append_data(out_data, out_size, buffer, bytes_received);
	}

	if (*out_data == NULL) {
		fprintf(stderr, "No data received\n");
		exit(1);
	}

	SSL_shutdown(ssl);
	SSL_free(ssl);
	SSL_CTX_free(ctx);

	close(sockete);
}