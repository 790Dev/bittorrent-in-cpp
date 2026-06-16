# BitTorrent Client in C++

A BitTorrent client built from scratch in C++ that implements the core BitTorrent protocol, including torrent parsing, tracker communication, peer discovery, peer handshakes, piece downloading, and SHA-1 verification.

## Overview

This project demonstrates the implementation of a peer-to-peer file sharing client using the BitTorrent protocol. The client parses `.torrent` files, communicates with trackers over HTTP/HTTPS, discovers peers, establishes peer connections, downloads pieces, and verifies data integrity using SHA-1 hashes.

The project was developed to gain hands-on experience with networking, socket programming, binary protocols, file transfer systems, and distributed systems concepts.

---

## Features

### Torrent Processing

* Custom Bencode parser
* Torrent metadata extraction
* Piece information parsing
* SHA-1 info hash generation

### Tracker Communication

* HTTP tracker support
* HTTPS tracker support
* Tracker URL parsing
* Tracker request generation
* Tracker response parsing

### Peer Communication

* Peer discovery
* TCP socket connections
* BitTorrent handshake implementation
* Handshake validation
* Peer message parsing

### BitTorrent Messages

* Keep-Alive
* Choke
* Unchoke
* Interested
* Not Interested
* Have
* Bitfield
* Request
* Piece

### Piece Downloading

* Piece requests
* Block downloads
* SHA-1 piece verification
* Piece storage

### Networking

* Raw TCP socket programming
* OpenSSL integration
* HTTP response parsing
* Binary protocol handling

---

## Tech Stack

* C++
* OpenSSL
* WinSock2
* TCP/IP Networking
* BitTorrent Protocol
* HTTP/HTTPS

---

## Project Structure

```text
src/
│
├── bencode/
│   ├── BencodeParser
│   └── BencodeEncoder
│
├── torrent/
│   ├── TorrentFile
│   ├── TorrentMetadata
│   └── InfoHashGenerator
│
├── tracker/
│   ├── TrackerClient
│   ├── TrackerRequestBuilder
│   ├── TrackerResponseParser
│   ├── UrlEncoder
│   └── HttpResponse
│
├── peer/
│   ├── PeerHandshake
│   ├── PeerSession
│   ├── PeerMessage
│   ├── PeerMessageReceiver
│   ├── PieceDownloader
│   └── PieceVerifier
│
├── network/
│   ├── TcpClient
│   └── HttpsClient
│
├── storage/
│
└── main.cpp
```

---

## How It Works

```text
Torrent File
      │
      ▼
Parse Metadata
      │
      ▼
Generate Info Hash
      │
      ▼
Contact Tracker
      │
      ▼
Receive Peer List
      │
      ▼
Connect To Peer
      │
      ▼
BitTorrent Handshake
      │
      ▼
Receive Bitfield
      │
      ▼
Send Interested
      │
      ▼
Receive Unchoke
      │
      ▼
Request Piece
      │
      ▼
Download Piece
      │
      ▼
Verify SHA-1 Hash
      │
      ▼
Store Piece
```

---

## Dependencies

### Windows

* MinGW-w64
* OpenSSL
* WinSock2

### Compiler

* GCC / G++
* C++17 or later

---

## Build Instructions

Compile the project:

```bash
g++ -static main.cpp \
bencode/BencodeParser.cpp \
bencode/BencodeEncoder.cpp \
utils/BencodePrinter.cpp \
torrent/TorrentFile.cpp \
torrent/TorrentMetadata.cpp \
torrent/InfoHashGenerator.cpp \
tracker/TrackerClient.cpp \
tracker/UrlEncoder.cpp \
tracker/TrackerRequestBuilder.cpp \
tracker/HttpResponse.cpp \
tracker/TrackerResponseParser.cpp \
peer/PeerIdGenerator.cpp \
peer/PeerHandshake.cpp \
peer/PeerSession.cpp \
network/TcpClient.cpp \
network/HttpsClient.cpp \
-lssl -lcrypto -lcrypt32 -lws2_32 \
-o main
```

Run:

```bash
./main
```

---

## Sample Output

```text
Torrent file loaded successfully

===== TORRENT METADATA =====
Name         : ubuntu-26.04-desktop-amd64.iso

===== TRACKER RESPONSE =====
Seeders    : 2345
Leechers   : 72

Handshake VALID

===== PEER MESSAGE =====
Type   : BITFIELD

INTERESTED sent

UNCHOKE received

Downloading full piece 0...

Downloaded bytes : 262144

PIECE VERIFIED
```

---

## Concepts Implemented

* Peer-to-Peer Networking
* BitTorrent Protocol
* Bencode Encoding
* Binary Data Processing
* TCP Socket Programming
* HTTPS Communication
* SHA-1 Hashing
* File Integrity Verification
* Distributed Systems Fundamentals

---

## Future Improvements

* Multi-peer downloading
* Rarest-first piece selection
* Resume interrupted downloads
* Magnet link support
* DHT support
* Peer Exchange (PEX)
* Seeding support

---

## Learning Outcomes

Through this project I gained practical experience in:

* Systems Programming
* Network Programming
* Protocol Design
* Concurrent Systems
* File Transfer Mechanisms
* Data Integrity Verification
* Large Scale Distributed Systems Concepts

---

## Author

**Devender Singh**

Built as a systems programming and networking project to understand the BitTorrent protocol from the ground up.
