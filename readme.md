# ft_irc

*This project has been created as part of the 42 curriculum by [rothiery], [rdedola].*

---

## Description

**ft_irc** is a fully functional IRC (Internet Relay Chat) server implemented in C++98. The goal of this project is to build a server that communicates over TCP/IP and complies with the IRC protocol (RFC 1459), allowing real IRC clients to connect and interact with it.

The server handles multiple simultaneous clients using non-blocking I/O with `poll()` (or equivalent), and supports core IRC features including:

- User authentication (password, nickname, username)
- Channel creation and management
- Private messaging
- Operator privileges and related commands

> No external libraries or boosts are used — pure C++98.

---

## Instructions

### Requirements

- A C++98-compatible compiler (`g++` or `clang++`)
- `make`
- A Unix-based OS (Linux / macOS)

### Compilation

```bash
make
```

### Running the server

```bash
./ircserv <port> <password>
```

- `<port>`: the port number the server will listen on (e.g. `6667`)
- `<password>`: the connection password clients must provide

### Connecting with an IRC client

You can connect using any standard IRC client (e.g. **irssi**, **WeeChat**, **HexChat**):

```bash
nc 127.0.0.1 6667
```

### Supported commands

| Command | Description |
|---------|-------------|
| `PASS`  | Authenticate with the server password |
| `NICK`  | Set or change nickname |
| `USER`  | Set username and realname |
| `JOIN`  | Join or create a channel |
| `PART`  | Leave a channel |
| `PRIVMSG` | Send a message to a user or channel |
| `KICK`  | Remove a user from a channel (operator) |
| `INVITE` | Invite a user to a channel (operator) |
| `TOPIC` | View or change a channel topic (operator) |
| `MODE`  | Set channel/user modes (operator) |
| `QUIT`  | Disconnect from the server |

---

## Resources

### IRC Protocol & Documentation

- [RFC 1459 — Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 — IRC Client Protocol (updated)](https://datatracker.ietf.org/doc/html/rfc2812)
- [Modern IRC documentation](https://modern.ircdocs.horse/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [poll() man page](https://man7.org/linux/man-pages/man2/poll.2.html)

### AI Usage

AI (Claude, ChatGPT) was used during this project for the following tasks:

- **RFC interpretation**: clarifying ambiguous parts of the IRC protocol specification
- **Code review**: suggesting improvements on code structure and error handling

---

## Authors

- **rothiery** — [42 profile](https://profile.intra.42.fr/users/rothiery)
- **rdedola** — [42 profile](https://profile.intra.42.fr/users/rdedola)
