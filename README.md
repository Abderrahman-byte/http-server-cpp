# Simple HTTP Server

A very simple lightweight http server that serves static files;
It support multitreading request handling.
It also uses HTTP/1.1 protocol by default to keep connection persistant.

## TODOs :

- [x] Clean Connections Pool
- [x] Parse http url 
- [x] Parse search query
- [x] Create Response Object
- [x] Serve static files
- [ ] Add Keep-alive max requests
- [x] Make it configurable
- [x] Add Error Handling
- [ ] Add config file as commad line argument

## Config file __(All directives)__ :

```
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
