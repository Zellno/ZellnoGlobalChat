# Zellno Global Chat testing

## Build

- PBO builds with prefix ZellnoGlobalChat.
- Zellno signature validates.
- Build performs no installation.

## Startup

- Dedicated server has no script compile errors.
- Client has no script compile errors.
- Server creates profiles/ZellnoGlobalChat/settings.json.

## Interface

- Enter opens chat normally.
- Initial channel is VICINITY.
- Numpad 4 alternates VICINITY and GLOBAL.
- Numpad 4 does not insert the character 4.
- Indicator does not cover the input field.
- Reconnect resets the channel to VICINITY.

## Multiplayer

- VICINITY remains limited by proximity.
- GLOBAL reaches distant players.
- Sender receives one server-relayed copy.
- Messages are not duplicated.

## Compatibility and security

- ZenModCore ! commands still work.
- VPPAdminTools / commands still work.
- Up Arrow chat history still works.
- Empty, oversized and control-character messages are rejected.
- Cooldown rejects rapid Global messages.
- Accepted and rejected requests appear in server logs.
