# ed25519-cli
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FWarchant%2Fed25519-cli.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FWarchant%2Fed25519-cli?ref=badge_shield)


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
    git submodule update --init
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

example:
```bash
$ ed25519-cli keygen
public key : 10b4b0f158afb93e3fd6111b564ad4c4054ae9a142362d8d9e05a9f2d6444530
private key: 7aa064fb575c861d5af00febf08c1c31620d5a70094c4bcb11cb2720630ee98a

$ echo "1" | ed25519-cli sign -pub 10b4b0f158afb93e3fd6111b564ad4c4054ae9a142362d8d9e05a9f2d6444530 -priv 7aa064fb575c861d5af00febf08c1c31620d5a70094c4bcb11cb2720630ee98a
c538752e628c9ca43b3328f68afc76af40cf68732db00a8c9a885a6d41045b495ef44fb625a6742895d6819a63c254e352537998961a6802687140115811a409

$ echo "1" | ed25519-cli verify -pub 10b4b0f158afb93e3fd6111b564ad4c4054ae9a142362d8d9e05a9f2d6444530 -sig c538752e628c9ca43b3328f68afc76af40cf68732db00a8c9a885a6d41045b495ef44fb625a6742895d6819a63c254e352537998961a6802687140115811a409
true

$ echo "2" | ed25519-cli verify -pub 10b4b0f158afb93e3fd6111b564ad4c4054ae9a142362d8d9e05a9f2d6444530 -sig c538752e628c9ca43b3328f68afc76af40cf68732db00a8c9a885a6d41045b495ef44fb625a6742895d6819a63c254e352537998961a6802687140115811a409
false
```

## License
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FWarchant%2Fed25519-cli.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2FWarchant%2Fed25519-cli?ref=badge_large)
