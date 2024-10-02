Distance-vector routing protocol.

## Build

```make all```

## Usage 

1. Launch the app.
2. Provide number of IP interfaces of the host.
3. For each, provide a specification in the form  ```<CIDR IP interface address> distance <distance to this network>```.

For example:
```
2
10.0.1.1/8 distance 3
192.168.5.43/24 distance 2
```

Run the application on other computers to allow detection of the shortest paths to other networks, if they exist.

The status of the routing table will be printed on the screen.
