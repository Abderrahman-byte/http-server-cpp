# Simple HTTP Server

A very simple lightweight http server that serves static files;

It support multitreading request handling.

It also uses HTTP/1.1 protocol by default to keep connection persistant.

No Library is required Buildin library Only.

## Installation :

Cmake and make Should be installed

```shell
git clone https://github.com/Abderrahman-byte/http-server-cpp

cd https://github.com/Abderrahman-byte/http-server-cpp

./configure.sh && ./build.sh
mv ./build/simple_http_server /usr/local/bin
```

## Usage :

```
Usage : simple_http_server [-f <config_file>]
        -f --file : config file (default : ./config.cfg)
        -h --help : show options
```

## Config file __(All directives)__ :

```conf
address=127.0.0.1
port=8000
static_dir=./static/
http_version=HTTP/1.1
keep_alive_timeout=5
keep_alive_max_requests=100
threads_count=10
header_server=Simple Http Server
header_powered_by=NULL
```

## TODOs :

- [x] Clean Connections Pool
- [x] Parse http url 
- [x] Parse search query
- [x] Create Response Object
- [x] Serve static files
- [x] Add Keep-alive max requests
- [x] Make it configurable
- [x] Add Error Handling
- [x] Add config file as commad line argument
- [ ] Add Http Status list
- [ ] Add Logs and make it configurable
- [ ] Add Interaple sighandler
- [ ] Add Windows Support
