
## Table of Contents

- [Introduction](#introduction)
- [Technologies](#technologies)
- [Architecture](#architecture)




## Introduction

For this project I had to implement a server and a client app which offers the possibility to convert various files (pdf, txt, tex, etc.). Users will send a file to the server through the client (which will also provide a graphical interface through which users can select the desired file and conversion type), which will be converted by the server and sent back to the client to be saved at a location chosen by the user. The server will also offer caching functionality for better performance.


## Technologies

Both the client and the server app were written in C++. The UI was created with the QT framework. 

The TCP protocol is a protocol from the TCP/IP protocol stack in the transport layer that ensures the delivery of a stream of bytes from the client to the server in the correct order and establishes the connection between the client and server through a 3-way handshake. We will use the TCP protocol because we want the messages to arrive from the client to the server and back, without losing information in the process which would affect the integrity of our file.  


To implement a concurrent server that responds to all client requests, we will use threads. When a client connects to the server, a thread is created to serve that client.


## Architecture
<p align="center">
  <img src="https://github.com/Claudiu2222/computerNetworksProject/blob/main/readmePics/architecture.jpg" />
</p>

Clients will send the type of the conversion which they want to perform to the server (e.g., ps2pdf, asp2php, etc.). Once they reach the server, it will look for the types in the configuration file where it will retrieve the necessary utility for conversion. To implement the caching functionality, the client will also send the hash of the file to be converted. On the computer where the server process is running, there will be folders for each accepted type (pdf, asp, ps, txt, etc.),in which we'll save the converted files with their respective hash name. Thus, when the client sends the hash, the server will check if it has already been converted and will send it back (if found in the corresponding folder). If this file is not found by the server, the client will send the file's size (to check if the file was delivered in its entirety to the server) and the file to be converted. Since we are using the TCP protocol, message transport between processes will be done through byte streams. Therefore, we will open the files to be converted and transmit byte sequences until we reach EOF. The server process will receive these sequences and write them to a new file, then convert this file with the necessary utility found in the config file, and send the converted file back to the client.

