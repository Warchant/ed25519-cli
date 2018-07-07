#include <iostream>
#include "clipp.h"
#include "hexutil.hpp"
#include <regex>
#include <ed25519/ed25519.h>
#include <string>
#include "hexstring.hpp"

using namespace clipp;

std::string readInput() {
  std::string document;
  for (std::string line; std::getline(std::cin, line);) {
    document += line;
  }

  return document;
}

template<typename T>
void processHexstring(const std::string &arg, size_t length, const std::string &longname, T &target) {
  if (Hexstring{length}(arg)) {
    std::string bytes = hex2bytes(arg);
    std::copy(bytes.begin(), bytes.end(), target);
  } else {
    std::cerr << "<<"
              << longname
              << ">>"
              << " must be in hex and have length exactly "
              << length
              << " bytes ("
              << length * 2
              << " in hex)"
              << '\n';
    std::exit(1);
  }
}

bool testPubkeyVsPrivkey(const private_key_t *priv, const public_key_t *pub) {
  public_key_t control;
  ed25519_derive_public_key(priv, &control);

  return 0 == strncmp(
      reinterpret_cast<const char *>(pub->data),
      reinterpret_cast<const char *>(control.data),
      ed25519_pubkey_SIZE);
}

int main(int argc, char **argv) {

  enum class mode {
    sign = 0, verify, keygen, help
  };

  mode selected = mode::help;
  bool selectedWithSeed = false;

  public_key_t pub{};
  private_key_t priv{};
  signature_t sig{};

  auto pubCli = required("-pub", "--public-key") & value("public key") >> ([&](const std::string &arg) {
    return processHexstring(arg, ed25519_pubkey_SIZE, "public key", pub.data);
  });

  auto privCli = required("-priv", "--private-key") & value("private key") >> ([&](const std::string &arg) {
    return processHexstring(arg, ed25519_privkey_SIZE, "private key", priv.data);
  });

  auto sigCli = required("-sig", "--signature") & value("signature") >> ([&](const std::string &arg) {
    return processHexstring(arg, ed25519_signature_SIZE, "signature", sig.data);
  });

  auto cli = (
      command("help").set(selected, mode::help) % "Get documentation"
          | (command("sign").set(selected, mode::sign) % "Sign SDTIN input",
              pubCli % "32 bytes hexencoded public key (64 bytes in hex)",
              privCli % "32 bytes hexencoded private key (64 bytes in hex)"
          )
          | (command("verify").set(selected, mode::verify) % "Verify STDIN input",
              pubCli,
              sigCli % "64 bytes hexencoded signature (128 bytes in hex)"
          )
          | (command("keygen").set(selected, mode::keygen) % "Generate a keypair",
              option("-priv", "--private-key") & value("private key") >> ([&](const std::string &arg) {
                selectedWithSeed = true;
                return processHexstring(arg, ed25519_privkey_SIZE, "private key", priv.data);
              })
          )
  );

  if (!parse(argc, argv, cli)) {
    std::cout << make_man_page(cli, argv[0]);
    return 1;
  }

  switch (selected) {
    case mode::help: {
      std::cout << make_man_page(cli, argv[0]) << '\n';
      break;
    }

    case mode::sign: {
      if (!testPubkeyVsPrivkey(&priv, &pub)) {
        std::cerr << "public key does not match to given private key\n";
        std::cerr << "check "
                  << argv[0]
                  << " "
                  << "keygen -priv "
                  << bytes2hex(priv.data, ed25519_privkey_SIZE)
                  << "\n";
        std::exit(1);
      }

      std::string document = readInput();

      ed25519_sign(
          &sig,
          reinterpret_cast<const unsigned char *>(document.data()),
          document.size(),
          &pub,
          &priv
      );

      std::cout << bytes2hex(sig.data, ed25519_signature_SIZE) << '\n';
      break;
    }

    case mode::verify: {
      std::string document = readInput();

      std::cout <<
                (
                    ed25519_verify(
                        &sig,
                        reinterpret_cast<const unsigned char *>(document.data()),
                        document.size(),
                        &pub
                    )
                    ? "true" : "false"
                )
                << '\n';

      break;
    }

    case mode::keygen: {
      if (selectedWithSeed) {
        ed25519_derive_public_key(&priv, &pub);
      } else {
        ed25519_create_keypair(&priv, &pub);
      }

      std::cout << "public key : "
                << bytes2hex(pub.data, ed25519_pubkey_SIZE)
                << '\n'
                << "private key: "
                << bytes2hex(priv.data, ed25519_privkey_SIZE)
                << '\n';

      break;
    }

    default: {
      std::cerr << "Internal parsing error\n";
    }
  }

  return 0;
}