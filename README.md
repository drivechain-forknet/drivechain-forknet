# Forknet Guide
Setup and testing instructions for Forknet

## Dependencies: (Setting this all up in a linux VM is suggested)
- electrum server 
- flutter sdk
- rustup, rust, cargo
- buf_curl or grpcurl
- enforcer + forknet support
- bitwindow + forknet support
- drivechain-forknet (bitcoin 31.x + drivechain fork)

## drivechain-forknet build instructions (example uses ubuntu LTS (24.04)) 
Install build dependencies: 
```git cmake build-essential libsqlite3-dev libboost-all-dev libzmq3-dev pkgconf```

Build:
```
cmake -B build -DBUILD_GUI=OFF -DBUILD_BENCH=OFF -DBUILD_FUZZ_BINARY=OFF -DBUILD_GUI_TESTS=OFF -DBUILD_TESTS=OFF -DENABLE_IPC=OFF -DWITH_ZMQ=ON -DBUILD_UTIL=ON
cmake --build build -j $(nproc)
```


## Data directories & config files:
```
// Windows: C:\Users\Username\AppData\Local\drivechain-forknet
// macOS: ~/Library/Application Support/drivechain-forknet
// Unix-like: ~/.drivechain-forknet
```
Config file name: ```drivechain-forknet.conf```


## Ports
The network port differs from bitcoin core so forknet nodes are not mistaken for
mainnet bitcoin nodes. The rpc port is the same as bitcoin core.
```
network 8433
rpc server 8332
```

# Forknet changes:
- [x] OP_DRIVECHAIN
- [x] OP_RETURN unlimited
- [x] Difficulty reset at block #0
- [x] Optional transaction replay protection
- [ ] Block size decreased
- [ ] SHAD


# TODO
- [ ] Update MAX_PACKAGE_WEIGHT policy to allow very large OP_RETURN outputs in a transaction?
- [ ] Increase MAX_STANDARD_TX_WEIGHT to the block size limit to allow full block size transactions?
- [ ] Verify no usage of OP_NOP10 in historic blocks or updated script interpreter code
- [ ] re-enable GBT peer check https://github.com/drivechain-forknet/drivechain-forknet/commit/daaff800eb02fe7c12312119b237cf189bbcc82c
