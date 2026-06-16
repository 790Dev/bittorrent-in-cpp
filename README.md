# BitTorrent Client in C++

A BitTorrent client built from scratch in C++ implementing core BitTorrent protocol functionality including torrent parsing, tracker communication, peer discovery, peer handshakes, piece downloading, and SHA-1 verification.

## Features

- Custom Bencode parser
- Torrent metadata extraction
- SHA-1 info hash generation
- HTTP/HTTPS tracker communication
- Peer discovery and connection
- BitTorrent handshake implementation
- Bitfield parsing
- Interested / Unchoke workflow
- Piece downloading
- Piece verification using SHA-1
- Piece storage

## Tech Stack

- C++
- OpenSSL
- WinSock2
- TCP/IP Networking

## Workflow

```text
Torrent File
    ↓
Parse Metadata
    ↓
Generate Info Hash
    ↓
Contact Tracker
    ↓
Get Peers
    ↓
Handshake
    ↓
Receive Bitfield
    ↓
Send Interested
    ↓
Receive Unchoke
    ↓
Download Piece
    ↓
Verify SHA-1
```

## Build

```bash
g++ -static *.cpp -lssl -lcrypto -lcrypt32 -lws2_32 -o main
```

## Current Status

✅ Torrent Parsing

✅ Tracker Communication

✅ Peer Discovery

✅ Handshake Validation

✅ Bitfield Processing

✅ Piece Downloading

✅ SHA-1 Verification

## Future Improvements

- Multi-peer downloading
- Rarest-first piece selection
- Resume interrupted downloads
- Magnet link support
- DHT support
- Seeding support

## Author

Devender Singh
