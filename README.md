# ed25519-cli

This tool can be used to sign, verify, generate a keypair with ed25519 (both sha2 and sha3).

## 1. build and install

1. build ed25519
    ```bash
    git clone https://github.com/hyperledger/iroha-ed25519
    cd iroha-ed25519
    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD=STATIC -DHASH=sha3_brainhub
    sudo make install
    ```
    
    **Note**: this will install `libed25519` with SHA3. If you need sha2 variant, then change `sha3_brainhub` to `sha2_openssl`.

2. build ed25519-cli
    ```
    git clone https://github.com/Warchant/ed25519-cli
    cd ed25519-cli
    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    sudo make install
    ```
    
    Binary `ed25519-cli` will be installed.


## 2. use

```bash
./ed25519-cli --help                                                                                                                        bogdan@Bogdans-MacBook-Pro
SYNOPSIS
        ./ed25519-cli help
        ./ed25519-cli sign -pub <public key> -priv <private key>
        ./ed25519-cli verify -pub <public key> -sig <signature>
        ./ed25519-cli keygen [-priv <private key>]

OPTIONS
        help        Get documentation
        sign        Sign SDTIN input

        -pub, --public-key <public key>
                    32 bytes hexencoded public key (64 bytes in hex)

        -priv, --private-key <private key>
                    32 bytes hexencoded private key (64 bytes in hex)

        verify      Verify STDIN input

        -pub, --public-key <public key>
                    32 bytes hexencoded public key (64 bytes in hex)

        -sig, --signature <signature>
                    64 bytes hexencoded signature (128 bytes in hex)

        keygen      Generate a keypair
```