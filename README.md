# Minitalk

Minitalk is a small client-server program written in C that allows two processes to communicate with each other using signals.

## How to Use
To use minitalk, first compile the program using the Makefile provided:

```shell
make
```

Once the program is compiled, start the server process by running:

```shell
./server
```

The server will display its PID. Make a note of this PID, as it will be needed to start the client process.

To send a message from the client to the server, run the following command in a separate terminal window:

```shell
./client [SERVER_PID] [MESSAGE]
```

Replace `[SERVER_PID]` with the PID displayed by the server when it was

## Implementation details

The communication between the client and server is done using signals. Specifically, the client sends a series of SIGUSR1 and SIGUSR2 signals to the server, with each signal representing a bit in the message. The server listens for these signals and reconstructs the message bit by bit.

The server acknowledges a bit once it has been received, which helps to prevent errors.

