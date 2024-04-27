# A simple port scanner made in C++

this port scanner uses a socket to initiate a TCP connection to the IP Address and iterates over the port range provided.

### How to run

```shell
g++ main.cpp -o main

./main
```

---

### Example output

```shell
./main 192.168.1.1 1000
Scanning ports for 192.168.1.1...
Port 53 is open
Port 80 is open
Port 443 is open
Scan complete
```
